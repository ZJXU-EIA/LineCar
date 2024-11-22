//
// Created by Nymphaea on 24-11-22.
//

#ifndef PID_H
#define PID_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float Setpoint;
    float Integral;
    float LastError;
} PIDController;
void PIDController_Init(PIDController *pid, float Kp, float Ki, float Kd, float Setpoint);
float Servo_Angle_PID_Calc(PIDController *pid, float angle);

#endif //PID_H
