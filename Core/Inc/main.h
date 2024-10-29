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
#define Grey_1_Pin GPIO_PIN_1
#define Grey_1_GPIO_Port GPIOA
#define Grey_2_Pin GPIO_PIN_2
#define Grey_2_GPIO_Port GPIOA
#define Grey_3_Pin GPIO_PIN_3
#define Grey_3_GPIO_Port GPIOA
#define Grey_4_Pin GPIO_PIN_4
#define Grey_4_GPIO_Port GPIOA
#define Grey_5_Pin GPIO_PIN_5
#define Grey_5_GPIO_Port GPIOA
#define Grey_6_Pin GPIO_PIN_6
#define Grey_6_GPIO_Port GPIOA
#define Grey_7_Pin GPIO_PIN_7
#define Grey_7_GPIO_Port GPIOA
#define US_Echo_Pin GPIO_PIN_10
#define US_Echo_GPIO_Port GPIOA
#define US_Trig_Pin GPIO_PIN_11
#define US_Trig_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define Grey_1 HAL_GPIO_ReadPin(Grey_1_GPIO_Port,Grey_1_Pin)
#define Grey_2 HAL_GPIO_ReadPin(Grey_2_GPIO_Port,Grey_2_Pin)
#define Grey_3 HAL_GPIO_ReadPin(Grey_3_GPIO_Port,Grey_3_Pin)
#define Grey_4 HAL_GPIO_ReadPin(Grey_4_GPIO_Port,Grey_4_Pin)
#define Grey_5 HAL_GPIO_ReadPin(Grey_5_GPIO_Port,Grey_5_Pin)
#define Grey_6 HAL_GPIO_ReadPin(Grey_6_GPIO_Port,Grey_6_Pin)
#define Grey_7 HAL_GPIO_ReadPin(Grey_7_GPIO_Port,Grey_7_Pin)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
