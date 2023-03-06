[![Build Binary Alpine](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_alpine.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_alpine.yml)
[![Build Binary Ubuntu](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_ubuntu.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_ubuntu.yml)
[![Build Binary Github](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_github.yml/badge.svg)](https://github.com/jasonyang-ee/STM32-LED/actions/workflows/build_github.yml)

# LED Class Use Instruction

Project Using STM32L432KC as Example. Test hardware is NUCLEO-L432KC.



## DMA

- DMA Init Position matters, must put in front of UART Init but after GPIO Init.
- DMA for Uart RX for "byte" "normal mode"
- __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT); is required to avoid half transfer complete interrupt collision.





## C++ Host
- Optionally, declear `extern object` in `instance.h` to allow object sharing.
- Only define object init in `main.cpp`.


### Side Note

Use Regular Expression: `` /\*.*/ `` to remove HAL comments in `main` and `it`


