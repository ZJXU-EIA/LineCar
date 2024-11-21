//
// Created by Nymphaea on 24-11-12.
//

#include "tracing.h"
#include <stm32f1xx_hal.h>
#include <main.h>
#include <oled.h>
#include <motor.h>
#include <servo.h>


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

/**
 * @brief 初始化灰度传感器的状态
 */

void InitializeStates() {
    Centre = (Gray_3_Value == GPIO_PIN_SET&&Gray_4_Value == GPIO_PIN_SET&&Gray_5_Value == GPIO_PIN_SET)||
        (Gray_3_Value == GPIO_PIN_SET&&Gray_4_Value == GPIO_PIN_SET)||
        (Gray_4_Value == GPIO_PIN_SET&&Gray_5_Value == GPIO_PIN_SET)||
        (Gray_3_Value == GPIO_PIN_SET)||
        (Gray_4_Value == GPIO_PIN_SET)||
        (Gray_5_Value == GPIO_PIN_SET);
    LeftSlight = Gray_2_Value == GPIO_PIN_SET;
    RightSlight = Gray_6_Value == GPIO_PIN_SET;
    Left = Gray_1_Value == GPIO_PIN_SET;
    Right = Gray_7_Value == GPIO_PIN_SET;
}

/**
 * @author Nymphaea0726
 * @brief 循迹函数
 */
void tracing() {
    InitializeStates();
    int left_speed = 30;
    int right_speed = 30;
    static int servo_angle; // 静态保存舵机角度
    static int prev_servo_angle = 90; // 静态保存上一个舵机角度

    if (Centre) {
        // Move forward
        left_speed = 30;
        right_speed = 30;
        if (prev_servo_angle < 90) {
            servo_angle = 90 + 5; // 舵机向右旋转小角度
        } else if (prev_servo_angle > 90) {
            servo_angle = 90 - 5; // 舵机向左旋转小角度
        } else {
            servo_angle = 90; // 保持直行
        }
    } else if (Left || LeftSlight) {
        // 左转或向左微调
        left_speed = 25;
        right_speed = 65;
        servo_angle = Left ? 55 : 75; // 设置舵机左转角度或左转小角度
    } else if (Right || RightSlight) {
        // 右转或向右微调
        left_speed = 65;
        right_speed = 25;
        servo_angle = Right ? 125 : 105; // 设置舵机右转角度或右转小角度
    }

    prev_servo_angle = servo_angle; // 更新上一个舵机角度

    Motor_Run(Motor_L, Forward, left_speed);
    Motor_Run(Motor_R, Forward, right_speed);
    Servo(servo_angle);
}
