#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

  void Delay_ms(uint32_t ms);


  /**
   * @brief  Initializes DWT_Cycle_Count for DWT_Delay_us function
   * @return Error DWT counter
   *         1: DWT counter Error
   *         0: DWT counter works
   */
  uint32_t DWT_Delay_Init(void);
  /**
   * @brief  This function provides a delay (in microseconds)
   * @param  microseconds: delay in microseconds
   */
  __STATIC_INLINE void Delay_us(volatile uint32_t microseconds)
  {
    uint32_t clk_cycle_start = DWT->CYCCNT;

    /* Go to number of cycles for system */
    microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

    /* Delay till end */
    while ((DWT->CYCCNT - clk_cycle_start) < microseconds)
    	;
  }

#ifdef __cplusplus
}
#endif

#endif
