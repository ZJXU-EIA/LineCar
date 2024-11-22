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
 * @attention PID部分仅供逻辑参考,不确定能否使用
 */
void tracing() {
    InitializeStates();
    int left_speed = 30;
    int right_speed = 30;
    static int servo_angle; // 静态保存舵机角度
    static int prev_servo_angle; // 静态保存上一个舵机角度
    static int crossCount = 0; // 静态保存十字计数
    static PIDController pid; // 静态保存PID控制器
    static int pid_Init = 0; // 静态保存PID初始化状态

    if (!pid_Init) {
        PIDController_Init(&pid, 1.0f, 0.1f, 0.1f, 90.0f);
        pid_Init = 1;
    }

    if (Cross) {
        crossCount++;
    }

    if (crossCount >= 14) {
        left_speed = 0;
        right_speed = 0;
    } else {
        if (Centre) {
            // Move forward
            left_speed = 30;
            right_speed = 30;
        } else if (Left || LeftSlight) {
            // Turn left or slight left adjustment
            left_speed = Left ? 20 : 25;
            right_speed = Left ? 40 : 35;
        } else if (Right || RightSlight) {
            // Turn right or slight right adjustment
            left_speed = Right ? 40 : 35;
            right_speed = Right ? 20 : 25;
        }
    }

    // 调用PID控制器对舵机角度进行计算
    float measure_servo = (float) (servo_angle);
    float output = Servo_Angle_PID_Calc(&pid, measure_servo);
    servo_angle = (int) (measure_servo + output);

    // 限制舵机角度在55-125之间
    if (servo_angle >= 125) {
        servo_angle = 125;
    } else if (servo_angle <= 55) {
        servo_angle = 55;
    }

    prev_servo_angle = servo_angle; // 更新上一个舵机角度

    Motor_Run(Motor_L, Forward, left_speed);
    Motor_Run(Motor_R, Forward, right_speed);
    Servo(servo_angle);
}
