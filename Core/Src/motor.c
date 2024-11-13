#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include <motor.h>


/*
 * @Author Nymphaea0726
 * @Description 初始化电机PWM
 */
void Motor_PWM_Init() {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

/*
 * Test the PWM
 * @Author Nymphaea0726
 * @Description 测试PWM功能,产生1k频率的PWM波形,占空比从0%到100%
 */
void PWM_Test() {
    for(int i=0; i <1000; i++) {
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, i);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, i);
        HAL_Delay(1);
    }
}


/*
 * @Author Nymphaea0726
 * @Description 控制电机运行
 * @param motor 电机编号 Motor_L:左电机 Motor_R:右电机
 * @param direction 方向 1:正转 0:反转
 * @param speed 速度 0-100 （占空比:0% - 100%）
 */
void Motor_Run(Motor motor, uint8_t direction, uint8_t speed) {
    if (motor == Motor_L) { // Left motor
        if (direction == 1) { // Forward
            HAL_GPIO_WritePin(L298N_IN1_GPIO_Port, L298N_IN1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(L298N_IN2_GPIO_Port, L298N_IN2_Pin, GPIO_PIN_RESET);
        } else { // Reverse
            HAL_GPIO_WritePin(L298N_IN1_GPIO_Port, L298N_IN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(L298N_IN2_GPIO_Port, L298N_IN2_Pin, GPIO_PIN_SET);
        }
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, speed*10);
    } else if (motor == Motor_R) { // Right motor
        if (direction == 1) { // Forward
            HAL_GPIO_WritePin(L298N_IN3_GPIO_Port, L298N_IN3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(L298N_IN4_GPIO_Port, L298N_IN4_Pin, GPIO_PIN_RESET);
        } else { // Reverse
            HAL_GPIO_WritePin(L298N_IN3_GPIO_Port, L298N_IN3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(L298N_IN4_GPIO_Port, L298N_IN4_Pin, GPIO_PIN_SET);
        }
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, speed*10);
    }
}