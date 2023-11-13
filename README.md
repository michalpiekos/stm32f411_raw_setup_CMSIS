# stm32f411_raw_setup_CMSIS
Very basic setup for STM32F411 with CMSIS.
- Linker script and startup with vector table are carried over from CubeMX.
- Makefile is adapted from generated one from CubeIDE.
- Contains .vscode folder with configuration for VS Code. Paths and some variables need to be adapted to suit your environment.
- Contains .svd file for debugger. In VS Code I use Cortex-Debug extension.

In `main.c`:
- Main clock is set at 96MHz
- Delay functions are implemented using Timer 3
- Blinky (LED on GPIOC 13)

## Final word
Any ideas on further improvements are highly welcomed.

