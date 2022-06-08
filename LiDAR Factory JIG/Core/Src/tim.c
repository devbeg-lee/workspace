/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
volatile uint8_t loading_count = 0;

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2500;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2250;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 45-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 500-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 250-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PB2     ------> TIM2_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */

  /* USER CODE END TIM3_MspPostInit 0 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PC8     ------> TIM3_CH3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM3_MspPostInit 1 */

  /* USER CODE END TIM3_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PB2     ------> TIM2_CH4
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    switch (loading_count)
    {
    case 0:
      LL_GPIO_SetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
      LL_GPIO_ResetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
      LL_GPIO_SetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
      loading_count = 1;
      break;

    case 1:
      LL_GPIO_ResetOutputPin(FND_F_GPIO_Port, FND_F_Pin);
      LL_GPIO_SetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
      loading_count = 2;
      break;

    case 2:
      LL_GPIO_ResetOutputPin(FND_E_GPIO_Port, FND_E_Pin);
      LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
      loading_count = 3;
      break;

    case 3:
      LL_GPIO_ResetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
      LL_GPIO_SetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
      loading_count = 4;
      break;

    case 4:
      LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
      LL_GPIO_SetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
      loading_count = 5;
      break;

    case 5:
      LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
      LL_GPIO_SetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
      loading_count = 6;
      break;

    case 6:
      LL_GPIO_ResetOutputPin(FND_D_GPIO_Port, FND_D_Pin);
      LL_GPIO_SetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
      loading_count = 7;
      break;

    case 7:
      LL_GPIO_ResetOutputPin(FND_C_GPIO_Port, FND_C_Pin);
      LL_GPIO_SetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
      loading_count = 8;
      break;

    case 8:
      LL_GPIO_ResetOutputPin(FND_B_GPIO_Port, FND_B_Pin);
      LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
      loading_count = 9;
      break;

    case 9:
      LL_GPIO_ResetOutputPin(FND4_SIG_GPIO_Port, FND4_SIG_Pin);
      LL_GPIO_SetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
      loading_count = 10;
      break;

    case 10:
      LL_GPIO_ResetOutputPin(FND3_SIG_GPIO_Port, FND3_SIG_Pin);
      LL_GPIO_SetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
      loading_count = 11;
      break;

    case 11:
      LL_GPIO_ResetOutputPin(FND2_SIG_GPIO_Port, FND2_SIG_Pin);
      LL_GPIO_SetOutputPin(FND1_SIG_GPIO_Port, FND1_SIG_Pin);
      LL_GPIO_SetOutputPin(FND_A_GPIO_Port, FND_A_Pin);
      loading_count = 0;
      break;
    }
  }
}

/* USER CODE END 1 */
