/* E220: UART 8N1 RX interrupt từng byte và TX DMA, có FIFO vòng. */
#include "e220.h"
#include <stddef.h>
#include <string.h>

static int valid_handle(const E220_t *e) {
    return e != NULL && e->huart != NULL && e->huart->Instance != NULL &&
           e->huart->Init.BaudRate > 0U;
}

/* Bật RX ngắt 1 byte; yêu cầu UART 8N1 và DMA TX. */
HAL_StatusTypeDef E220_Init(E220_t *e, UART_HandleTypeDef *uart) {
    if (e == NULL || uart == NULL || uart->Instance == NULL ||
        uart->hdmatx == NULL ||
        uart->Init.BaudRate == 0U ||
        uart->Init.WordLength != UART_WORDLENGTH_8B ||
        uart->Init.StopBits != UART_STOPBITS_1 ||
        uart->Init.Parity != UART_PARITY_NONE ||
        uart->Init.HwFlowCtl != UART_HWCONTROL_NONE) return HAL_ERROR;

    memset(e, 0, sizeof(*e));
    e->huart = uart;
    e->rx_status = HAL_UART_Receive_IT(uart, &e->rx_byte, 1U);
    return e->rx_status;
}

/* Copy dữ liệu sang buffer rồi phát DMA. */
HAL_StatusTypeDef E220_Send_DMA(E220_t *e, const uint8_t *data, uint16_t len) {
    if (!valid_handle(e) || e->huart->hdmatx == NULL || len == 0U ||
        len > E220_MAX_PACKET_SIZE || data == NULL) return HAL_ERROR;

    if (e->tx_active || e->huart->gState != HAL_UART_STATE_READY) {
        ++e->tx_busy_count;
        return HAL_BUSY;
    }

    e->tx_active = 1U;
    e->tx_begin_ms = HAL_GetTick();
    memcpy(e->tx_dma_buffer, data, len);
    HAL_StatusTypeDef rc = HAL_UART_Transmit_DMA(e->huart, e->tx_dma_buffer, len);
    if (rc == HAL_OK) {
        ++e->tx_start_count;
    } else {
        e->tx_active = 0U;
        if (rc == HAL_BUSY) ++e->tx_busy_count;
        else ++e->tx_error_count;
    }
    return rc;
}

HAL_StatusTypeDef E220_SendString_DMA(E220_t *e, const char *str) {
    if (!str) return HAL_ERROR;
    size_t n = 0U;
    while (n <= E220_MAX_PACKET_SIZE && str[n] != '\0') ++n;
    if (n == 0U || n > E220_MAX_PACKET_SIZE) return HAL_ERROR;
    return E220_Send_DMA(e, (const uint8_t *)str, (uint16_t)n);
}

HAL_StatusTypeDef E220_Send(E220_t *e, const uint8_t *data, uint16_t n) {
    return E220_Send_DMA(e, data, n);
}

/* Tên IT nhưng thực tế gọi TX DMA. */
HAL_StatusTypeDef E220_Send_IT(E220_t *e, const uint8_t *data, uint16_t n) {
    return E220_Send_DMA(e, data, n);
}

HAL_StatusTypeDef E220_SendString(E220_t *e, const char *s) {
    return E220_SendString_DMA(e, s);
}

/* Kết thúc truyền DMA, xóa cờ bận. */
void E220_TxCpltCallback(E220_t *e) {
    if (!valid_handle(e)) return;
    e->tx_active = 0U;
    ++e->tx_done_count;
}

