/********************************************************************************
* @author: ternura-xiang
* @email: ternura_xiang@foxmail.com
* @date: 2026-10-26 23:43
* @version: 1.0.0
* @description: 
* @section 更新历史
* | 版本号 | 修改说明 | 修订者 | 修订日期 |
* |----------|----------------|----------|------------|
* | v1.0.0 | 创建文档 | ternura-xiang | 2026-10-26 |
********************************************************************************/
#ifndef TEMP_SHT31_H
#define TEMP_SHT31_H

#include <stdint.h>
#include "stm32l0xx_hal.h"

/**
 *  @addtogroup SHT31
 *  @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief  I2C handle used for communication with the SHT3x sensor.
 *
 * @note   The user must define the I2C handle according to the hardware setup.
 *         For example, if I2C1 is used:
 *         @code
 *         extern I2C_HandleTypeDef hi2c1;
 *         @endcode
 *         Replace 'hi2c1' with the appropriate I2C handle name.
 */
extern I2C_HandleTypeDef hi2c1;


#define SHT3X_I2C_ADDR  0x44			/**< Default I2C address for SHT3x */
#define SHT3X_CMD_SOFT_RESET  0x30A2	/**< Soft reset command */

#define CRC8_POLYNOMIAL  0x31 			/**< CRC-8 polynomial used for data check */
#define CRC8_INIT        0xFF			/**< Initial value for CRC computation */

/**
 * @brief Measurement resolution options for SHT3x.
 */
typedef enum {
	LOW_RESOLUTION = 0x2416, 			/**< Low repeatability */
	MEDIUM_RESOLUTION = 0x240B, 		/**< Medium repeatability */
	HIGH_RESOLUTION = 0x2400 			/**< High repeatability */
} resolution_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef  __cplusplus
extern "C" {
#endif // __cplusplus

void SHT3x_Init(void);
void SHT3x_ReadTempAndHumidity(float *temperature, float *humidity,
		resolution_t resolution);

#ifdef  __cplusplus
}
#endif // __cplusplus

/**
 *  @}
 */
 
#endif //TEMP_SHT31_H
