/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "conf.h"
#include "switch.h"
#include "status.h"
  // UART1 : JIG Board DBG
  // UART2 : LiDAR RS232
  // UART3 : LiDAR RS485
  // UART5 : PC
  // UART6 : LiDAR UART     //sj - uart define

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FND_A_Pin LL_GPIO_PIN_13
#define FND_A_GPIO_Port GPIOC
#define FND_F_Pin LL_GPIO_PIN_0
#define FND_F_GPIO_Port GPIOC
#define FND_E_Pin LL_GPIO_PIN_1
#define FND_E_GPIO_Port GPIOC
#define FND1_SIG_Pin LL_GPIO_PIN_2
#define FND1_SIG_GPIO_Port GPIOC
#define In_Current_ADC_Pin LL_GPIO_PIN_0
#define In_Current_ADC_GPIO_Port GPIOA
#define GREEN_LED_Pin LL_GPIO_PIN_1
#define GREEN_LED_GPIO_Port GPIOA
#define Detect_SIG_1_Pin LL_GPIO_PIN_4
#define Detect_SIG_1_GPIO_Port GPIOA
#define Detect_SIG_2_Pin LL_GPIO_PIN_5
#define Detect_SIG_2_GPIO_Port GPIOA
#define Detect_SIG_3_Pin LL_GPIO_PIN_6
#define Detect_SIG_3_GPIO_Port GPIOA
#define RED_LED_Pin LL_GPIO_PIN_7
#define RED_LED_GPIO_Port GPIOA
#define MODE_SW_Pin LL_GPIO_PIN_0
#define MODE_SW_GPIO_Port GPIOB
#define MODE_SW_EXTI_IRQn EXTI0_IRQn
#define BLUE_LED_Pin LL_GPIO_PIN_12
#define BLUE_LED_GPIO_Port GPIOB
#define FB_STOP1_SIG_Pin LL_GPIO_PIN_13
#define FB_STOP1_SIG_GPIO_Port GPIOB
#define LD_TRIG_Pin LL_GPIO_PIN_14
#define LD_TRIG_GPIO_Port GPIOB
#define START_SW_Pin LL_GPIO_PIN_15
#define START_SW_GPIO_Port GPIOB
#define START_SW_EXTI_IRQn EXTI15_10_IRQn
#define Buzzer_Pin LL_GPIO_PIN_8
#define Buzzer_GPIO_Port GPIOC
#define SW_OP_4_Pin LL_GPIO_PIN_9
#define SW_OP_4_GPIO_Port GPIOC
#define SW_OP_3_Pin LL_GPIO_PIN_8
#define SW_OP_3_GPIO_Port GPIOA
#define SW_OP_2_Pin LL_GPIO_PIN_11
#define SW_OP_2_GPIO_Port GPIOA
#define SW_OP_1_Pin LL_GPIO_PIN_12
#define SW_OP_1_GPIO_Port GPIOA
#define FND4_SIG_Pin LL_GPIO_PIN_10
#define FND4_SIG_GPIO_Port GPIOC
#define FND3_SIG_Pin LL_GPIO_PIN_11
#define FND3_SIG_GPIO_Port GPIOC
#define FND2_SIG_Pin LL_GPIO_PIN_5
#define FND2_SIG_GPIO_Port GPIOB
#define FND_C_Pin LL_GPIO_PIN_6
#define FND_C_GPIO_Port GPIOB
#define FND_B_Pin LL_GPIO_PIN_7
#define FND_B_GPIO_Port GPIOB
#define FND_D_Pin LL_GPIO_PIN_8
#define FND_D_GPIO_Port GPIOB
#define FND_G_Pin LL_GPIO_PIN_9
#define FND_G_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
  void USART6_Rx_Callback(USART_TypeDef *USARTx);
  void UART5_Rx_Callback(USART_TypeDef *USARTx);

  enum eStatus
  {
    kStatus_Idle = 0,
    kStatus_Test,
    kStatus_Result
  };

  extern volatile enum eStatus g_Status;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
