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
            LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_15); // Viewer start button enable only
        }
    }
    else // LD Tx
    {
        Mode_data = 0x01U;
        LL_GPIO_ResetOutputPin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
        LL_GPIO_SetOutputPin(RED_LED_GPIO_Port, RED_LED_Pin);
        LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_15);
    }
}