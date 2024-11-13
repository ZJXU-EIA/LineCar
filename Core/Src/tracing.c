//
// Created by Nymphaea on 24-11-12.
//

#include "tracing.h"
#include <stm32f1xx_hal.h>
#include <main.h>
#include <oled.h>
#include <motor.h>


/**
* @author Nymphaea0726
* @brief GrayScaleSensorTest
*/
void GrayScaleTest() {
    OLED_NewFrame();
    OLED_PrintString(0,0,GPIO_PinStateToString(Gray_1_Value),&font16x16,0);
    OLED_PrintString(16,0,GPIO_PinStateToString(Gray_2_Value),&font16x16,0);
    OLED_PrintString(32,0,GPIO_PinStateToString(Gray_3_Value),&font16x16,0);
    OLED_PrintString(48,0,GPIO_PinStateToString(Gray_4_Value),&font16x16,0);
    OLED_PrintString(64,0,GPIO_PinStateToString(Gray_5_Value),&font16x16,0);
    OLED_PrintString(80,0,GPIO_PinStateToString(Gray_6_Value),&font16x16,0);
    OLED_PrintString(96,0,GPIO_PinStateToString(Gray_7_Value),&font16x16,0);
    OLED_ShowFrame();
}

/**
 * @author Nymphaea0726
 * @brief 预定义的灰度传感器的状态
 */
char Centre;
char Left;
char Right;

void InitializeStates() {
    Centre = (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET);
    Left = (Gray_1_Value == GPIO_PIN_SET || Gray_2_Value == GPIO_PIN_SET);
    Right = (Gray_6_Value == GPIO_PIN_SET || Gray_7_Value == GPIO_PIN_SET);
}

/**
 * @author Nymphaea0726
 * @brief 循迹函数
 * @attention 该函数部分目前仍为伪代码，请勿直接使用。
 */
void tracing() {
    if (Centre) {
        Motor_Run(Motor_L, 1, 50);
        Motor_Run(Motor_R, 1, 50);
    } else if(Left) {
        // Turn left
        Motor_Run(Motor_L, 1, 30);
        Motor_Run(Motor_R, 1, 70);
        // Servo(0);
    } else if(Right) {
        // Turn right
        Motor_Run(Motor_L, 1, 70);
        Motor_Run(Motor_R, 1, 30);
        // Servo(100);
    }
}
