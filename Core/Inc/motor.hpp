//
// Created by Nymphaea on 24-11-27.
//

#ifndef MOTOR_H
#define MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_tim.h>
void Motor_PWM_Init();

#ifdef __cplusplus

class Motor {
public:
    enum Direction {
        Forward,
        Backward
    };

    Motor(GPIO_TypeDef* in1Port, uint16_t in1Pin, GPIO_TypeDef* in2Port, uint16_t in2Pin, TIM_HandleTypeDef* htim,uint32_t channel) {
        this->in1Port = in1Port;
        this->in1Pin = in1Pin;
        this->in2Port = in2Port;
        this->in2Pin = in2Pin;
        this->htim = htim;
        this->channel = channel;
    }

    void Run(Direction direction,uint8_t speed);

private:
    GPIO_TypeDef* in1Port;
    uint16_t in1Pin;
    GPIO_TypeDef* in2Port;
    uint16_t in2Pin;
    TIM_HandleTypeDef* htim;
    uint32_t channel;
};
#endif

#ifdef __cplusplus
}
#endif

#endif //MOTOR_H
