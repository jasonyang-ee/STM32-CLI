
/**
 ******************************************************************************
 * @file    stm32l4xx_it.c
 * @brief   Interrupt Service Routines.
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

#include "stm32l4xx_it.h"

#include "main.h"

extern DMA_HandleTypeDef hdma_tim2_up;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Prefetch fault, memory access fault.
 */
void BusFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
    while (1) {
    }
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) { HAL_IncTick(); }

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }

/**
 * @brief This function handles DMA1 channel6 global interrupt.
 */
void DMA1_Channel6_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart2_rx); }

/**
 * @brief This function handles USART2 global interrupt.
 */
void USART2_IRQHandler(void) { HAL_UART_IRQHandler(&huart2); }
