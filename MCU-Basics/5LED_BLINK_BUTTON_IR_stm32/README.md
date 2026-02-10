# STM32 Quick Start Example

Simple STM32 project for basic GPIO usage.

## Features

- Toggles the built-in LED (LD2) every 3 seconds.
- Toggles an additional LED (`LED_new`) when a button (`B1`) is pressed.
- Handles GPIO interrupts for button presses.
- The project uses STM32 HAL library.
- Designed for quick experimentation and learning

## Code Overview

- **main.c**: Initializes the MCU, system clock, GPIOs, and UART. The main loop handles the LED blinking with a 3-second interval.
- **HAL_GPIO_EXTI_Callback**: Interrupt callback to toggle the second LED when the button is pressed.
