/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "Button.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
const int digitConfig[][7] = {
        // A, B, C, D, E, F, G, DP
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };
typedef enum
{
  STATE_1,
  STATE_2,
  STATE_3,
  STATE_4
} TrafficLightState;
int state_7SEG = 0;
int state2_7SEG = 0;

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 ) ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int count_StateButton1 = 0;
  int count = 0;
  int time_LEDRED = 5;
  int time_LEDAMB = 3;
  int time_LEDGREEN = 2;
  setTimer0(50);
  setTimer1(50);
  setTimer2(50);
  int GREEN_total = 0;
  int AMB_total = 0;
  int RED_total = 0;
  int state_GREEN = 0;
  int state_AMB = 0;
  int state_RED = 0;
  display7SEG1(0);
  display7SEG2(0);
  setAllLED();
  int counter = 0;
  int counter2 = 0;
  setTimer_RED(100);
  setTimerState(100);
  setTimerSwitch(50);
  TrafficLightState state = STATE_1;
  while (1)
  {
    /* USER CODE END WHILE */
	  if (button1_flag ==1) {
		  if( button1_flag != button1_flagRelease && button1_flagRelease == 0) {
			  count_StateButton1 ++;
			  setAllLED();
			  if(count_StateButton1 > 4) {
				  count_StateButton1 = 1;
			  }
		  }
		  state_7SEG = 0;
		  state2_7SEG = 0;
		  display7SEG1(count_StateButton1);
		  button1_flagRelease = button1_flag ;
		  button1_flag = 0 ;
		  count = 0;
		  if(count_StateButton1 == 1) {
			  counter = -1;
			  counter2 = -1;
		  }
	  }
	  if(count_StateButton1 == 1) {
		    switch (state)
		    {
		    case STATE_1:
		      if (counter <= 0 && counter2 <= 0)
		      {
		    	  setAllLED();
		        HAL_GPIO_WritePin(GPIOA, LED_Green1_Pin | LED_Green3_Pin | LED_RED2_Pin | LED_RED4_Pin, GPIO_PIN_RESET);
		        state = STATE_2;
		        counter2 = time_LEDGREEN;
		        counter = time_LEDRED;
		      }
		      break;

		    case STATE_2:
		      if (counter <= 0 || counter2 <= 0)
		      {
		    	  setAllLED();
		        HAL_GPIO_WritePin(GPIOA, LED_AMB1_Pin | LED_AMB3_Pin | LED_RED2_Pin | LED_RED4_Pin, GPIO_PIN_RESET);

		        state = STATE_3;
		        counter2 = time_LEDAMB;
		      }
		      break;

		    case STATE_3:
		      if (counter <= 0 && counter2 <= 0)
		      {
		    	  setAllLED();
		        HAL_GPIO_WritePin(GPIOA, LED_Green4_Pin | LED_Green2_Pin | LED_RED3_Pin | LED_RED1_Pin, GPIO_PIN_RESET);

		        state = STATE_4;
		        counter = time_LEDGREEN;
		        counter2 = time_LEDRED;
		      }
		      break;

		    case STATE_4:
		      if (counter2 <= 0 || counter <= 0)
		      {
		    	  setAllLED();
		        HAL_GPIO_WritePin(GPIOA, LED_AMB2_Pin | LED_AMB4_Pin | LED_RED3_Pin | LED_RED1_Pin, GPIO_PIN_RESET);

		        state = STATE_1;
		        counter = time_LEDAMB;
		      }
		      break;
		    }
		    display7SEG1(counter);
		    display7SEG2(counter2);

		    if(timerState_flag == 1){
			    counter--;
			    counter2--;
			    setTimerState(100);
		    }
		    if (counter < 0)
		    {
		      counter = 0;
		    }
		    if (counter2 < 0)
		    {
		      counter2 = 0;
		    }
	  }
	  if (count_StateButton1 == 2) {
	  	  	  if (timer0_flag == 1) {
	  	  			  HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin) ;
	  	  			  HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin) ;
	  	  			  HAL_GPIO_TogglePin(LED_RED3_GPIO_Port, LED_RED3_Pin) ;
	  	  			  HAL_GPIO_TogglePin(LED_RED4_GPIO_Port, LED_RED4_Pin) ;
	  	  			  setTimer0(50) ;
	  	  		  }
	  	  		  if (button2_flag == 1) {
	  	  			  button2_flag = 0;
	  	  			  count += 1;
	  	  			  state_RED = 0;
	  	  		  }
		  		  RED_total = time_LEDRED+ count ;
  		  		  if(RED_total >= 100) {
  		  			time_LEDRED = 0;
  		  			count = 0;
  		  		  }
		  			  if (RED_total > 9 && RED_total <= 99) {
		  				  if(timerRED_flag == 1){
	  		  				if(state_RED == 0){
	  		  				    display7SEG2(RED_total / 10);
	  		  				    state_RED = 1;
	  		  				}
	  		  				else{
							display7SEG2(RED_total % 10);
							state_RED = 0;
						}
	  		  			    setTimer_RED(50);
		  				  }
		  			  }
		  			  if(RED_total <= 9){
		  			       display7SEG2(RED_total) ;
		  			  }


	  	  		 if (button3_flag == 1) {
	  	  			  if( button3_flag != button3_flagRelease && button3_flagRelease == 0) {
	  	 	  			 time_LEDRED = time_LEDRED + count ;
	  	 	  			 count = 0;
	  	  			  }
	  	  			  button3_flagRelease = button3_flag ;
	  	  			  button3_flag = 0;
	  	  		 }
	  	  	  }
	  	  	 if (count_StateButton1 == 3) {
	  	  			  if (timer2_flag == 1) {
	  	  				  HAL_GPIO_TogglePin(LED_AMB1_GPIO_Port, LED_AMB1_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_AMB2_GPIO_Port, LED_AMB2_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_AMB3_GPIO_Port, LED_AMB3_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_AMB4_GPIO_Port, LED_AMB4_Pin) ;
	  	  				  setTimer2(50) ;
	  	  			  }
	  		  		  if (button2_flag == 1) {
	  		  			  button2_flag = 0;
	  		  			  count += 1;
	  		  			  state_AMB == 0;
	  		  		  }
	  		  			  AMB_total = time_LEDAMB+ count ;
		  		  		  if(AMB_total >= 100) {
		  		  			time_LEDAMB = 0;
		  		  			count = 0;
		  		  		  }
	  		  			  if (AMB_total > 9 && AMB_total <= 99) {
	  		  				  if(timerAMB_flag == 1){
	  	  		  				if(state_AMB == 0){
	  	  		  				    display7SEG2(AMB_total / 10);
	  	  		  				    state_AMB = 1;
	  	  		  				}
	  	  		  				else{
									display7SEG2(AMB_total % 10);
									state_AMB = 0;
								}
	  	  		  			    setTimer_AMB(50);
	  		  				  }
	  		  			  }
	  		  			  if(AMB_total <= 9){
	  		  			       display7SEG2(AMB_total) ;
	  		  			  }

	  		  		 if (button3_flag == 1) {
	  		  			  if( button3_flag != button3_flagRelease && button3_flagRelease == 0) {
	  		 	  			 time_LEDAMB = time_LEDAMB + count ;
	  		 	  			 count = 0;
	  		  			  }
	  		  			  button3_flagRelease = button3_flag ;
	  		  			  button3_flag = 0;
	  		  		 }
	  	  		  }
	  	  	 if (count_StateButton1 == 4) {
	  	  			  if (timer1_flag == 1) {
	  	  				  HAL_GPIO_TogglePin(LED_Green1_GPIO_Port, LED_Green1_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_Green2_GPIO_Port, LED_Green2_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_Green3_GPIO_Port, LED_Green3_Pin) ;
	  	  				  HAL_GPIO_TogglePin(LED_Green4_GPIO_Port, LED_Green4_Pin) ;
	  	  				  setTimer1(50) ;
	  	  			  }
	  		  		  if (button2_flag == 1) {
	  		  			  button2_flag = 0;
	  		  			  count += 1;
	  		  			  state_GREEN == 0;
	  		  		  }
	  		  		  GREEN_total = time_LEDGREEN + count ;
	  		  		  if(GREEN_total >= 100) {
	  		  			time_LEDGREEN = 0;
	  		  			count = 0;
	  		  		  }
					  if(GREEN_total > 9 && GREEN_total <= 99) {
						  if(timerGREEN_flag == 1){
								if(state_GREEN == 0){
									display7SEG2(GREEN_total / 10);
									state_GREEN = 1;
								}
								else{
									display7SEG2(GREEN_total % 10);
									state_GREEN = 0;
								}
							setTimer_GREEN(50);
						  }
					  }
					  if(GREEN_total <= 9){
						   display7SEG2(GREEN_total) ;
					  }


			          if (button3_flag == 1) {
					       if( button3_flag != button3_flagRelease && button3_flagRelease == 0) {
						        time_LEDGREEN = time_LEDGREEN + count ;
						        count = 0;
					        }
					  button3_flagRelease = button3_flag ;
					  button3_flag = 0;
				 }
			  }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin|LED_RED2_Pin|LED_RED3_Pin|LED_RED4_Pin
                          |LED_AMB1_Pin|LED_AMB2_Pin|LED_AMB3_Pin|LED_AMB4_Pin
                          |LED_Green1_Pin|LED_Green2_Pin|LED_Green3_Pin|LED_Green4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D1_Pin
                          |SEG_E1_Pin|SEG_F1_Pin|SEG_G1_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin|SEG_A1_Pin
                          |SEG_B1_Pin|SEG_C1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Button1_Pin Button2_Pin Button3_Pin */
  GPIO_InitStruct.Pin = Button1_Pin|Button2_Pin|Button3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED1_Pin LED_RED2_Pin LED_RED3_Pin LED_RED4_Pin
                           LED_AMB1_Pin LED_AMB2_Pin LED_AMB3_Pin LED_AMB4_Pin
                           LED_Green1_Pin LED_Green2_Pin LED_Green3_Pin LED_Green4_Pin */
  GPIO_InitStruct.Pin = LED_RED1_Pin|LED_RED2_Pin|LED_RED3_Pin|LED_RED4_Pin
                          |LED_AMB1_Pin|LED_AMB2_Pin|LED_AMB3_Pin|LED_AMB4_Pin
                          |LED_Green1_Pin|LED_Green2_Pin|LED_Green3_Pin|LED_Green4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG_A_Pin SEG_B_Pin SEG_C_Pin SEG_D1_Pin
                           SEG_E1_Pin SEG_F1_Pin SEG_G1_Pin SEG_D_Pin
                           SEG_E_Pin SEG_F_Pin SEG_G_Pin SEG_A1_Pin
                           SEG_B1_Pin SEG_C1_Pin */
  GPIO_InitStruct.Pin = SEG_A_Pin|SEG_B_Pin|SEG_C_Pin|SEG_D1_Pin
                          |SEG_E1_Pin|SEG_F1_Pin|SEG_G1_Pin|SEG_D_Pin
                          |SEG_E_Pin|SEG_F_Pin|SEG_G_Pin|SEG_A1_Pin
                          |SEG_B1_Pin|SEG_C1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void setAllLED() {
	  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_RED3_GPIO_Port, LED_RED3_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_RED4_GPIO_Port, LED_RED4_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_AMB1_GPIO_Port, LED_AMB1_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_AMB2_GPIO_Port, LED_AMB2_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_AMB3_GPIO_Port, LED_AMB3_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_AMB4_GPIO_Port, LED_AMB4_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_Green1_GPIO_Port, LED_Green1_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_Green2_GPIO_Port, LED_Green2_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_Green3_GPIO_Port, LED_Green3_Pin, SET) ;
	  HAL_GPIO_WritePin(LED_Green4_GPIO_Port, LED_Green4_Pin, SET) ;
}
void display7SEG1(int num) {

	    if (num > 9 || num < 0) {
	    	return;
        }

	    	const int *config = digitConfig[num];

	 HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, config[0] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, config[1] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, config[2] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, config[3] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, config[4] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, config[5] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, config[6] ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void display7SEG2(int num) {

	    if (num > 9 || num < 0) {
	    	return;
     }

	    	const int *config = digitConfig[num];
	 HAL_GPIO_WritePin(SEG_A1_GPIO_Port, SEG_A1_Pin, config[0] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_B1_GPIO_Port, SEG_B1_Pin, config[1] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_C1_GPIO_Port, SEG_C1_Pin, config[2] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_D1_GPIO_Port, SEG_D1_Pin, config[3] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_E1_GPIO_Port, SEG_E1_Pin, config[4] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_F1_GPIO_Port, SEG_F1_Pin, config[5] ? GPIO_PIN_RESET : GPIO_PIN_SET);
	 HAL_GPIO_WritePin(SEG_G1_GPIO_Port, SEG_G1_Pin, config[6] ? GPIO_PIN_RESET : GPIO_PIN_SET);

}
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
    timerRun();
    getKeyInput();

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
