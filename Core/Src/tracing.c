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
    int servo_angle = 90;

    if (Centre) {
        // Move forward
        left_speed = 30;
        right_speed = 30;
        servo_angle = 90;
    } else if (Left) {
        // Turn left
        left_speed = 25;
        right_speed = 65;
        servo_angle = 55;
    } else if (Right) {
        // Turn right
        left_speed = 65;
        right_speed = 25;
        servo_angle = 125;
    } else if (LeftSlight) {
        // Slight left adjustment
        left_speed = 25;
        right_speed = 65;
        servo_angle = 75;
    } else if (RightSlight) {
        // Slight right adjustment
        left_speed = 65;
        right_speed = 25;
        servo_angle = 105;
    }

    Motor_Run(Motor_L, Forward, left_speed);
    Motor_Run(Motor_R, Forward, right_speed);
    Servo(servo_angle);
    HAL_Delay(100);
}
