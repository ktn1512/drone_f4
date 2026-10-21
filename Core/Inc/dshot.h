#ifndef DSHOT_H
#define DSHOT_H

#include "main.h"

void DSHOT_Init(void);

void DSHOT_Write(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4);

#endif
