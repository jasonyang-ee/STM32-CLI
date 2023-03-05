[![Build Binary Alpine](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_alpine.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_alpine.yml)
[![Build Binary Ubuntu](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_ubuntu.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_ubuntu.yml)
[![Build Binary Github](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_github.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_github.yml)

# LED Class Use Instruction

Project Using STM32L432KC as Example. Test hardware is NUCLEO-L432KC.

## PWM

- `Prescaler` x `Overflow` = `Clock Source` = `System Clock` / `Desired PWM Frequency`

- If wanting period be 100 for ease of duty cycle setting:
- 32Mhz / 1KHz / 100 = 320
- => `prescaler`: 320, `period`: 100, `PWM Frequency`: 1KHz
- If wanting max precision with using max period:
- 32Mhz / 1KHz / (if > 65535) then divide 65535 (16bit period)
- => `prescaler`: 1, `period`: 32000, `PWM Frequency`: 1KHz
- Use `clock source`: `internal clock (APBx)`
- Enable `global interrupt`
- Run `HAL_TIM_PWM_Start_IT(&htimX, TIM_CHANNEL_X)` in `main()`
- Define `void PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)`
- Run `led_user.scheduler()` in the `PWM_PulseFinishedCallback`

## LED Class
  - Init object `LED led_user{period, dimmer, PWM Frequency}`
  - Passthogh channel CCR with `led_user.setCCR(&htimX.Instance->CCRX);`
  - Ready to use `on()`, `off()`, `toggle()`, `set()`, `breath()`, `blink()`, `rapid()`.

## C++ Host
- Optionally, declear `extern object` in `instance.h` to allow object sharing.
- Only define object init in `main.cpp`.


### Side Note

Use Regular Expression: `` /\*.*/ `` to remove HAL comments in `main` and `it`


