
#ifndef FPCOUNTER_H
#define FPCOUNTER_H

#include "main.h"
#include "fpCounter_Config.h"

#define FPCOUNTER_TIM_USE_LL

/* Prototype functions */
void fpCounter_p_init(void);
//void fpCounter_p_IRQ(void);
void fpCounter_p_get(double *period, uint32_t *frequency, float *duty);
//HAL_StatusTypeDef fpCounter_demo(void);

#endif
