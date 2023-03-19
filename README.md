[![Build Binary](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build-all.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build-all.yml)



# 1. Command Line Interface Under FreeRTOS Instruction

Project Using STM32L432KC as Example. Test hardware is NUCLEO-L432KC.

STM32CubeMX File Included.

Credit to `lwshell`: https://github.com/MaJerle/lwshell


## 1.1. Build This Project

```
docker run -v "{Your_Local_Full_Path}":"/home" jasonyangee/stm32_ubuntu:latest https://github.com/jasonyang-ee/STM32-CLI
```
![Run](doc/img/run.gif)

## 1.1. C++
Project using C++ fake OOP method. Each feature class has attempted to be stand-alone where disabling each should not affect other's function. For example, LED class and Uart class can be enabled/disabled individually.

The key is to `extern` declear all objects in `instance.h` file. Then, **ONLY define ONCE of the object definiation in `main.cpp`**. The result benefit is that after including `instance.h`, all objects gets global visibility to be used in controlling OS: `CLI`, `FreeRTOS`, or `boost/sml`.



## 1.2. System
- System Freq: 80MHz.
- Using Hardware Timer 16 for FreeRTOS.



## 1.3. UART
Class Name: `SerialCOM`

Dependancy: `string` `algorithm`

- Enable UART Interrupt.
- Continues Sending of All Remaining String Buffer Using: `HAL_UART_TxCpltCallback`.
- Continues Receiving Using: `HAL_UARTEx_RxEventCallback` with Receiving Function Self Restart.
- Method avoided using `osstream` and `sprintf` to limit binary size.
- Output buffer using `std::string` for simplicity of not needing ring buffer. User must schedule `sendOut()` in a reasonable time period to transmit data. String buffer will auto clear after each transmition.
- UART buffer default with 64 bytes. Overwrite it by `#define UART_BUFFER ###` in `main.cpp` or `instance.h`. This is only necessary if trying to receive long data at once. Sending is not the bottleneck.

### 1.3.1. Use of UART Object
- `sendString(std::string)` and `ssendNumber(any number)`to add data to buffer.
- `sendLn()` for fast formatting.
- `sendOut()` to initiate transmission. **Recall this funtion in `HAL_UART_TxCpltCallback` to send all buffer.**
- Start of the Instance:
> Before `main()`:
```c++
	SerialCOM serialCOM{};
```
> Inside `main()`:
```c++
	MX_USART2_UART_Init();
	serialCOM.setPort(&huart2);
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, serialCOM.m_rx_data, UART_BUFFER);
```






## 1.4. CLI
Class Name: `CLI`

Dependancy: `string.h`

- This is a wrapper class to use `lwshell` in C++ style.
- User is responsible for defining output function to have `lwshell` make auto `Unknown Command` or `-h` response. If output response is not needed. Simple remove `lwshell_set_output_fn(&CLI::output);` in `init()`. In this project, we are defining `output()` wrapper `static` function to bridge SerialCOM output method.
```c++
	static void CLI::output(const char* str, lwshell* lwobj) { serialCOM.sendString(str); }
	lwshell_set_output_fn(&CLI::output);
```
- This project assume human command only where processing time is sufficient to complete all task before next command arrival. So, we are parsing directly from RX buffer. When setting up machine communication, a `std::vector<std::string>`  is needed to catch all incomming command and process later.
- We are defining `parse()` wrapper function to predefine the source of Uart RX buffer and buffer size reported from interrupt.
- `setSize(uint16_t)` is required in receiving interrupt to correct parse correct amount of data.

### 1.4.1. Use of CLI Object

- Direct usage without FreeRTOS:
> Inside `HAL_UARTEx_RxEventCallback()`:
```c++
	cli.setSize(Size);
	cli.parse();
```

- Start of the Instance:
> Before `main()`:
```c++
	CLI cli{};
```
> Inside `main()`:
```c++
	cli.init();
```

### 1.4.2. Customization

- Finally, we can populate our `static` custom command functions. **All function MUST `return int32_t;`.**
- You will need to define the command and register it in `init()`.
- Example Command with Sub Commands:
> Inside init():
```c++
	lwshell_register_cmd("led", &CLI::led, NULL);
```
> Function Define:
```c++
	static int32_t CLI::led(int32_t argc, char** argv) {
		const char* led_help =
			"\nLED Functions:\n"
			"  on\tTurns ON LED\n"
			"  off\tTurns OFF LED\n"
			"  breath\tLED in breath effect mode\n"
			"  blink\tLED in slow blink mode\n"
			"  rapid\tLED in fast blink mode\n\n";

		if (!strcmp(argv[1], "help")) serialCOM.sendString(led_help);
		if (!strcmp(argv[1], "on")) led_user.on();
		if (!strcmp(argv[1], "off")) led_user.off();
		if (!strcmp(argv[1], "breath")) led_user.breath();
		if (!strcmp(argv[1], "blink")) led_user.blink();
		if (!strcmp(argv[1], "rapid")) led_user.rapid();
		return 0;
	}
```



## 1.5. FreeRTOS

API: https://www.freertos.org/a00106.html

Class Name: `Thread`

Dependancy: `FreeRTOS.h` `task.h`

- This provides a C++ wrap for FreeRTOS.
- Thread itself must also create an object in `instances.h`.
- `#include "instances.h"` must be in `Thread.cpp` file but not `Thread.hpp` file
- All `instances.h` object must be configured and initialized before `vTaskStartScheduler()`.
- `#define configSUPPORT_STATIC_ALLOCATION` set to false.
- SerialCOM using under FreeRTOS limitation. Due to the use of string buffer. The task priority of `serial_send()` must be greater or equal to all task that uses `serialCOM.sendString()`. The key is to avoid writing into string buffer during transmission.




### 1.5.1. Use of FreeRTOS Wrapper Class
- The task are created in the object initialization using Lamda due to C++ wrapping.
> In object initializer:
```c++
    auto t1 = [](void *arg) { static_cast<Thread *>(arg)->parse(); };
    xTaskCreate(t1, "cli parsing", 256, this, -2, &parse_Handle);
```
- Each of the corresponding task are decleared with its handle typle.
> In header:
```c++
    TaskHandle_t parse_Handle;
    void parse();
```



### 1.5.2. FreeRTOS Debug

- Install VS Code Extension: RTOS Views (`mcu-debug.rtos-views`)
- Use a hardware timer with 20KHz setting. In this projcet timer 7 is used.
- Include the follwing code to enable full debugging feature.
> In `FreeRTOSConfig.h`:
```c++
	#include "tim.h"								// Using 20kHz hardware timer
	#define configUSE_TRACE_FACILITY 1				// Show RTOS task ID stats
	#define configUSE_STATS_FORMATTING_FUNCTIONS 1	// Enable using vTaskList()
	#define configRECORD_STACK_HIGH_ADDRESS 1		// Show RTOS stack stats
	#define configGENERATE_RUN_TIME_STATS 1
	#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() MX_TIM7_Init()
	#define portGET_RUN_TIME_COUNTER_VALUE() htim7.Instance->CNT
```
> In `MX_TIM7_Init()`:
```c++
	/* USER CODE BEGIN TIM7_Init 2 */
	__TIM7_CLK_ENABLE();
	HAL_TIM_Base_Init(&htim7);
	HAL_TIM_Base_Start(&htim7);
```



## 1.6. Side Note

Use Regular Expression: `` /\*.*/ `` to remove HAL comments in `main.cpp`.

All other CubeMX generated code are untouched.


