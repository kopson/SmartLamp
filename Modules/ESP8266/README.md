# ESP8266

### Update firmware

1. Download flashing tool:
https://github.com/themadinventor/esptool/

2. Download firware:
https://github.com/espressif/esp8266_at/tree/master/bin

3. Connect
ESP8266:
    VCC 	-> Arduino 3.3V (needs around 300-400mA peak)
    GND 	-> Arduino GND
    CH_PD 	-> Arduino 3.3V
    RST 	-> Leave floating
    GPIO0 	-> Arduino GND
    UTXD 	-> FTDI/Serial RXD
    URXD 	-> FTDI/Serial RXD
    		   FTDI/Serial GND -> Arduino GND
    		   FTDI/Serial 3V3 -> FTDI/Serial VCC
    		   FTDI/Serial 5V -> Leave floating

4. Flash
./esptool.py --port /dev/ttyUSB0 write_flash 0x00000 ../ESP8266_AT/bin/boot_v1.1.bin 0x01000 ../ESP8266_AT/bin/v0.20/user1.bin 0x7C000 ../ESP8266_AT/bin/esp_init_data_default.bin 0x7E000 ../ESP8266_AT/bin/blank.bin

### Use

### References
http://iot-playground.com/blog/2-uncategorised/35-esp8266-firmware-update
http://majsterkowo.pl/proste-male-bezprzewodowe-czujniki-temperatury-i-wilgotnosci-komunikujace-sie-przez-wifi-esp8266/
http://allaboutee.com/