[![Build Binary](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build-all.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build-all.yml)

# LED Class Use Instruction

Project Using STM32L432KC as Example. Test hardware is NUCLEO-L432KC.

## UART
- Send confirmation using `HAL_UART_TxCpltCallback`
- Receiving DMA using `HAL_UARTEx_RxEventCallback` with interrupt turned on.
- IRQ:
```c++
	void DMA1_Channel6_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart2_rx); }
	void USART2_IRQHandler(void) { HAL_UART_IRQHandler(&huart2); }
```
- In `main`:
```c++
	MX_USART2_UART_Init();
	serialCOM.setPort(&huart2);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, serialCOM.m_rx_data, BUFFER_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
```

## DMA

- `MX_DMA_Init()` position matters, must put in front of UART Init but after GPIO Init.
- DMA for Uart RX for "byte" "normal mode"
- `__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT)` is required to avoid half transfer complete interrupt collision.
- Reciving will trigger `HAL_UARTEx_RxEventCallback()`. Arrival action defined in here. 
- In `HAL_UARTEx_RxEventCallback()` to restart DMA:
```c++
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, serialCOM.m_rx_data, BUFFER_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
```


## CLI

- Before `main`:
```c++
	#include "lwshell.h"
```

- In `main`:
```c++
	lwshell_init();
	lwshell_register_cmd("testCMD", testCMD, "turn on");
```

- In `HAL_UARTEx_RxEventCallback()`
```c++
	lwshell_input(&serialCOM.m_rx_data, Size);
```

- Define the command excution functions with return value `int32_t`. MUST `return;`:
```c++
	int32_t testCMD(int32_t argc, char** argv){
		led_user.toggle();
		serialCOM.send("LED Turned ON\n");
		return 0;
	}
```

- command function will finish first and then return back to `lwshell_input()`.


## SerialCOM

- Using Tx complete callback to tag completion
```c++
	void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
		serialCOM.setTxComplete();
	}
```


## C++ Host
- Optionally, declear `extern object` in `instance.h` to allow object sharing.
- Only define object init in `main.cpp`.
- Hal Timebase using TIM16. RTOS using systick





## Free RTOS

API: https://www.freertos.org/a00106.html

- Class `Thread` is used to hose RTOS task creation and defination.
- All `instances` object must be configured and initialized before `osKernelStart()`.
- `#define configSUPPORT_STATIC_ALLOCATION` set to false.







### Side Note

Use Regular Expression: `` /\*.*/ `` to remove HAL comments in `main` and `it`


