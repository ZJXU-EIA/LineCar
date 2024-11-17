//
// Created by Nymphaea on 24-11-13.
//

#ifndef MOTOR_H
#define MOTOR_H

typedef enum {
    Motor_L,
    Motor_R
} Motor;

typedef enum {
    Forward,
    Backward
} Direction;

void Motor_PWM_Init();
void PWM_Test();
void Motor_Run(Motor motor, uint8_t direction, uint8_t speed);

#endif //MOTOR_H
