/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.hpp
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
char* GPIO_PinStateToString(GPIO_PinState state);
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Motor_L_Pin GPIO_PIN_2
#define Motor_L_GPIO_Port GPIOA
#define Motor_R_Pin GPIO_PIN_3
#define Motor_R_GPIO_Port GPIOA
#define L298N_IN1_Pin GPIO_PIN_4
#define L298N_IN1_GPIO_Port GPIOA
#define L298N_IN2_Pin GPIO_PIN_5
#define L298N_IN2_GPIO_Port GPIOA
#define L298N_IN3_Pin GPIO_PIN_6
#define L298N_IN3_GPIO_Port GPIOA
#define L298N_IN4_Pin GPIO_PIN_7
#define L298N_IN4_GPIO_Port GPIOA
#define Servo_Pin GPIO_PIN_1
#define Servo_GPIO_Port GPIOB
#define Gray_7_Pin GPIO_PIN_12
#define Gray_7_GPIO_Port GPIOB
#define Gray_6_Pin GPIO_PIN_13
#define Gray_6_GPIO_Port GPIOB
#define Gray_5_Pin GPIO_PIN_14
#define Gray_5_GPIO_Port GPIOB
#define Gray_4_Pin GPIO_PIN_15
#define Gray_4_GPIO_Port GPIOB
#define Gray_3_Pin GPIO_PIN_9
#define Gray_3_GPIO_Port GPIOA
#define Gray_2_Pin GPIO_PIN_10
#define Gray_2_GPIO_Port GPIOA
#define Gray_1_Pin GPIO_PIN_12
#define Gray_1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define Gray_1_Value HAL_GPIO_ReadPin(Gray_1_GPIO_Port,Gray_1_Pin)
#define Gray_2_Value HAL_GPIO_ReadPin(Gray_2_GPIO_Port,Gray_2_Pin)
#define Gray_3_Value HAL_GPIO_ReadPin(Gray_3_GPIO_Port,Gray_3_Pin)
#define Gray_4_Value HAL_GPIO_ReadPin(Gray_4_GPIO_Port,Gray_4_Pin)
#define Gray_5_Value HAL_GPIO_ReadPin(Gray_5_GPIO_Port,Gray_5_Pin)
#define Gray_6_Value HAL_GPIO_ReadPin(Gray_6_GPIO_Port,Gray_6_Pin)
#define Gray_7_Value HAL_GPIO_ReadPin(Gray_7_GPIO_Port,Gray_7_Pin)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
