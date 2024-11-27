//
// Created by Nymphaea on 24-11-14.
//

#ifndef SERVO_H
#define SERVO_H



#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_tim.h>
void Servo_PWM_Init();

#ifdef __cplusplus
class Servo {
public:
    Servo(TIM_HandleTypeDef* htim, uint32_t channel) {
        this->htim = htim;
        this->channel = channel;
    }

    void Move(int angle);

private:
    TIM_HandleTypeDef* htim;
    uint32_t channel;
};

#endif

#ifdef __cplusplus
}
#endif



#endif //SERVO_H
