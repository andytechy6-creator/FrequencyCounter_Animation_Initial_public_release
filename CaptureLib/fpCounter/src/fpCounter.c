#include "fpCounter.h"

// Local variables storing capture compare register values
static uint32_t IC1, IC2;

#define T0	0.00000072f
#define F0	72000000U
#define Kt	1U
#define Kf

/**
* @brief  Enables period counter input capture or CH1 and CH1
* @info		Also enables interrupts or DMA for data transfer
**/
void fpCounter_p_init(void)
{

	LL_TIM_CC_EnableChannel(FPCOUNTER_TIM_MACRO, LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(FPCOUNTER_TIM_MACRO, LL_TIM_CHANNEL_CH2);


	// CH1
	// Set up dma for IC1
	LL_DMA_SetDataLength(FPCOUNTER_DMA, FPCOUNTER_DMA_CH1, 1);
	LL_DMA_SetMemoryAddress(FPCOUNTER_DMA, FPCOUNTER_DMA_CH1, (uint32_t)&IC1);
	LL_DMA_SetPeriphAddress(FPCOUNTER_DMA, FPCOUNTER_DMA_CH1, (uint32_t)&FPCOUNTER_TIM_MACRO->CCR1);
	LL_DMA_EnableChannel(FPCOUNTER_DMA, FPCOUNTER_DMA_CH1);
	// set tim request for IC1
	LL_TIM_EnableDMAReq_CC1(FPCOUNTER_TIM_MACRO);
	// CH2
	// Set up dma for IC2
	LL_DMA_SetDataLength(FPCOUNTER_DMA, FPCOUNTER_DMA_CH2, 1);
	LL_DMA_SetMemoryAddress(FPCOUNTER_DMA, FPCOUNTER_DMA_CH2, (uint32_t)&IC2);
	LL_DMA_SetPeriphAddress(FPCOUNTER_DMA, FPCOUNTER_DMA_CH2, (uint32_t)&FPCOUNTER_TIM_MACRO->CCR2);
	LL_DMA_EnableChannel(FPCOUNTER_DMA, FPCOUNTER_DMA_CH2);
	// set tim request for IC2
	LL_TIM_EnableDMAReq_CC2(FPCOUNTER_TIM_MACRO);
	LL_TIM_EnableCounter(FPCOUNTER_TIM_MACRO);


}

/**
* @brief  Period counter interrupt routine
* @info		Copies input capture compare data to global variable
**/
#if 0
void fpCounter_p_get(double *period, uint32_t *frequency, float *duty)
{
    uint32_t ic1 = IC1;
    uint32_t ic2 = IC2;

    uint32_t delta = (ic2 >= ic1) ? (ic2 - ic1) : (0x10000 - ic1 + ic2);

    *period = (double)delta / F0;
    *frequency = (uint32_t)(F0 / delta);

    *duty = (float)IC2 / (float)(IC1);
}
#endif

#if 1
void fpCounter_p_get(double *period, uint32_t *frequency, float *duty)
{

	uint32_t ic1 = IC1, ic2 = IC2;

	*period = (double)(ic1 +1) /F0;
	*frequency = (uint32_t)((float)1 / *period);
	*duty = ((float)(ic2 +1))/(ic1 +1);
}
#endif