/* Đưa byte vào FIFO vòng và kích RX IT tiếp. */
void E220_RxCallback(E220_t *e) {
    if (!valid_handle(e)) return;
    ++e->rx_total_count;
    uint16_t next = (uint16_t)((e->rx_head + 1U) % E220_RX_BUFFER_SIZE);
    if (next != e->rx_tail) {
        e->rx_buffer[e->rx_head] = e->rx_byte;
        __DMB();
        e->rx_head = next;
    } else {
        ++e->rx_overflow_count;
    }
    e->rx_status = HAL_UART_Receive_IT(e->huart, &e->rx_byte, 1U);
    if (e->rx_status != HAL_OK) {
        ++e->rx_rearm_fail_count;
        e->rx_rearm_pending = 1U;
        e->rx_rearm_since_ms = HAL_GetTick();
    } else {
        e->rx_rearm_pending = 0U;
    }
}

/* ISR: record error only. Do not perform blocking abort/re-init inside IRQ. */
void E220_ErrorCallback(E220_t *e) {
    if (!valid_handle(e)) return;
    ++e->uart_error_count;
    e->last_uart_error = HAL_UART_GetError(e->huart);
    if (!e->rx_rearm_pending) e->rx_rearm_since_ms = HAL_GetTick();
    e->rx_rearm_pending = 1U;
    if (e->huart->gState == HAL_UART_STATE_READY && e->tx_active) {
        e->tx_active = 0U;
        ++e->tx_error_count;
    }
}

/* UART recovery from foreground. The 700-ms threshold is for the UART
 * DMA transfer, NOT for radio-air delivery; keep M0/M1 in normal mode. */
void E220_Service(E220_t *e) {
    if (!valid_handle(e)) return;
    uint32_t now = HAL_GetTick();

    if (e->tx_active && (uint32_t)(now - e->tx_begin_ms) > 700U) {
        HAL_StatusTypeDef rc = HAL_UART_AbortTransmit(e->huart);
        if (rc == HAL_OK && e->huart->gState == HAL_UART_STATE_READY) {
            e->tx_active = 0U;
            ++e->tx_stall_recover_count;
            ++e->tx_error_count;
        }
    }

    /* Normal state after HAL_UART_Receive_IT is BUSY_RX. If it silently
     * becomes READY, there is no active one-byte receive request. */
    if (!e->rx_rearm_pending && e->huart->RxState == HAL_UART_STATE_READY) {
        e->rx_rearm_pending = 1U;
        e->rx_rearm_since_ms = now;
    }
    if (!e->rx_rearm_pending) return;
    if ((uint32_t)(now - e->rx_retry_last_ms) < 25U) return;
    e->rx_retry_last_ms = now;

    /* Allow HAL error processing to finish before aborting stale RX state. */
    if (e->huart->RxState != HAL_UART_STATE_READY) {
        if ((uint32_t)(now - e->rx_rearm_since_ms) < 60U) return;
        if (HAL_UART_AbortReceive(e->huart) != HAL_OK) {
            ++e->rx_restart_fail_count;
            return;
        }
    }
    if (e->huart->RxState != HAL_UART_STATE_READY) return;
    e->rx_status = HAL_UART_Receive_IT(e->huart, &e->rx_byte, 1U);
    if (e->rx_status == HAL_OK) {
        e->rx_rearm_pending = 0U;
        ++e->rx_restart_count;
    } else {
        ++e->rx_restart_fail_count;
    }
}

uint16_t E220_Available(E220_t *e) {
    if (!valid_handle(e)) return 0U;
    return (uint16_t)((e->rx_head + E220_RX_BUFFER_SIZE - e->rx_tail) % E220_RX_BUFFER_SIZE);
}

uint8_t E220_ReadByte(E220_t *e) {
    if (!valid_handle(e) || e->rx_tail == e->rx_head) return 0U;
    uint16_t index = e->rx_tail;
    __DMB();
    uint8_t data = e->rx_buffer[index];
    __DMB();
    e->rx_tail = (uint16_t)((index + 1U) % E220_RX_BUFFER_SIZE);
    return data;
}

uint16_t E220_Read(E220_t *e, uint8_t *data, uint16_t max_len) {
    if (data == NULL) return 0U;
    uint16_t n = 0U;
    while (n < max_len && E220_Available(e) != 0U)
        data[n++] = E220_ReadByte(e);
    return n;
}
