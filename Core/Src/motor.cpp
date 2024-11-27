//
// Created by Nymphaea on 24-11-27.
//

#include "motor.hpp"
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>
#include <tim.h>

void Motor_PWM_Init() {
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
}

void Motor::Run(Direction direction, uint8_t speed) {
    if (direction == Forward) {
        HAL_GPIO_WritePin(in1Port, in1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(in2Port, in2Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(in1Port, in1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(in2Port, in2Pin, GPIO_PIN_RESET);
    }
    __HAL_TIM_SET_COMPARE(htim, channel, speed * 10);
}