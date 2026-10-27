/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level
   * HT1621B 空闲状态要求:
   *   /CS  = HIGH (片选无效)
   *   /WR  = HIGH (时钟空闲高电平)
   *   DATA = LOW  (数据空闲低电平)
   */
  HAL_GPIO_WritePin(GPIOA, WR_Pin|CS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, DAT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : WR_Pin CS_Pin DAT_Pin */
  GPIO_InitStruct.Pin = WR_Pin|CS_Pin|DAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  /* GPIO_SPEED_FREQ_LOW = 2MHz, 但 HT1621 最大 2.1MHz,
   * 改用 MEDIUM (25MHz) 确保边沿质量, HT1621 内部有下拉, 实际速率由软件延时决定
   */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
