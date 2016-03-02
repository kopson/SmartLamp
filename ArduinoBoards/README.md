# Development Boards

| Board                              | Arduino Compatible Software/Harware | Architecture | SOC              | Clock |   FLASH | SRAM  | EEPROM | GPIO/ PWM | AI/O | Logic | Current Efficiency | DC     | Communication         | Programming         | Price                |
|------------------------------------|-------------------------------------|--------------|------------------|-------|--------:|-------|--------|-----------|------|-------|--------------------|--------|-----------------------|---------------------|----------------------|
| ![Arduino Uno Rev3][arduino_uno]   | YES/YES                             | AVR          | ATmega328        | 16MHz | 32 kB   | 2 kB  | 1kB    | 14/6      | 6    | 5V    | 40 mA              | 7-12V  | UART, I2C, SPI        | USB A               | $3 (Aliexpress)      |
| ![Arduino Nano V4][arduino_nano]   | YES/YES                             | AVR          | ATmega328        | 16MHz | 32 kB   | 2 kB  | 1kB    | 14/6      | 6    | 5V    | 40 mA              | 7-12V  | UART, I2C, SPI        | microUSB            | <$2 (Aliexpress)     |
| ![Teensy++ 2.0][teensy_pp_20]      | YES/YES                             | AVR          | AT90USB128       | 16MHz | 128kB   | 8kB   | 4kB    | 46/9      | 8    | 5V    |                    |        | UART, I2C, SPI        | mini USB B          | $20 (Aliexpress)     |
| ![Maple Mini][maple_mini]          | YES/YES                             | ARM          | STM32 F103RCBT6  | 72MHz | 128kB   | 20kB  | N/A    | 34/12     | 9    |       |                    | 3-12V  | UART, I2C, SPI        | mini USB B          | $4 (Aliexpress)      |
| ![STM32F103C8T6][stm32_clone]      | YES/YES                             | ARM          | STM32F103C8T6    | 72MHz | 64kB    | 20kB  | N/A    |           |      |       |                    |        |                       | mini USB B          | $2,3 (Aliexpress)    |
| ![Nucleo-F103RB][nucleo_f103rb]    | NO/NO                               | ARM          | STM32F103RBT6    | 72MHz | 128kB   | 20kB  | N/A    | 51/       |      | 3,3V  |                    | 3-12V  | UART, I2C, SPI        | mini USB B          | 60PLN                |
| ![Nucleo-32][nucleo_32]            | NO/YES                              | ARM          | STM32F031K6T6    | 72MHz | 64kB    | 16kB  | N/A    | 32/       |      | 3,3V  |                    | 2-3,6V | I2C, SPI, CAN, 2xUART | micro USB AB        | $22 (Aliexpress)     |
| ![Raspberry Pi Zero][rasp_pi_zero] | NO/NO                               | ARM          | Broadcom BCM2835 | 1GHz  | SD card | 512MB | N/A    | 40/       |      |       |                    |        |                       | Mini HDMI micro USB | $5 (**Unavaliable**) |

[arduino_uno]: 	https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/arduino_uno_r3.jpg "Arduino UNO"
[arduino_nano]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/arduino_nano_v3.jpg "Arduino Nano"
[teensy_pp_20]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/teensy_pp_20.jpg "Teensy++ 2.0"
[maple_mini]: 	https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/maple_mini.jpg "Maple Mini"
[stm32_clone]: 	https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/stm32_clone.jpg "STM32F103C8T6"
[nucleo_f103rb]:https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/nucleo_f103rb.jpeg "Nucleo-F103RB"
[nucleo_32]: 	https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/nucleo_32.jpeg "Nucleo-32"
[rasp_pi_zero]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/rasp_pi_zero.jpeg "Raspberry Pi Zero"

### References

[MarkDown Table Generator](http://www.tablesgenerator.com/markdown_tables)