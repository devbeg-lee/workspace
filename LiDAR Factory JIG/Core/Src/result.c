#include "result.h"

/*
      PC13   //fnd1
      PB7    //fnd2
      PB6    //fnd3
      PB8    //fnd4
      PC1   //fnd5
      PC0   //fnd6
      PB9    //fnd7
*/

/*
g_Result = kResult_Pass;
Result();
*/

volatile enum eResult g_Result = kResult_None;

extern TIM_HandleTypeDef htim3;
int divide_freq = 2000000;
int duty_freq = 3500000;

void fail_sound(uint8_t i)
{
    if (i == 0 || i == 2 || i == 4 || i == 6)
    {
        unsigned int fail_sound[] = {T5, T5, T5, T5, T5, T5, T5, T5}; //수정 중

        __HAL_TIM_SET_AUTORELOAD(&htim3, divide_freq / fail_sound[i]);
        //__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, divide_freq / fail_sound[i] / 2);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty_freq / fail_sound[i] / 2);
    }
    else
    {
        htim3.Instance->CCR3 = 0;
    }
}

void pass_sound(uint8_t i)
{
    unsigned int pass_sound[] = {C5, E5, G5, C6, C5, E5, G5, C6};

    __HAL_TIM_SET_AUTORELOAD(&htim3, divide_freq / pass_sound[i]);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty_freq / pass_sound[i] / 2);
}

void result(uint8_t data)
{
    g_Result = data;

    switch (g_Result)
    {
    case kResult_None:
        LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
        LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
        LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
        LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
        break;

    case kResult_Pass:
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
        for (uint8_t j = 0; j <= 7; j++)
        {
            pass_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_P();
                Delay_ms(1);
                FND_2();
                FND_A();
                Delay_ms(1);
                FND_3();
                FND_S();
                Delay_ms(1);
                FND_4();
                Delay_ms(1);
            }
        }
        break;

    case kResult_Err_1: // UART Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_one();
                Delay_ms(1);
            }
        }
        break;

    case kResult_Err_2: // Detect Pin 1 Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_two();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_3: // Detect Pin 2 Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_three();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_4: // Err Pin Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_four();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_5: // Ethernet chip Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_five();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_6: // APD BIAS Control Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_six();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_7: // Motor speed calibration Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_seven();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_8: // Encoder check start slit Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_eight();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_9: // TDC Init Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_zero();
                Delay_ms(1);
                FND_4();
                FND_nine();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_10: // TDC Calibration Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_one();
                Delay_ms(1);
                FND_4();
                FND_zero();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_11: // LD Tx feedback Fail
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_one();
                Delay_ms(1);
                FND_4();
                FND_one();
                Delay_ms(1);
            }
        }
        break;
    case kResult_Err_12: //여분
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

        for (uint8_t j = 0; j <= 7; j++)
        {
            fail_sound(j);
            for (uint8_t i = 1; i <= 125; i++)
            {
                FND_1();
                FND_E();
                Delay_ms(1);
                FND_2();
                FND_r();
                Delay_ms(1);
                FND_3();
                FND_one();
                Delay_ms(1);
                FND_4();
                FND_two();
                Delay_ms(1);
            }
        }
        break;

    default:
        break;
    }
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    turn_off();
    g_Result = kResult_None;
    g_Status = kStatus_Idle;
}

void FND_1(void)
{
    LL_GPIO_SetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
}
void FND_2(void)
{
    LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
    LL_GPIO_SetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
}
void FND_3(void)
{
    LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
    LL_GPIO_SetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
}
void FND_4(void)
{
    LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
    LL_GPIO_SetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
}

void FND_P(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_ResetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_A(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_S(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_E(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_ResetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_r(void)
{
    LL_GPIO_ResetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_ResetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_zero(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_ResetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_one(void)
{
    LL_GPIO_ResetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_ResetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_two(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_ResetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}
void FND_three(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_four(void)
{
    LL_GPIO_ResetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_five(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_six(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_seven(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_ResetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void FND_eight(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}
void FND_nine(void)
{
    LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
    LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
    LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
    LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
    LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
    LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
    LL_GPIO_SetOutputPin(FND_G_GPIO_Port, FND_G_Pin);
}

void turn_off(void)
{
    LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
    LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
}
