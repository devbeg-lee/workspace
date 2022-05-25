#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include "stm32f4xx_hal.h"
#include "main.h"

#define hViewer huart5
#define hLiDAR huart6

#define QUEUE_BUFFER_LENGTH 255

typedef struct
{
    uint8_t head, tail, data;
    uint8_t Buffer[QUEUE_BUFFER_LENGTH];
} UARTQUEUE, *pUARTQUEUE;

extern UARTQUEUE LiDARQueue;
extern UARTQUEUE ViewerQueue;

void InitUartQueue(pUARTQUEUE pQueue);
void PutDataToUartQueue(UART_HandleTypeDef *huart, uint8_t data);
uint8_t GetDataFromUartQueue(UART_HandleTypeDef *huart);

#endif /* __RINGBUF_H__ */