# STM32 HAL driver for ADS1115

This STM32 driver uses HAL and was developed for fast single-shot reading.
It polls ADC state instead of waiting some time and hoping that the read data is the new sample.

Interface for programmable comparator hasn't been implemented.
Init hasn't been implemented as ads1115 does not require any initialization and defaults were correct for the use. 
taskENTER_CRITICAL and osDelay were added while fixing strange system behavior. They might not be needed, especially the latter.
