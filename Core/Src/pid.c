//
// Created by Nymphaea on 24-11-22.
//
#include "pid.h"

/**
 * @brief 初始化PIDController
 * @author Nymphea0726
 * @param pid PID控制器结构体
 * @param Kp 比例系数
 * @param Ki 积分系数
 * @param Kd 微分系数
 * @param Setpoint 设定值
 * @attention Setpoint为设定值,即期望值,即PID控制器的目标值
 * @return void
 */
void PIDController_Init(PIDController *pid, float Kp, float Ki, float Kd, float Setpoint) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->Setpoint = Setpoint;
    pid->Integral = 0;
    pid->LastError = 0;
}

/**
 * @brief 计算由PID控制器计算出的舵机值
 * @param pid PID控制器结构体
 * @param deviation 误差值
 * @return float 舵机值
 */
float Servo_Angle_PID_Calc(PIDController *pid, float deviation) {
    float error = pid->Setpoint - deviation;
    pid->Integral += error;
    float derivative = error - pid->LastError;
    float output = pid->Kp * error + pid->Ki * pid->Integral + pid->Kd * derivative;
    pid->LastError = error;
    return output;
}