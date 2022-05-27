#include "switch.h"

uint8_t Mode_data;

void switch_check(void)
{
    if (HAL_GPIO_ReadPin(MODE_SW_GPIO_Port, MODE_SW_Pin)) // factory jig
    {
        Mode_data = 0x00U;
        LL_GPIO_SetOutputPin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
        LL_GPIO_ResetOutputPin(RED_LED_GPIO_Port, RED_LED_Pin);
        if (connect)
        {
            // HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // Viewer start button enable only
            g_Start_Switch_IRQ_Flag = 0;
        }
    }
    else // LD Tx
    {
        Mode_data = 0x01U;
        LL_GPIO_ResetOutputPin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
        LL_GPIO_SetOutputPin(RED_LED_GPIO_Port, RED_LED_Pin);
        // HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
        g_Start_Switch_IRQ_Flag = 1;
    }
}