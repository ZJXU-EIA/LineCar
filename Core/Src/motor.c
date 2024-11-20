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
 * @param direction 方向 0:正转 1:反转
 * @param speed 速度 0-100 （占空比:0% - 100%）
 */
/*
 * @Author Nymphaea0726
 * @Description 控制电机运行
 * @param motor 电机编号 Motor_L:左电机 Motor_R:右电机
 * @param direction 方向 0:正转 1:反转
 * @param speed 速度 0-100 （占空比:0% - 100%）
 */
void Motor_Run(Motor motor, Direction direction, uint8_t speed) {
    GPIO_TypeDef* IN1_Port;
    uint16_t IN1_Pin;
    GPIO_TypeDef* IN2_Port;
    uint16_t IN2_Pin;
    uint32_t TIM_Channel;

    if (motor == Motor_L) {
        IN1_Port = L298N_IN1_GPIO_Port;
        IN1_Pin = L298N_IN1_Pin;
        IN2_Port = L298N_IN2_GPIO_Port;
        IN2_Pin = L298N_IN2_Pin;
        TIM_Channel = TIM_CHANNEL_3;
    } else {
        IN1_Port = L298N_IN3_GPIO_Port;
        IN1_Pin = L298N_IN3_Pin;
        IN2_Port = L298N_IN4_GPIO_Port;
        IN2_Pin = L298N_IN4_Pin;
        TIM_Channel = TIM_CHANNEL_4;
    }

    if (direction == Forward) {
        HAL_GPIO_WritePin(IN1_Port, IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_Port, IN2_Pin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(IN1_Port, IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_Port, IN2_Pin, GPIO_PIN_SET);
    }

    __HAL_TIM_SET_COMPARE(&htim2, TIM_Channel, speed * 10);
}