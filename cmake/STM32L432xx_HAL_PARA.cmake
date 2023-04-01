set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

set(compiler_define
    "USE_HAL_DRIVER"
    "STM32L432xx"
)