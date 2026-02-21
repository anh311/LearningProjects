# STM32 Rotary Encoder Example

Hardware-based example project for using a rotary encoder with an STM32.


## Features

- Uses the STM32 Timer in Encoder Mode to count pulses directly in hardware.  
- No software debouncing or interrupts needed for encoder pins.  
- Reads encoder value via UART when the B1 button is pressed.  
- Direction and position tracking.  
- Rotating the encoder and pressing `B1` produces output.

## Setup

- Rotary Encoder connected to two STM32 GPIO pins.  
- Button B1 to read the current encoder value.   
  
## Purpose

This project is a simple STM32 learning example:

- Using STM32 timers in encoder mode 
- Understand hardware acceleration on microcontrollers.  
- Learn that microcontrollers often have special hardware blocks that offload work from the CPU, similar to hardware blocks in FPGAs.


