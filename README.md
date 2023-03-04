[![Build Binary Alpine](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_alpine.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_alpine.yml)
[![Build Binary Ubuntu](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_ubuntu.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_ubuntu.yml)
[![Build Binary Github](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_github.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-CLI/actions/workflows/build_github.yml)

# CLI Use



regEX
/\*.*/ to nothing



LED Library:

- PWM
  - `Prescaler * Overflow = Period-in-Cycles = Clock-cycles-per-Second / Frequency`
  - overflow  = 2^bits
  - prescaler * overflow >= period_cycles
```
#define CLOCK_CYCLES_PER_SECOND  72000000
#define MAX_RELOAD               0xFFFF

uint32_t period_cycles = CLOCK_CYCLES_PER_SECOND / freq;
uint16_t prescaler = (uint16)(period_cycles / MAX_RELOAD + 1);
uint16_t overflow = (uint16)((period_cycles + (prescaler / 2)) / prescaler);
uint16_t duty = (uint16)(overflow / 2);
```



- it.c:
  - extern TIM_HandleTypeDef htimX;
  - add TIMX_IRQHandler calling {HA_TIM_IRQHandler(&htimX)}
- it.h:
  - add function header
- use Timer Based SysTick
  - Then, `void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {` add `if (htim->Instance == TIMX) {`
- 20Hz
- 
```
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 3200 - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 499;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
```

- main.c:
  - TIM_HandleTypeDef htimX;
  - MX_TIMX_Init();
  - HAL_TIM_PWM_Start(&htimX, TIM_CHANNEL_X);
  - led_user.setPort(&htimX.Instance->CCRX); // CCR is channel
- main.h
  - `void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);`