#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "main.h"

void LiDAR_Protocol_Tx(uint8_t parameter);
void GUI_Protocol_Tx(uint8_t parameter, uint8_t data);
void UART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t length);

#endif