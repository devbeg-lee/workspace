/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

    /* USER CODE BEGIN Includes */

    /* USER CODE END Includes */

    extern UART_HandleTypeDef huart5;

    extern UART_HandleTypeDef huart6;

    /* USER CODE BEGIN Private defines */
    enum eLiDARComstatus
    {
        kLiDARstatus_Etc = 0,
        kLiDARstatus_Info,
        kLiDARstatus_Serial
    };

    /* USER CODE END Private defines */

    void MX_UART5_Init(void);
    void MX_USART6_UART_Init(void);

    /* USER CODE BEGIN Prototypes */
    void UART5_Rx_Callback(void);
    void USART6_Rx_Callback(void);

    extern volatile enum eLiDARComstatus g_LiDAR_ComStatus;

    // extern uint8_t LiDAR_Rx_Buffer[255];
    // extern uint8_t Viewer_Rx_Buffer[9];
    // extern uint8_t LiDAR_Rx_Flag;
    // extern uint8_t Viewer_Rx_Flag;
    // extern uint8_t LiDAR_Rx_Size;

    /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
