#include "status.h"

uint8_t connect = 0;
uint8_t INFO_RX_Flag = 0;
uint8_t INFO_RX_BUFF[13] = {0};
uint8_t INFO_RX_Cnt = 0;

void Idle_status(void)
{

    uint8_t CONNECT_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xDA};
    uint8_t INFO_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x25};
    uint8_t MODE_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x01, 0x00, 0x01, 0x00, 0xDA};
    uint8_t START_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x24};

    uint8_t checksum = 0;

    // uint8_t temp_INFO_DATA[13] = {0xFA, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x05, 0x01, 0xF4, 0x01, 0x2F, 0x04, 0xFF};

    LiDAR_Cur_Check();

    if (ViewerQueue.data > 0)
    {
        /* if (memcmp(&CONNECT_BUFF, &Viewer_Rx_Buffer, sizeof(Viewer_Rx_Buffer)) == 0) // PC Connect
        {
            GUI_Protocol_Tx(GUI_COMMAND_CONNECT, 0);
            connect = 1;
            HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // Viewer start button enable only
        }
        else if (memcmp(&INFO_BUFF, &Viewer_Rx_Buffer, sizeof(Viewer_Rx_Buffer)) == 0) // PC -> JIG Info request
        {
            if (INFO_RX_Flag == 0)
            {
                LiDAR_Protocol_Tx(LIDAR_COMMAND_INFO);
                for (uint8_t i = 0; i <= 12; i++)
                {
                    //                    INFO_RX_BUFF[i] = LL_USART_ReceiveData8(USART6);
                }

                checksum = INFO_RX_BUFF[0];
                for (uint16_t i = 1U; i < 12; i++)
                {
                    checksum ^= INFO_RX_BUFF[i];
                }

                if (checksum == INFO_RX_BUFF[12])
                {
                    INFO_RX_Flag = 1;
                    //                    UART_Transmit(UART5, INFO_RX_BUFF, 13);
                }
            }
            else
            {
                //                UART_Transmit(UART5, INFO_RX_BUFF, 13);
            }
        }
        else if (memcmp(&MODE_BUFF, &LiDAR_Rx_Buffer, LiDAR_Rx_Size) == 0)
        {
            GUI_Protocol_Mode_Tx(Mode_data);
        }
        else if (memcmp(&START_BUFF, &LiDAR_Rx_Buffer, LiDAR_Rx_Size) == 0)
        {
            g_Status = kStatus_Test;
        }
        else
        {
        }
        Viewer_Rx_Flag = 0; */
    }
    else // PC Not Connect
    {
        if (INFO_RX_Flag == 0)
        {
            LiDAR_Protocol_Tx(LIDAR_COMMAND_INFO);
            while (LiDARQueue.data > 0)
            {
                INFO_RX_BUFF[INFO_RX_Cnt] = GetDataFromUartQueue(&hLiDAR);
                INFO_RX_Cnt++;
            }
            if (INFO_RX_BUFF[0] != 0x00)
            {
                INFO_RX_Flag = 1;
            }
        }

        else
        {
        }
        Delay_ms(500);
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

    LiDAR_Protocol_Tx(LIDAR_COMMAND_START);
    Delay_ms(500);
}
