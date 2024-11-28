//
// Created by Nymphaea on 24-11-14.
//

#include "servo.hpp"
#include <tim.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_tim.h>

/**
 * @author Nymphaea0726
 * @brief Initialize the PWM for the servo
 */
void Servo_PWM_Init() {
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

/**
 * @author Nymphaea0726
 * @brief Move the servo to a specific angle
 * @param angle The angle to move the servo to
 */
void Servo::Move(int angle) {
    // 1. Calculate the pulse width
    int pulse_width = 500 + (angle * 2000 / 180);
    // 2. Set the pulse width
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pulse_width);
    // 3. Wait for the servo to move
    HAL_Delay(20);
}
