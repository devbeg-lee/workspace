#include "stm32f4xx_hal.h"

#include "ringbuf.h"

UARTQUEUE LiDARQueue;
UARTQUEUE ViewerQueue;

void InitUartQueue(pUARTQUEUE pQueue)
{
    pQueue->data = pQueue->head = pQueue->tail = 0;
}

void PutDataToUartQueue(UART_HandleTypeDef *huart, uint8_t data)
{
    pUARTQUEUE pQueue = (huart->Instance == UART5 ? &ViewerQueue : &LiDARQueue);
    // if (pQueue->data == QUEUE_BUFFER_LENGTH)
    //     GetDataFromUartQueue(huart);
    pQueue->Buffer[pQueue->head++] = data;
    if (pQueue->head == QUEUE_BUFFER_LENGTH)
        pQueue->head = 0;
    pQueue->data++;
}

uint8_t GetDataFromUartQueue(UART_HandleTypeDef *huart)
{
    uint8_t ret;

    // UART_HandleTypeDef *dst = (huart->Instance == USART5 ? &hMonitor : &hViewer);
    pUARTQUEUE pQueue = (huart->Instance == UART5 ? &ViewerQueue : &LiDARQueue);
    // if (HAL_UART_Transmit(dst, pQueue->Buffer + pQueue->tail, 1, 3000) != HAL_OK)
    // {
    //     Error_Handler(__FILE__, __LINE__);
    // }
    ret = pQueue->Buffer[pQueue->tail];
    pQueue->tail++;
    if (pQueue->tail == QUEUE_BUFFER_LENGTH)
        pQueue->tail = 0;
    pQueue->data--;
    return ret;
    HAL_Delay(1);
}