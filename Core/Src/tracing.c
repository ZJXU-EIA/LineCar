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
char LeftLight;
char RightLight;

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
    LeftLight = Gray_2_Value == GPIO_PIN_SET;
    RightLight = Gray_6_Value == GPIO_PIN_SET;
    Left = Gray_1_Value == GPIO_PIN_SET;
    Right = Gray_7_Value == GPIO_PIN_SET;
}

/**
 * @author Nymphaea0726
 * @brief 循迹函数
 */
void tracing() {
    InitializeStates();
    if (Centre) {
        // Move forward
        Motor_Run(Motor_L, 1, 30);
        Motor_Run(Motor_R, 1, 30);
        Servo(90);
    } else if (Left) {
        // Turn left
        Motor_Run(Motor_L, 1, 25);
        Motor_Run(Motor_R, 1, 65);
        Servo(55);
    } else if (Right) {
        // Turn right
        Motor_Run(Motor_L, 1, 65);
        Motor_Run(Motor_R, 1, 25);
        Servo(125);
    } else if (LeftLight) {
        // Slight left adjustment
        Motor_Run(Motor_L, 1, 25);
        Motor_Run(Motor_R, 1, 65);
        Servo(75);
    } else if (RightLight) {
        // Slight right adjustment
        Motor_Run(Motor_L, 1, 65);
        Motor_Run(Motor_R, 1, 25);
        Servo(105);
    } else {
        Motor_Run(Motor_L, 1, 30);
        Motor_Run(Motor_R, 1, 30);
        Servo(90);
    }
}
