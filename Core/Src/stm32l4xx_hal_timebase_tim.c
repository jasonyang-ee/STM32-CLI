
/**
 ******************************************************************************
 * @file    stm32l4xx_hal_timebase_TIM.c
 * @brief   HAL time base based on the hardware TIM.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"

TIM_HandleTypeDef htim1;

/**
 * @brief  This function configures the TIM1 as a time base source.
 *         The time source is configured  to have 1ms time base with a dedicated
 *         Tick interrupt priority.
 * @note   This function is called  automatically at the beginning of program
 * after reset by HAL_Init() or at any time when clock is configured, by
 * HAL_RCC_ClockConfig().
 * @param  TickPriority: Tick interrupt priority.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    RCC_ClkInitTypeDef clkconfig;
    uint32_t uwTimclock = 0;
    uint32_t uwPrescalerValue = 0;
    uint32_t pFLatency;

    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, TickPriority, 0);

    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

    __HAL_RCC_TIM1_CLK_ENABLE();

    HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

    uwTimclock = HAL_RCC_GetPCLK2Freq();

    uwPrescalerValue = (uint32_t)((uwTimclock / 1000000U) - 1U);

    htim1.Instance = TIM1;

    /* Initialize TIMx peripheral as follow:
    + Period = [(TIM1CLK/1000) - 1]. to have a (1/1000) s time base.
    + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
    + ClockDivision = 0
    + Counter direction = Up
    */
    htim1.Init.Period = (1000000U / 1000U) - 1U;
    htim1.Init.Prescaler = uwPrescalerValue;
    htim1.Init.ClockDivision = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;

    if (HAL_TIM_Base_Init(&htim1) == HAL_OK) {
        return HAL_TIM_Base_Start_IT(&htim1);
    }

    return HAL_ERROR;
}

/**
 * @brief  Suspend Tick increment.
 * @note   Disable the tick increment by disabling TIM1 update interrupt.
 * @param  None
 * @retval None
 */
void HAL_SuspendTick(void) { __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_UPDATE); }

/**
 * @brief  Resume Tick increment.
 * @note   Enable the tick increment by Enabling TIM1 update interrupt.
 * @param  None
 * @retval None
 */
void HAL_ResumeTick(void) { __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE); }
