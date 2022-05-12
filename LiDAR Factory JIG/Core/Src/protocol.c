#include "protocol.h"

void LiDAR_Protocol_Tx(uint8_t parameter)
{
    uint8_t checksum = 0U;
    uint8_t cnt = 0U;
    uint8_t senddata[9] = {0};

    switch (parameter)
    {
    case LIDAR_COMMAND_INFO:
    case LIDAR_COMMAND_START:
    case LIDAR_COMMAND_DETECT1:
    case LIDAR_COMMAND_DETECT2:
    case LIDAR_COMMAND_DETECT3:

        senddata[cnt++] = PROTOCOL_HEADER;
        senddata[cnt++] = PRODUCT_LINE;
        senddata[cnt++] = PRODUCT_ID;
        senddata[cnt++] = LIDAR_MODE;
        senddata[cnt++] = parameter;
        senddata[cnt++] = 0x00U;
        senddata[cnt++] = 0x00U;
        senddata[cnt++] = 0x00U;

        checksum = senddata[0];
        for (uint16_t i = 1U; i < cnt; i++)
        {
            checksum ^= senddata[i];
        }
        senddata[cnt++] = checksum;
        break;
    default:
        break;
    }
    UART_Transmit(USART6, senddata, sizeof(senddata));
}

void GUI_Protocol_Tx(uint8_t parameter, uint8_t data)
{
    uint8_t checksum = 0U;
    uint8_t cnt = 0U;
    uint8_t senddata[9] = {0};

    switch (parameter)
    {
    case GUI_COMMAND_CONNECT:
        senddata[cnt++] = PROTOCOL_HEADER;
        senddata[cnt++] = PRODUCT_LINE;
        senddata[cnt++] = PRODUCT_ID;
        senddata[cnt++] = GUI_MODE;
        senddata[cnt++] = parameter;
        senddata[cnt++] = 0x00U;
        senddata[cnt++] = 0x00U;
        senddata[cnt++] = data;

        checksum = senddata[0];
        for (uint16_t i = 1U; i < cnt; i++)
        {
            checksum ^= senddata[i];
        }
        senddata[cnt++] = checksum;
        break;

    case GUI_COMMAND_MODE:
    case GUI_COMMAND_ETHERNET:
    case GUI_COMMAND_APD_BIAS:
    case GUI_COMMAND_MOT_SPEED:
    case GUI_COMMAND_ENC_CHECK:
    case GUI_COMMAND_TDC_INIT:
    case GUI_COMMAND_TDC_CAL:

        senddata[cnt++] = PROTOCOL_HEADER;
        senddata[cnt++] = PRODUCT_LINE;
        senddata[cnt++] = PRODUCT_ID;
        senddata[cnt++] = GUI_MODE;
        senddata[cnt++] = parameter;
        senddata[cnt++] = 0x00U;
        senddata[cnt++] = 0x01U;
        senddata[cnt++] = data; // 0x00 : Factory JIG MODE, 0x01 : Tx MODE    0x00 : OK, 0x01 : FAIL

        checksum = senddata[0];
        for (uint16_t i = 1U; i < cnt; i++)
        {
            checksum ^= senddata[i];
        }
        senddata[cnt++] = checksum;
        break;
    default:
        break;
    }
    UART_Transmit(UART5, senddata, sizeof(senddata));
}

void UART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        LL_USART_TransmitData8(USARTx, data[i]);
        while (!LL_USART_IsActiveFlag_TXE(USARTx))
            ;
    }
}