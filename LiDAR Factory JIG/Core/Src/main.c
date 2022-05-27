/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "result.h"
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile enum eStatus g_Status = kStatus_Info;

uint8_t sArr[10][100] = {{
                             0,
                         },
                         {
                             0,
                         }};
uint8_t row_idx = 0;
uint8_t col_idx = 0;
uint8_t temp[6];
uint8_t result_1 = 0;
uint8_t result_2 = 0;
uint8_t result_3 = 0;
uint8_t result_4 = 0;
uint8_t result_5 = 0;
uint8_t result_6 = 0;
extern uint8_t tx_start_flag;
extern volatile uint8_t detect_flag;
uint8_t avg = 0;
uint8_t stop_feedback = 0;
uint8_t feedback_ng_cnt = 0;

extern uint8_t rx_flag;
extern uint8_t rx_data[9];

extern uint8_t Mode_data;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_UART5_Init();
  MX_TIM3_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  DWT_Delay_Init();

  InitUartQueue(&ViewerQueue);
  InitUartQueue(&LiDARQueue);
  if (HAL_UART_Receive_IT(&hViewer, ViewerQueue.Buffer, 1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UART_Receive_IT(&hLiDAR, LiDARQueue.Buffer, 1) != HAL_OK)
  {
    Error_Handler();
  }

  switch_check();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  __HAL_UART_ENABLE_IT(&huart5, UART_IT_RXNE);
  __HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);

  while (1)
  {
    if (tx_start_flag == 1) // LD Tx On
    {
      if (stop_feedback == 0)
      {
        LL_GPIO_SetOutputPin(LD_TRIG_GPIO_Port, LD_TRIG_Pin);
        stop_feedback = HAL_GPIO_ReadPin(FB_STOP1_SIG_GPIO_Port, FB_STOP1_SIG_Pin);
        LL_GPIO_ResetOutputPin(LD_TRIG_GPIO_Port, LD_TRIG_Pin);
        feedback_ng_cnt++;
        if (feedback_ng_cnt >= 5)
        {
          g_Result = kResult_Err_11;
          stop_feedback = 1;
          feedback_ng_cnt = 0;
        }
        Delay_us(20);
      }
      else
      {
        LL_GPIO_SetOutputPin(LD_TRIG_GPIO_Port, LD_TRIG_Pin);
        LL_GPIO_ResetOutputPin(LD_TRIG_GPIO_Port, LD_TRIG_Pin);
        Delay_us(20);
      }
    }
    else // Etc.
    {
      switch (g_Status)
      {
      case kStatus_Info:
        Info_status();
        break;

      case kStatus_Detect1:
        Detect1_status();
        break;

      case kStatus_Detect2:
        Detect2_status();
        break;

      case kStatus_Detect3:
        Detect3_status();
        break;

      case kStatus_Idle:
        Idle_status();
        break;

      case kStatus_Test:
        Test_status();
        break;

      case kStatus_Result:
        result();
        break;

      default:
        break;
      }
    }

    // swtich(g_Status);
    // {
    // case Status_Info: // LiDAR H/W, F/W Ver, Model request
    //   InfoMode();
    //   break;

    // case Status_Idle: // wait start button, wait PC Interrupt
    //   IdleMode();
    //   break;

    // case Status_Test: // start test
    //   TestMode();
    //   break;

    // case Status_Result: // result display
    //   ResultMode();
    //   break;

    // default:
    //   break;
    // }
    // if (result_1)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_ETHERNET, 0);
    //   result_1 = 0;
    // }
    // if (result_2)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_APD_BIAS, 0);
    //   result_2 = 0;
    // }
    // if (result_3)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_MOT_SPEED, 0);
    //   result_3 = 0;
    // }
    // if (result_4)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_ENC_CHECK, 0);
    //   result_4 = 0;
    // }
    // if (result_5)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_TDC_INIT, 0);
    //   result_5 = 0;
    // }
    // if (result_6)
    // {
    //   GUI_Protocol_Mode(GUI_COMMAND_TDC_CAL, 0);
    //   result_6 = 0;
    // }
  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
   */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*
void USART6_Rx_Callback(USART_TypeDef *USARTx)
{
  uint8_t ETH_BUFF[6] = {' ', 'E', 't', 'h', 'e', 'r'};
  uint8_t APD_BUFF[6] = {' ', 'A', 'P', 'D', ' ', 'B'};
  uint8_t MOT_BUFF[6] = {' ', 'M', 'o', 't', 'o', 'r'};
  uint8_t ENC_BUFF[6] = {' ', 'E', 'n', 'c', 'o', 'd'};
  uint8_t TDC_INIT_BUFF[6] = {' ', 'T', 'D', 'C', ' ', 'I'};
  uint8_t TDC_CAL_BUFF[6] = {' ', 'T', 'D', 'C', ' ', 'C'};

  rx_data = LL_USART_ReceiveData8(USART6);

  if (rx_data != '\n') // non carriage return
  {
    sArr[col_idx][row_idx] = rx_data;
    row_idx++;
  }
  else // carriage return Rx
  {
    if (sArr[col_idx][row_idx - 4] == 'o' && sArr[col_idx][row_idx - 3] == 'k')
    {
      for (uint8_t i = 0; i <= 5; i++)
      {
        temp[i] = sArr[col_idx][i];
      }

      if (memcmp(ETH_BUFF, temp, 6) == 0)
      {
        result_1 = 1;
      }
      if (memcmp(APD_BUFF, temp, 6) == 0)
      {
        result_2 = 1;
      }
      if (memcmp(MOT_BUFF, temp, 6) == 0)
      {
        result_3 = 1;
      }
      if (memcmp(ENC_BUFF, temp, 6) == 0)
      {
        result_4 = 1;
      }
      if (memcmp(TDC_INIT_BUFF, temp, 6) == 0)
      {
        result_5 = 1;
      }
      if (memcmp(TDC_CAL_BUFF, temp, 6) == 0)
      {
        result_6 = 1;
      }

      col_idx++;
      row_idx = 0;
    }
    else if (sArr[col_idx][row_idx - 4] == 'i' && sArr[col_idx][row_idx - 3] == 'l')
    {
      col_idx++;
      row_idx = 0;
    }

    else
    {
      for (uint8_t i = 0; i <= sizeof(row_idx); i++)
      {
        sArr[col_idx][i] = 0;
      }
      row_idx = 0;
    }
  }
}
*/
// void UART5_Rx_Callback(USART_TypeDef *USARTx) // PC Interrupt
// {
//   uint8_t rx_data[9] = {
//       0,
//   };
//   uint8_t CONNECT_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xDA};
//   uint8_t INFO_BUFF[9] = {0xFA, 0x00, 0xD0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x25};
//   uint8_t MODE_BUFF[9] = {0xFA, 0x00, 0xD0, 0xF0, 0x01, 0x00, 0x01, 0x00, 0xDA};

//   for (uint8_t i = 0; i < 9; i++)
//   {
//     rx_data[i] = LL_USART_ReceiveData8(UART5);
//   }

//   if (memcmp(CONNECT_BUFF, rx_data, 9) == 0)
//   {
//     GUI_Protocol_Mode(GUI_COMMAND_CONNECT, 0);
//     connect = 1;
//     // GPIO Interrupt disable repair
//   }

//   if (memcmp(INFO_BUFF, rx_data, 9) == 0)
//   {
//   }
// }

// void InfoMode(void)
// {
//   uint8_t read_flag = 0;
//   uint8_t rec_data[13];
//   uint8_t checksum = 0;

//   LiDAR_Protocol_Mode(LIDAR_COMMAND_INFO);
//   for (uint8_t i = 0; i < 12; i++)
//   {
//     rec_data[i] = LL_USART_ReceiveData8(USART6); // timeout? repair
//   }

//   for (uint8_t j = 0; j < 11; j++)
//   {
//     checksum += rec_data[j];
//   }

//   if (checksum == rec_data[12])
//   {
//     g_LidarInfo.HWVer = (uint16_t)((rec_data[7] & 0x00FF) << 8);
//     g_LidarInfo.HWVer |= (uint16_t)((rec_data[8] & 0x00FF);
//     g_LidarInfo.FWVer = (uint16_t)((rec_data[9] & 0x00FF) << 8);
//     g_LidarInfo.FWVer |= (uint16_t)((rec_data[10] & 0x00FF);
//     g_LidarInfo.Model = rec_data[11];

//     g_Status = Status_Idle;
//   }
//   else
//   {
//     g_Status = Status_Info;
//   }
// }
void Idlemode(void)
{
  // PC community check
  // Model, F/W, H/W Ver Protocol Tx(Timeout 5s)
  // when Rx receive Tx stop
  // when PC request Model info-> model buff clean : UART Passing / buff full : Info Tx to PC  //sj
}

void Test_mode(void)
{
  // UART2(LiDAR) Start protocol Tx
  // LiDAR Factory Serial Rx & Sort -> [fail] : 7-segment, buzzer on
  // detect sig1~3 Tx & Rx
  // all [ok] : 7-segment, buzzer on
  // start button enable
  // Test->Idle Mode change //sj
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
