//
// Created by Nymphaea on 24-11-12.
//

#include "tracing.h"
#include <stm32f1xx_hal.h>
#include <main.h>
#include <oled.h>


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
// char Centre = (Gray_3_Value == GPIO_PIN_SET && Gray_4_Value == GPIO_PIN_SET && Gray_5_Value == GPIO_PIN_SET);
// char Left = (Gray_1_Value == GPIO_PIN_SET || Gray_2_Value == GPIO_PIN_SET);
// char Right = (Gray_6_Value == GPIO_PIN_SET || Gray_7_Value == GPIO_PIN_SET);

/**
 * @author Nymphaea0726
 * @brief 循迹函数
 */
// void tracing() {
//     if (Centre) {
//         // Move forward
//         // Motor(50,50);
//         // Servo(50);
//     } else if(Left) {
//         // Turn left
//         // Motor(50,0);
//         // Servo(0);
//     } else if(Right) {
//         // Turn right
//         // Motor(0,50);
//         // Servo(100);
//     }
// }
