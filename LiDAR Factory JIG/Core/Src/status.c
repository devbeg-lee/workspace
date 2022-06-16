#include "status.h"

uint8_t connect = 0;
uint8_t INFO_RX_BUFF[13] = {0};
uint8_t INFO_RX_Cnt = 0;
uint8_t LiDAR_Model = 0;
uint8_t Detect1_Result = 0;
uint8_t Detect2_Result = 0;
uint8_t Detect3_Result = 0;
uint8_t Detect_Check_Count = 0;
uint8_t VIEWER_RX_BUFF[9] = {0};
uint8_t VIEWER_RX_Cnt = 0;
uint8_t LiDAR_RX_BUFF[256] = {0};
uint8_t LiDAR_RX_Cnt = 0;
uint8_t Test_Start_Flag = 0;

void Info_status(void)
{
    uint8_t checksum = 0;
    // uint8_t temp_INFO_DATA[13] = {0xFA, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x05, 0x01, 0xF4, 0x01, 0x2F, 0x04, 0xFF};

    LiDAR_Protocol_Tx(LIDAR_COMMAND_INFO);
    Delay_ms(500);
    while (LiDARQueue.data > 0)
    {
        INFO_RX_BUFF[INFO_RX_Cnt++] = GetDataFromUartQueue(&hLiDAR);
    }
    if (INFO_RX_BUFF[0] != 0xFA)
    {
        INFO_RX_Cnt = 0;
        memset(INFO_RX_BUFF, 0, sizeof(INFO_RX_BUFF));
    }
    else
    {
        checksum = INFO_RX_BUFF[0];
        for (uint8_t i = 1; i < INFO_RX_Cnt - 1; i++)
        {
            checksum ^= INFO_RX_BUFF[i];
        }

        if (INFO_RX_BUFF[12] == checksum)
        {
            LiDAR_Model = INFO_RX_BUFF[11];
            INFO_RX_Cnt = 0;
            g_Status = kStatus_Detect1;
        }
        else
        {
            INFO_RX_Cnt = 0;
            memset(INFO_RX_BUFF, 0, sizeof(INFO_RX_BUFF));
        }
    }
}

void Detect1_status(void)
{
    while (Detect_Check_Count < 20 && Detect1_Result != 0x01U)
    {
        LiDAR_Protocol_Tx(LIDAR_COMMAND_DETECT1);
        Delay_ms(1);
        Detect1_Result = HAL_GPIO_ReadPin(Detect_SIG_1_GPIO_Port, Detect_SIG_1_Pin);

        Detect_Check_Count++;
    }
    Detect_Check_Count = 0;

    if (LiDAR_Model == 0x04) // R300
    {
        g_Status = kStatus_Detect3;
    }
    else
    {
        g_Status = kStatus_Detect2;
    }
}

void Detect2_status(void)
{
    while (Detect_Check_Count < 20 && Detect2_Result != 0x01U)
    {
        LiDAR_Protocol_Tx(LIDAR_COMMAND_DETECT2);
        Delay_ms(1);
        Detect2_Result = HAL_GPIO_ReadPin(Detect_SIG_2_GPIO_Port, Detect_SIG_2_Pin);

        Detect_Check_Count++;
    }

    Detect_Check_Count = 0;
    g_Status = kStatus_Detect3;
}

void Detect3_status(void)
{
    while (Detect_Check_Count < 20 && Detect3_Result != 0x01U)
    {
        LiDAR_Protocol_Tx(LIDAR_COMMAND_DETECT3);
        Delay_ms(5);
        if (LiDAR_Model == 0x04) // R300
        {
            Detect3_Result = HAL_GPIO_ReadPin(Detect_SIG_2_GPIO_Port, Detect_SIG_2_Pin);
        }
        else
        {
            Detect3_Result = HAL_GPIO_ReadPin(Detect_SIG_3_GPIO_Port, Detect_SIG_3_Pin);
        }

        Detect_Check_Count++;
    }

    Detect_Check_Count = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
        Delay_ms(500);
    }
    g_Status = kStatus_Idle;
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_15);
}

