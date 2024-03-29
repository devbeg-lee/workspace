#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "main.h"
#include "adc.h"

extern uint8_t g_R300_connect;
extern uint8_t g_R4_connect;

void LiDAR_Protocol_Tx(UART_HandleTypeDef *huart, uint8_t parameter);
void GUI_Protocol_Tx(uint8_t parameter, uint8_t data);
void GUI_Protocol_Mode_Tx(uint8_t data);
void UART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t length);
void GUI_Protocol_Detect_Tx(uint8_t parameter, uint8_t data);

#endif