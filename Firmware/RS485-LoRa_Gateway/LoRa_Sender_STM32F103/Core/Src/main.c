/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LoRa.h"
#include <string.h>
#include <stdio.h>
#include<math.h>
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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
LoRa myLoRa;
uint8_t read_data[128];
uint8_t send_data[128];
int RSSI;
volatile uint8_t lora_rx_done = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	// MODULE SETTINGS ----------------------------------------------
	myLoRa = newLoRa();

	myLoRa.hSPIx = &hspi1;
	myLoRa.CS_port = LORA_SS_GPIO_Port;
	myLoRa.CS_pin = LORA_SS_Pin;
	myLoRa.reset_port = LORA_RESET_GPIO_Port;
	myLoRa.reset_pin = LORA_RESET_Pin;
	myLoRa.DIO0_port = LORA_DIO0_GPIO_Port;
	myLoRa.DIO0_pin = LORA_DIO0_Pin;

	myLoRa.frequency = 865;		// default = 433 MHz
	myLoRa.spredingFactor = SF_12;// default = SF_7
	myLoRa.bandWidth = BW_125KHz;// default = BW_125KHz
	myLoRa.crcRate = CR_4_5;// default = CR_4_5
	myLoRa.power = POWER_20db;// default = 20db
	myLoRa.overCurrentProtection = 120;// default = 100 mA
	myLoRa.preamble = 10;// default = 8;

	LoRa_reset(&myLoRa);
	if(LoRa_init(&myLoRa) == LORA_OK){
		HAL_UART_Transmit(&huart1, "LoRa Init Succsess\r\n", sizeof("LoRa Init Succsess\r\n"), 100);
	}else{
		HAL_UART_Transmit(&huart1, "LoRa Init error\r\n", sizeof("LoRa Init error\r\n"), 100);
	}

	// START CONTINUOUS RECEIVING -----------------------------------
	LoRa_startReceiving(&myLoRa);
	//---------------------------------------------------------------

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while (1)
  {
/*
		// SENDING DATA - - - - - - - - - - - - - - - - - - - - - - - - -
		HAL_UART_Transmit(&huart1, "Sending Data\r\n", sizeof("Sending Data\r\n"), 100);
		send_data[0] = 0x3B; // MY ADDRESS
		for (int i = 0; i < 26; i++)
			send_data[i + 1] = 48 + i;
		LoRa_transmit(&myLoRa, send_data, 128, 500);
		HAL_Delay(1500);

		// RECEIVING DATA - - - - - - - - - - - - - - - - - - - - - - - -
		LoRa_receive(&myLoRa, read_data, 128);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	//}
  /* USER CODE END 3 */
//}*/

/* SENDING DATA - - - - - - - - - - - - - - - - - - - - - - - - -
		HAL_UART_Transmit(&huart1, "Sending Data\r\n", sizeof("Sending Data\r\n"), 100);

		// Clear previous data
		memset(send_data, 0, sizeof(send_data));

		// Create whatever message you want here!
		sprintf((char *)send_data, "Hello Tejas");

		// Transmit precisely the length of the string
		LoRa_transmit(&myLoRa, send_data, strlen((char *)send_data), 500);
		HAL_Delay(1500);

		// RECEIVING DATA - - - - - - - - - - - - - - - - - - - - - - - -
		LoRa_receive(&myLoRa, read_data, 128);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	//}
	/* USER CODE END 3 */
//}*/


// SENDING DATA Counter Code- - - - - - - - - - - - - - - - - - - - - - - - -
		HAL_UART_Transmit(&huart1, "Sending Data\r\n", sizeof("Sending Data\r\n"), 100);
		// 1. Create a counter that remembers its value because of 'static'
		static int counter = 0;

		// 2. Clear old data from the array
		memset(send_data, 0, sizeof(send_data));

		uint8_t Tx_Buffer[8];
		Tx_Buffer[0]=255;
		Tx_Buffer[1]=255;
		Tx_Buffer[2]=255;
		Tx_Buffer[3]=255;
		Tx_Buffer[4]=255;
		Tx_Buffer[5]=255;
		Tx_Buffer[6]=255;
		Tx_Buffer[7]=255;

		// 3. Insert the counter into your text message using '%d'
		sprintf((char *)send_data, "Hello Form:");

		// 4. Increase the counter so the next time it loops, the number is higher
		counter++;

		// 5. Transmit the new string exactly at its size
		LoRa_transmit(&myLoRa, Tx_Buffer, 8, 500);

		HAL_Delay(5000); // Wait 1.5 seconds between sending

		// RECEIVING DATA - - - - - - - - - - - - - - - - - - - - - - - -
		LoRa_receive(&myLoRa, read_data, 128);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LORA_SS_GPIO_Port, LORA_SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LORA_RESET_GPIO_Port, LORA_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LORA_SS_Pin */
  GPIO_InitStruct.Pin = LORA_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LORA_SS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LORA_DIO0_Pin */
  GPIO_InitStruct.Pin = LORA_DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LORA_DIO0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LORA_RESET_Pin */
  GPIO_InitStruct.Pin = LORA_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LORA_RESET_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == myLoRa.DIO0_pin){
		LoRa_receive(&myLoRa, read_data, 128);
	}
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
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