void Idle_status(void)
{
    __HAL_UART_ENABLE_IT(&hViewer, UART_IT_RXNE);

    uint8_t checksum = 0;

    uint8_t CONNECT_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xDA};
    uint8_t INFO_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x25};
    uint8_t MODE_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x01, 0x00, 0x01, 0x00, 0xDA};
    uint8_t START_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x24};
    uint8_t DETECT1_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x02, 0x00, 0x00, 0x00, 0x27};
    uint8_t DETECT2_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x26};
    uint8_t DETECT3_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x04, 0x00, 0x00, 0x00, 0x21};
    uint8_t RESET_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x08, 0x00, 0x00, 0x00, 0xD2};

    LiDAR_Cur_Check();

    while (ViewerQueue.data > 0)
    {
        VIEWER_RX_BUFF[VIEWER_RX_Cnt++] = GetDataFromUartQueue(&hViewer);
    }

    if (VIEWER_RX_BUFF[0] != 0xFA)
    {
        VIEWER_RX_Cnt = 0;
        memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
    }
    else
    {
        checksum = VIEWER_RX_BUFF[0];
        for (uint8_t i = 1; i < VIEWER_RX_Cnt - 1; i++)
        {
            checksum ^= VIEWER_RX_BUFF[i];
        }

        if (VIEWER_RX_BUFF[8] == checksum)
        {
            if (memcmp(&CONNECT_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0) // PC Connect
            {

                GUI_Protocol_Tx(GUI_COMMAND_CONNECT, 1);
                connect = 1;
                if (Mode_data == 0)
                {
                    LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_15);
                }
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&INFO_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0) // PC -> JIG Info request
            {
                HAL_UART_Transmit(&hViewer, INFO_RX_BUFF, sizeof(INFO_RX_BUFF), 100);
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&DETECT1_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0) // PC -> JIG Detect 1 reqeust
            {
                GUI_Protocol_Detect_Tx(LIDAR_COMMAND_DETECT1, Detect1_Result);
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&DETECT2_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0) // PC -> JIG Detect 1 reqeust
            {
                GUI_Protocol_Detect_Tx(LIDAR_COMMAND_DETECT2, Detect2_Result);
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&DETECT3_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0) // PC -> JIG Detect 1 reqeust
            {
                GUI_Protocol_Detect_Tx(LIDAR_COMMAND_DETECT3, Detect3_Result);
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&MODE_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0)
            {
                GUI_Protocol_Mode_Tx(Mode_data);
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&START_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0)
            {
                g_Status = kStatus_Test;
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else if (memcmp(&RESET_BUFF, &VIEWER_RX_BUFF, sizeof(VIEWER_RX_BUFF)) == 0)
            {
                GUI_Protocol_Tx(GUI_COMMAND_RESET, 1);
                g_Status = kStatus_Info;
                connect = 0;
                memset(INFO_RX_BUFF, 0, sizeof(INFO_RX_BUFF));
                memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
                VIEWER_RX_Cnt = 0;
            }
            else
            {
            }
            VIEWER_RX_Cnt = 0;
        }
        else
        {
            VIEWER_RX_Cnt = 0;
            memset(VIEWER_RX_BUFF, 0, sizeof(VIEWER_RX_BUFF));
        }
    }
}

