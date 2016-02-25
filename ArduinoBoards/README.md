# Development Boards

| Board                            | Arduino Compatible Software/Harware | Architecture | CHIP            | Clock | FLASH | SRAM | EEPROM | GPIO/ PWM | AI/O | Logic | Current Efficiency | DC    | Communication  | Programming | Price            |
|----------------------------------|-------------------------------------|--------------|-----------------|-------|------:|------|--------|-----------|------|-------|--------------------|-------|----------------|-------------|------------------|
| ![Arduino Uno Rev3][arduino_uno] | YES/YES                             | AVR          | ATmega328       | 16MHz | 32 kB | 2 kB | 1kB    | 14/6      | 6    | 5V    | 40 mA              | 7-12V | UART, I2C, SPI | USB A       | $3 (Aliexpress)  |
| ![Arduino Nano V4][arduino_nano] | YES/YES                             | AVR          | ATmega328       | 16MHz | 32 kB | 2 kB | 1kB    | 14/6      | 6    | 5V    | 40 mA              | 7-12V | UART, I2C, SPI | microUSB    | <$2 (Aliexpress) |
| ![Teensy++ 2.0][teensy_pp_20]    | YES/YES                             | AVR          | AT90USB128      | 16MHz | 128kB | 8kB  | 4kB    | 46/9      | 8    | 5V    |                    |       | UART, I2C, SPI | mini USB B  | $20 (Aliexpress) |
| ![Maple Mini][maple_mini]        | YES/YES                             | ARM          | STM32 F103RCBT6 | 72MHz | 128kB | 20kB | N/A    | 34/12     | 9    |       |                    | 3-12V | UART, I2C, SPI | mini USB B  | $4 (Aliexpress)  |

[arduino_uno]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/arduino_uno_r3.jpg "Arduino UNO"
[arduino_nano]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/arduino_nano_v3.jpg "Arduino Nano"
[teensy_pp_20]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/teensy_pp_20.gif "Teensy++ 2.0"
[maple_mini]: https://github.com/kopson/SmartLamp/blob/master/ArduinoBoards/maple_mini.jpg "Maple Mini"

### References
[http://www.tablesgenerator.com/markdown_tables]