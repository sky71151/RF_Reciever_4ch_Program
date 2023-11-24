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
IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
int on = 0;
int off = 1;
char lastMode = 16;
char timerStarted = 0;
int timerCounter = 0;
int delay = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_IWDG_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
void mode0();
void mode1();
void mode2();
void mode3();
void mode4();
void mode5();
void mode6();
void mode7();
void mode8();
void mode9();
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
  MX_IWDG_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
HAL_Delay(500);
HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_IWDG_Refresh(&hiwdg);


		char Dip1 = !HAL_GPIO_ReadPin(DIP1_GPIO_Port, DIP1_Pin);
		char Dip2 = !HAL_GPIO_ReadPin(DIP2_GPIO_Port, DIP2_Pin);
		char Dip3 = !HAL_GPIO_ReadPin(DIP3_GPIO_Port, DIP3_Pin);
		char Dip4 = !HAL_GPIO_ReadPin(DIP4_GPIO_Port, DIP4_Pin);

		char mode = ((Dip1<<3) + (Dip2<<2) + (Dip3<<1) + Dip4);

		switch (mode) {
			case 0:
				mode0();
				break;

			case 1:
				mode1();
				break;

			case 2:
				mode2();
				break;

			case 3:
				mode3();
				break;

			case 4:
				mode4();
				break;

			case 5:
				mode5();
				break;

			case 6:
				mode6();
				break;

			case 7:
				mode7();
				break;

			case 8:
				mode8(); // timer modus lmp
				break;

			case 9:
				mode9(); // timer modus lmp
				break;
			default:
				mode0();
				break;
		}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Window = 2500;
  hiwdg.Init.Reload = 1561;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 749;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 63999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, R1_Pin|R2_Pin|R3_Pin|R4_Pin
                          |LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : R1_Pin R2_Pin R3_Pin R4_Pin
                           LED_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin
                          |LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DIP1_Pin DIP2_Pin DIP3_Pin DIP4_Pin */
  GPIO_InitStruct.Pin = DIP1_Pin|DIP2_Pin|DIP3_Pin|DIP4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CH1_Pin CH2_Pin CH3_Pin CH4_Pin */
  GPIO_InitStruct.Pin = CH1_Pin|CH2_Pin|CH3_Pin|CH4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void mode0() {

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,
			HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin,
			HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin));

	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin,
			HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin));

}

void mode1() {

	if (lastMode != 1) {
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 1;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,
			HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin,
			HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin));

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}

}

void mode2(){

	if (lastMode != 2) {
		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 2;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,
			HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}


}

void mode3(){


	if (lastMode != 3) {
		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 3;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)) {
		HAL_GPIO_TogglePin(R2_GPIO_Port, R2_Pin);
		while (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}
}

void mode4(){

	if (lastMode != 4) {
		HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 4;
	}

	if (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin)) {
		HAL_GPIO_TogglePin(R1_GPIO_Port, R1_Pin);
		while (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)) {
		HAL_GPIO_TogglePin(R2_GPIO_Port, R2_Pin);
		while (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}
}

void mode5(){

	if (lastMode != 5) {
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
	lastMode = 5;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,
			HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}



}

void mode6(){

	if (lastMode != 6) {
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
	lastMode = 6;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,
			HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}



}

void mode7(){

	if (lastMode != 7) {
	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
	lastMode = 7;
	}

	if (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin)) {
		HAL_GPIO_TogglePin(R1_GPIO_Port, R1_Pin);
		while (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)) {
		HAL_GPIO_TogglePin(R2_GPIO_Port, R2_Pin);
		while (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}



}

void mode8(){

	if (lastMode != 8) {
		HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 8;
	}


	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));

	if (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin)) {

		HAL_TIM_Base_Stop_IT(&htim1);
		HAL_TIM_Base_Stop(&htim1);

		timerStarted = 0;
		timerCounter = 0;

		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);

	}


	if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)) {
		if (!timerStarted) {

			TIM1->CNT = 0;
			timerStarted = 1;
			timerCounter = 0;
			delay = 210;
			HAL_TIM_Base_Start_IT(&htim1);
			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);

		} else {
			HAL_TIM_Base_Stop_IT(&htim1);
			HAL_TIM_Base_Stop(&htim1);

			timerStarted = 0;
			timerCounter = 0;

			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);

		}
		while (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin));

	}


	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin))
			;
		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin))
			;
		HAL_Delay(100);
	}

}

void mode9(){

	if (lastMode != 9) {
		HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	lastMode = 9;
	}

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,
			HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin));


	if (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin)) {

		HAL_TIM_Base_Stop_IT(&htim1);
		HAL_TIM_Base_Stop(&htim1);

		timerStarted = 0;
		timerCounter = 0;

		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);


	}


	if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)) {


		if (!timerStarted) {
			TIM1->CNT = 0;
			timerStarted = 1;
			timerCounter = 0;
			delay = 210;
			HAL_TIM_Base_Start_IT(&htim1);
			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);


		}else {
			HAL_TIM_Base_Stop_IT(&htim1);
			HAL_TIM_Base_Stop(&htim1);

			timerStarted = 0;
			timerCounter = 0;

			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);




	}
		while(HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin)){
			HAL_IWDG_Refresh(&hiwdg);
		}
	}

	if (!HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin) && timerStarted){

		if (timerCounter < 7) {
			HAL_TIM_Base_Stop_IT(&htim1);
			HAL_TIM_Base_Stop(&htim1);

			timerStarted = 0;
			timerCounter = 0;
			TIM1->CNT = 0;

			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);

		}


	}

	if (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)) {
		HAL_GPIO_TogglePin(R3_GPIO_Port, R3_Pin);
		while (HAL_GPIO_ReadPin(CH3_GPIO_Port, CH3_Pin)){
			HAL_IWDG_Refresh(&hiwdg);
		}

		HAL_Delay(100);
	}

	if (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)) {
		HAL_GPIO_TogglePin(R4_GPIO_Port, R4_Pin);
		while (HAL_GPIO_ReadPin(CH4_GPIO_Port, CH4_Pin)){
			HAL_IWDG_Refresh(&hiwdg);
		}

		HAL_Delay(100);
	}



}


// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim1 )
  {
   timerCounter++;

   if (timerCounter == delay) {

	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_Base_Stop(&htim1);

	timerStarted = 0;

	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
}


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
