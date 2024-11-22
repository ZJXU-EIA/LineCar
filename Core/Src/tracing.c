//
// Created by Nymphaea on 24-11-12.
//

#include "tracing.h"
#include <stm32f1xx_hal.h>
#include <main.h>
#include <oled.h>
#include <motor.h>
#include <servo.h>
#include <pid.h>


/**
* @author Nymphaea0726
* @brief GrayScaleSensorTest
*/
void GrayScaleTest() {
    OLED_NewFrame();
    OLED_PrintString(0, 0, GPIO_PinStateToString(Gray_1_Value), &font16x16, 0);
    OLED_PrintString(16, 0, GPIO_PinStateToString(Gray_2_Value), &font16x16, 0);
    OLED_PrintString(32, 0, GPIO_PinStateToString(Gray_3_Value), &font16x16, 0);
    OLED_PrintString(48, 0, GPIO_PinStateToString(Gray_4_Value), &font16x16, 0);
    OLED_PrintString(64, 0, GPIO_PinStateToString(Gray_5_Value), &font16x16, 0);
    OLED_PrintString(80, 0, GPIO_PinStateToString(Gray_6_Value), &font16x16, 0);
    OLED_PrintString(96, 0, GPIO_PinStateToString(Gray_7_Value), &font16x16, 0);
    OLED_ShowFrame();
}

/**
 * @author Nymphaea0726
 * @brief 预定义的灰度传感器的状态
 */
char Centre;
char Left;
char Right;
char LeftSlight;
char RightSlight;
char Cross;

/**
 * @brief 初始化灰度传感器的状态
 */

void InitializeStates() {
    Centre = (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET) ||
             (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET) ||
             (Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET);
    LeftSlight = Gray_2_Value == GPIO_PIN_SET;
    RightSlight = Gray_6_Value == GPIO_PIN_SET;
    Left = Gray_1_Value == GPIO_PIN_SET;
    Right = Gray_7_Value == GPIO_PIN_SET;
    Cross = Gray_1_Value == GPIO_PIN_SET && Gray_2_Value == GPIO_PIN_SET && Gray_3_Value == GPIO_PIN_SET &&
            Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET && Gray_6_Value == GPIO_PIN_SET &&
            Gray_7_Value == GPIO_PIN_SET;
}

/**
 * @author Nymphaea0726
 * @brief 循迹函数
 * @attention PID部分仅供逻辑参考,不确定能否正常运行,尚待测试
 */
void tracing() {
    InitializeStates();
    int left_speed;
    int right_speed;
    static int servo_angle; // 静态保存舵机角度
    static int prev_servo_angle; // 静态保存上一个舵机角度
    static int cross_Count = 0; // 静态保存十字计数
    static PIDController pid; // 创建PID控制器
    static int pid_Init = 0; // 保存PID初始化状态


    if (!pid_Init) {
        PIDController_Init(&pid, 1.0f, 0.1f, 0.1f, 0.0f);
        pid_Init = 1;
    }

    if (Cross) {
        cross_Count++;
    }

    if (cross_Count >= 14) {
        left_speed = 0;
        right_speed = 0;
    } else {
        float sensor_Weights[7] = {-3.0f,-2.0f,-1.0f,0.0f,1.0f,2.0f,3.0f}; // 定义传感器位置权重
        float sensor_Value[7]={
            Gray_1_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_2_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_3_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_4_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_5_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_6_Value == GPIO_PIN_SET ? 1.0f : 0.0f,
            Gray_7_Value == GPIO_PIN_SET ? 1.0f : 0.0f
        }; // 定义传感器值
        float sensor_sum = 0.0f; // 传感器值和
        float weighted_sum = 0.0f; // 加权和

        for (int i = 0; i < 7; i++) {
            weighted_sum += sensor_Weights[i] * sensor_Value[i];
            sensor_sum += sensor_Value[i];
        }
        float deviation = sensor_sum != 0? weighted_sum / sensor_sum : 0.0f; // 计算偏差

        // 调用PID控制器对舵机角度进行计算
        float pid_output = Servo_Angle_PID_Calc(&pid, deviation);
        servo_angle = (int)(90.0f + pid_output);
        // 限制舵机角度在55-125之间
        if (servo_angle >= 125) {
            servo_angle = 125;
        } else if (servo_angle <= 55) {
            servo_angle = 55;
        }

        // 根据误差值调整左右电机速度
        if (deviation < -1.0f) {
            left_speed = 25;
            right_speed = 40;
        } else if (deviation > 1.0f) {
            left_speed = 40;
            right_speed = 25;
        } else {
            left_speed = 30;
            right_speed = 30;
        }
    }

    prev_servo_angle = servo_angle; // 更新上一个舵机角度

    Motor_Run(Motor_L, Forward, left_speed);
    Motor_Run(Motor_R, Forward, right_speed);
    Servo(servo_angle);
}