void Test_status(void)
{
    uint8_t ETH_BUFF[6] = {' ', 'E', 't', 'h', 'e', 'r'};
    uint8_t APD_BUFF[6] = {' ', 'A', 'P', 'D', ' ', 'B'};
    uint8_t MOT_BUFF[6] = {' ', 'M', 'o', 't', 'o', 'r'};
    uint8_t ENC_BUFF[6] = {' ', 'E', 'n', 'c', 'o', 'd'};
    uint8_t TDC_INIT_BUFF[6] = {' ', 'T', 'D', 'C', ' ', 'I'};
    uint8_t TDC_CAL_BUFF[6] = {' ', 'T', 'D', 'C', ' ', 'C'};

    LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_15);
    HAL_TIM_Base_Start_IT(&htim2);

    if (Test_Start_Flag == 0)
    {
        LiDAR_Protocol_Tx(LIDAR_COMMAND_START);
    }
    while (LiDARQueue.data > 0)
    {
        Test_Start_Flag = 1;
        uint8_t data = GetDataFromUartQueue(&hLiDAR);
        // if (data != '\n') // non carriage return
        if (data != ']' && data != '\n')
        {
            LiDAR_RX_BUFF[LiDAR_RX_Cnt++] = data;
        }
        else if (data == ']') // input carriage return
        {
            if (LiDAR_RX_BUFF[LiDAR_RX_Cnt - 2] == 'o' && LiDAR_RX_BUFF[LiDAR_RX_Cnt - 1] == 'k')
            {
                if (memcmp(ETH_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_ETHERNET, 0x00);
                }
                else if (memcmp(APD_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_APD_BIAS, 0x00);
                }
                else if (memcmp(MOT_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_MOT_SPEED, 0x00);
                }
                else if (memcmp(ENC_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_ENC_CHECK, 0x00);
                }
                else if (memcmp(TDC_INIT_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_TDC_INIT, 0x00);
                }
                else if (memcmp(TDC_CAL_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_TDC_CAL, 0x00);
                    g_Status = kStatus_Result;

                    if (LiDAR_Model == 0x04)
                    {
                        if (Detect1_Result == 0)
                        {
                            g_Result = kResult_Err_2;
                        }
                        else if (Detect3_Result == 0)
                        {
                            g_Result = kResult_Err_4;
                        }
                        else
                        {
                            g_Result = kResult_Pass;
                        }
                    }

                    else
                    {
                        if (Detect1_Result == 0)
                        {
                            g_Result = kResult_Err_2;
                        }
                        else if (Detect2_Result == 0)
                        {
                            g_Result = kResult_Err_3;
                        }
                        else if (Detect3_Result == 0)
                        {
                            g_Result = kResult_Err_4;
                        }
                        else
                        {
                            g_Result = kResult_Pass;
                        }
                    }
                }
                else
                {
                };
                memset(LiDAR_RX_BUFF, 0x00, sizeof(LiDAR_RX_BUFF));
                LiDAR_RX_Cnt = 0;
            }
            else if (LiDAR_RX_BUFF[LiDAR_RX_Cnt - 2] == 'i' && LiDAR_RX_BUFF[LiDAR_RX_Cnt - 1] == 'l')
            {
                if (memcmp(ETH_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_ETHERNET, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_5;
                }
                else if (memcmp(APD_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_APD_BIAS, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_6;
                }
                else if (memcmp(MOT_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_MOT_SPEED, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_7;
                }
                else if (memcmp(ENC_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_ENC_CHECK, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_8;
                }
                else if (memcmp(TDC_INIT_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_TDC_INIT, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_9;
                }
                else if (memcmp(TDC_CAL_BUFF, LiDAR_RX_BUFF, 6) == 0)
                {
                    GUI_Protocol_Tx(GUI_COMMAND_TDC_CAL, 0x01);
                    g_Status = kStatus_Result;
                    g_Result = kResult_Err_10;
                }
                else
                {
                };
                memset(LiDAR_RX_BUFF, 0x00, sizeof(LiDAR_RX_BUFF));
                LiDAR_RX_Cnt = 0;
            }
            else
            {
                memset(LiDAR_RX_BUFF, 0x00, sizeof(LiDAR_RX_BUFF));
                LiDAR_RX_Cnt = 0;
            }
        }
        else if (data == 0x0A) // LF
        {
            memset(LiDAR_RX_BUFF, 0x00, sizeof(LiDAR_RX_BUFF));
            LiDAR_RX_Cnt = 0;
        }
    }
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_15);
    HAL_TIM_Base_Stop_IT(&htim2);
}
