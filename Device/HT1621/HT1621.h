/********************************************************************************
* @author: ternura-xiang
* @email: ternura_xiang@foxmail.com
* @date: 2026-10-26 10:43
* @version: 1.0.0
* @description:
* @section 更新历史
* | 版本号 | 修改说明 | 修订者 | 修订日期 |
* |----------|----------------|----------|------------|
* | v1.0.0 | 创建文档 | ternura-xiang | 2026-10-26 |
********************************************************************************/
#ifndef HT1621_H
#define HT1621_H

#include <stdint.h>

/**
 *  @addtogroup HT1621
 *  @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief HT1621B GPIO 配置 */
#define HT1621_GPIOx       GPIOA
#define HT1621_CS_Pin      GPIO_PIN_9
#define HT1621_SDA_Pin     GPIO_PIN_10
#define HT1621_SCK_Pin     GPIO_PIN_8

#define HT1621_CS_SET      HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_CS_Pin, GPIO_PIN_SET)
#define HT1621_CS_RESET    HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_CS_Pin, GPIO_PIN_RESET)

#define HT1621_SDA_SET     HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_SDA_Pin, GPIO_PIN_SET)
#define HT1621_SDA_RESET   HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_SDA_Pin, GPIO_PIN_RESET)

#define HT1621_SCK_SET     HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_SCK_Pin, GPIO_PIN_SET)
#define HT1621_SCK_RESET   HAL_GPIO_WritePin(HT1621_GPIOx, HT1621_SCK_Pin, GPIO_PIN_RESET)

/** @brief GPIO 位bang 延时 */
#if defined(__GNUC__)
#define HT1621_DELAY_CYCLE() __asm__ volatile ("nop")
#else
#define HT1621_DELAY_CYCLE() do { __NOP(); } while (0)
#endif

/**
 * @brief LCD 显示类型
 */
typedef enum
{
    HT1621_DISPLAY_TEMPERATURE = 0,		// 温度
    HT1621_DISPLAY_HUMIDITY = 1			// 湿度
} HT1621_DisplayType_t;

/**
 * @brief LCD 显示段数据
 */
typedef enum
{
    Digit_0 = 0x5F,
    Digit_1 = 0x06,
    Digit_2 = 0x6B,
    Digit_3 = 0x2F,
    Digit_4 = 0x36,
    Digit_5 = 0x3D,
    Digit_6 = 0x7D,
    Digit_7 = 0x07,
    Digit_8 = 0x7F,
    Digit_9 = 0x3F,

    Dot   = 0x80,
    Minus = 0x80,
    Num_1 = 0x80,

    Per = 0x10,
    C   = 0x20,

    S5  = 0x08,
    S6  = 0x04,
    S7  = 0x02,
    S8  = 0x01,
    S9  = 0x80,
    S10 = 0x40,
    S11 = 0x10,
    S12 = 0x20,

    LcdDisplay_On = 0xFF,
    Off           = 0x00
} HT1621_Data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化 HT1621B 并清空屏幕
 */
void LCD_Init(void);

/**
 * @brief 清空屏幕
 */
void LCD_Clear(void);

/**
 * @brief 显示数字及温湿度部分
 *
 * @param value 数值
 * @param display_type 显示类型
 */
void LCD_Display_value(float value, HT1621_DisplayType_t display_type);

void LCD_Display_power(uint8_t power);

#ifdef __cplusplus
}
#endif

/**
 *  @}
 */

#endif /* HT1621_H */
