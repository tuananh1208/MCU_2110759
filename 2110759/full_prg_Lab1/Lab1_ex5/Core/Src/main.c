/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "software_timer.h"
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
enum led_state {
	led1_red_led2_green,	// 3s
	led1_red_led2_yellow,	// 2s
	led1_green_led2_red,	// 3s
	led1_yellow_led2_red	// 2s
};

const int RED_duration = 5;
const int GREEN_duration = 3;
const int YELLOW_duration = 2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t led_pattern[] = {	// abcdefgh
	    0b1000000, // 0
	    0b1111001, // 1
	    0b0100100, // 2
	    0b0110000, // 3
	    0b0011001, // 4
	    0b0010010, // 5
	    0b0000010, // 6
	    0b1111000, // 7
	    0b0000000, // 8
	    0b0010000  // 9
};

void display7SEG(int n) {
	uint8_t pattern = led_pattern[n];
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_A_Pin, (pattern >> 0) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_B_Pin, (pattern >> 1) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_C_Pin, (pattern >> 2) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_D_Pin, (pattern >> 3) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_E_Pin, (pattern >> 4) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_F_Pin, (pattern >> 5) & 1);
	HAL_GPIO_WritePin(LED_7SEG_Port, SEG_G_Pin, (pattern >> 6) & 1);
}
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  enum led_state state;
  state = led1_yellow_led2_red;

  setTimer1(300);
  setTimer2(100);
  timer1_flag = 1;
  timer2_flag = 1;
  int counter;

  while (1)
  {
	  if (timer1_flag == 1) {
//		  if (state == led1_red_led2_green) {
//			  state = led1_red_led2_yellow;
//		  } else if (state == led1_red_led2_yellow) {
//			  state = led1_green_led2_red;
//		  } else if (state == led1_green_led2_red){
//			  state = led1_yellow_led2_red;
//		  } else {
//			  state = led1_red_led2_green;
//		  }

		  if (state == led1_red_led2_green) {
			  setTimer1(200);
			  state = led1_red_led2_yellow;
			  counter = 2;
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_YELLOW_Pin|LED1_GREEN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_RED_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_GREEN_Pin|LED2_RED_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_YELLOW_Pin, GPIO_PIN_SET);

		  } else if (state == led1_red_led2_yellow) {
			  setTimer1(300);
			  state = led1_green_led2_red;
			  counter = 3;
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_RED_Pin|LED1_YELLOW_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_GREEN_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_YELLOW_Pin|LED2_GREEN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_SET);

		  } else if (state == led1_green_led2_red) {
			  setTimer1(200);
			  state = led1_yellow_led2_red;
			  counter = 2;
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_GREEN_Pin|LED1_RED_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_YELLOW_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_YELLOW_Pin|LED2_GREEN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_SET);

		  } else {
			  setTimer1(300);
			  state = led1_red_led2_green;
			  counter = 5;
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_YELLOW_Pin|LED1_GREEN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED1_RED_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_YELLOW_Pin|LED2_RED_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED2_GREEN_Pin, GPIO_PIN_SET);
		  }
	  }
	  if (timer2_flag == 1) {
		  setTimer2(100);
		  display7SEG(counter--);
	  }
	  timerRun();
	  HAL_Delay(10);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_RED_Pin|LED1_YELLOW_Pin|LED1_GREEN_Pin|LED2_RED_Pin
                          |LED2_YELLOW_Pin|LED2_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_RED_Pin LED1_YELLOW_Pin LED1_GREEN_Pin LED2_RED_Pin
                           LED2_YELLOW_Pin LED2_GREEN_Pin */
  GPIO_InitStruct.Pin = LED1_RED_Pin|LED1_YELLOW_Pin|LED1_GREEN_Pin|LED2_RED_Pin
                          |LED2_YELLOW_Pin|LED2_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_A_Pin SEG_B_Pin SEG_C_Pin SEG_D_Pin
                           SEG_E_Pin SEG_F_Pin SEG_G_Pin */
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
