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
#include "HT1621.h"
#include "gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief 数字映射 */
const uint8_t num[] = {	Digit_0, Digit_1, Digit_2, Digit_3,
						Digit_4, Digit_5, Digit_6, Digit_7,
						Digit_8, Digit_9};

/** @brief HT1621B 命令定义 */
#define HT1621_MODE_CMD          0x80U
#define HT1621_MODE_WRITE        0xA0U

#define HT1621_CMD_SYS_EN        0x01U
#define HT1621_CMD_LCD_ON        0x03U
#define HT1621_CMD_LCD_OFF       0x02U
#define HT1621_CMD_BIAS_1_3_4COM 0x29U

/** @brief HT1621B RAM: 32 addresses, 4 bits per address */
#define HT1621_RAM_BYTES       32U
#define HT1621_LCD_FIELD_BYTES 5U

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
 * @brief 传输位 (MSB first)
 * @param data 要传输的数据。
 * @param bit_count 要传输的位数。
 */
static void HT1621_WriteBits(uint8_t data, uint8_t bit_count)
{
    uint8_t i;

    for (i = 0U; i < bit_count; ++i)
    {
        if ((data & 0x80U) != 0U)
        {
            HT1621_SDA_SET;
        }
        else
        {
            HT1621_SDA_RESET;
        }

        HT1621_SCK_RESET;
        HT1621_DELAY_CYCLE();

        HT1621_SCK_SET;
        HT1621_DELAY_CYCLE();

        data <<= 1U;
    }
}

/**
 * @brief 传输一个六位 LCD RAM 地址。
 * @param address RAM 地址。
 */
static void HT1621_WriteAddress(uint8_t address)
{
    HT1621_WriteBits((uint8_t)(address << 2U), 6U);
}

/**
 * @brief 初始化 HT1621B 并清空屏幕
 */
void LCD_Init(void)
{
	HT1621_CS_RESET;
	HT1621_SCK_SET;
	HT1621_SDA_SET;

	HT1621_WriteBits(HT1621_MODE_CMD, 3U);
	HT1621_WriteBits(HT1621_CMD_SYS_EN, 9U);
	HT1621_WriteBits(HT1621_CMD_BIAS_1_3_4COM, 9U);
	HT1621_WriteBits(HT1621_CMD_LCD_ON, 9U);

	HT1621_CS_SET;

	LCD_Clear();
}

/**
 * @brief 清空屏幕
 */
void LCD_Clear(void)
{
	HT1621_CS_RESET;
	HT1621_WriteBits(HT1621_MODE_WRITE, 3U);
	HT1621_WriteAddress(9U);
	for (uint8_t i = 0U; i < HT1621_LCD_FIELD_BYTES; ++i)
	{

		HT1621_WriteBits(Off, 8U);
	}
	HT1621_CS_SET;
}

/**
 * @brief 显示数字及温湿度部分
 *
 * @param value 数值
 * @param display_type 显示类型
 */
void LCD_Display_value(float value, HT1621_DisplayType_t display_type)
{
	int value_int;
	if (value >= 0)
	{
		value_int = (int)((value + 0.05f) * 10.0);
	}
	else
	{
		value_int = (int)((-value + 0.05f) * 10.0);
	}

    uint8_t data[HT1621_LCD_FIELD_BYTES] =
    {
        (uint8_t)(num[(value_int/100)%10]),
        (uint8_t)(num[(value_int/10)%10]),
        (uint8_t)(num[value_int%10] | Dot),
        0x00U,
    };

	if (value < 0)	data[1] |= Minus;			// 负号
	if (value_int >= 1000)	data[0] |= Num_1;	// 100以上
	if (display_type == HT1621_DISPLAY_TEMPERATURE)		// 温度&湿度符号
	{
		data[3] = C;
	}
	else if (display_type == HT1621_DISPLAY_HUMIDITY)
	{
		data[3] = Per;
	}

	HT1621_CS_RESET;
    HT1621_WriteBits(HT1621_MODE_WRITE, 3U);
	HT1621_WriteAddress(9U);
    for (uint8_t i = 0U; i < HT1621_LCD_FIELD_BYTES-1; ++i)
    {

        HT1621_WriteBits(data[i], 8U);
    }
    HT1621_CS_SET;
}

void LCD_Display_power(uint8_t power)
{
	uint8_t data;
	switch (power)
	{
		case 0U:
			data = 0x80U;	// (S9)
			break;
		case 1U:
			data = 0xC0U;	// (S9|S10)
			break;
		case 2U:
			data = 0xD0U;	// (S9|S10|S11)
			break;
		case 3U:
			data = 0xF0U;	// (S9|S10|S11|S12)
			break;
		default:
			data = 0x00U;
			break;
	}

	HT1621_CS_RESET;
	HT1621_WriteBits(HT1621_MODE_WRITE, 3U);
	HT1621_WriteAddress(17U);
	HT1621_WriteBits(data, 8U);
	HT1621_CS_SET;
}
