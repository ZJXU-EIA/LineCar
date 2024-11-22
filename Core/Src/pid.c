//
// Created by Nymphaea on 24-11-22.
//
#include "pid.h"

void PIDController_Init(PIDController *pid, float Kp, float Ki, float Kd, float Setpoint) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->Setpoint = Setpoint;
    pid->Integral = 0;
    pid->LastError = 0;
}

float Servo_Angle_PID_Calc(PIDController *pid, float angle) {
    float error = pid->Setpoint - angle;
    pid->Integral += error;
    float derivative = error - pid->LastError;
    float output = pid->Kp * error + pid->Ki * pid->Integral + pid->Kd * derivative;
    pid->LastError = error;
    return output;
}