/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define Button1_Pin GPIO_PIN_13
#define Button1_GPIO_Port GPIOC
#define Button2_Pin GPIO_PIN_14
#define Button2_GPIO_Port GPIOC
#define Button3_Pin GPIO_PIN_15
#define Button3_GPIO_Port GPIOC
#define LED_RED1_Pin GPIO_PIN_1
#define LED_RED1_GPIO_Port GPIOA
#define LED_RED2_Pin GPIO_PIN_2
#define LED_RED2_GPIO_Port GPIOA
#define LED_RED3_Pin GPIO_PIN_3
#define LED_RED3_GPIO_Port GPIOA
#define LED_RED4_Pin GPIO_PIN_4
#define LED_RED4_GPIO_Port GPIOA
#define LED_AMB1_Pin GPIO_PIN_5
#define LED_AMB1_GPIO_Port GPIOA
#define LED_AMB2_Pin GPIO_PIN_6
#define LED_AMB2_GPIO_Port GPIOA
#define LED_AMB3_Pin GPIO_PIN_7
#define LED_AMB3_GPIO_Port GPIOA
#define SEG_A_Pin GPIO_PIN_0
#define SEG_A_GPIO_Port GPIOB
#define SEG_B_Pin GPIO_PIN_1
#define SEG_B_GPIO_Port GPIOB
#define SEG_C_Pin GPIO_PIN_2
#define SEG_C_GPIO_Port GPIOB
#define SEG_D1_Pin GPIO_PIN_11
#define SEG_D1_GPIO_Port GPIOB
#define SEG_E1_Pin GPIO_PIN_12
#define SEG_E1_GPIO_Port GPIOB
#define SEG_F1_Pin GPIO_PIN_13
#define SEG_F1_GPIO_Port GPIOB
#define SEG_G1_Pin GPIO_PIN_14
#define SEG_G1_GPIO_Port GPIOB
#define LED_AMB4_Pin GPIO_PIN_8
#define LED_AMB4_GPIO_Port GPIOA
#define LED_Green1_Pin GPIO_PIN_9
#define LED_Green1_GPIO_Port GPIOA
#define LED_Green2_Pin GPIO_PIN_10
#define LED_Green2_GPIO_Port GPIOA
#define LED_Green3_Pin GPIO_PIN_11
#define LED_Green3_GPIO_Port GPIOA
#define LED_Green4_Pin GPIO_PIN_12
#define LED_Green4_GPIO_Port GPIOA
#define SEG_D_Pin GPIO_PIN_3
#define SEG_D_GPIO_Port GPIOB
#define SEG_E_Pin GPIO_PIN_4
#define SEG_E_GPIO_Port GPIOB
#define SEG_F_Pin GPIO_PIN_5
#define SEG_F_GPIO_Port GPIOB
#define SEG_G_Pin GPIO_PIN_6
#define SEG_G_GPIO_Port GPIOB
#define SEG_A1_Pin GPIO_PIN_7
#define SEG_A1_GPIO_Port GPIOB
#define SEG_B1_Pin GPIO_PIN_8
#define SEG_B1_GPIO_Port GPIOB
#define SEG_C1_Pin GPIO_PIN_9
#define SEG_C1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
