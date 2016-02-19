#ifndef _DS18B20_h_
#define _DS18B20_h_

#include <Arduino.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <OneWire.h>

#define MIN_QUALITY   9
#define MAX_QUALITY   12
#define ADDR_SIZE     8
#define TEMP_ERROR    -273.15f
#define DS18B20_CHIP  0x28

// Pointer type to an array in flash memory of device address
#define FA( pgm_ptr ) ( reinterpret_cast< const __FlashStringHelper * >( pgm_ptr ) )

// Exceptions catcher
#define E(a) __check(a, __LINE__)

// Teperature value exception catcher
#define TE(a) __check(a != TEMP_ERROR, __LINE__)

void __check(bool value, uint16_t line);

class DS18B20
{
public:
  DS18B20(OneWire* oneWire);
  bool begin(uint8_t quality = MAX_QUALITY);
  bool request(void);
  bool request(uint8_t *address);
  bool request(const __FlashStringHelper *_address);

  bool available(void);
  float readTemperature(uint8_t *address);
  float readTemperature(const __FlashStringHelper *_address);

private:
  OneWire *_oneWire;
  uint8_t _quality;
  bool _samePowerType;
  bool _powerType;
  uint32_t _beginConversionTime;

  bool _sendCommand(uint8_t *address, uint8_t command);
  bool _sendQuality(uint8_t *address);
  bool _receivePowerType(uint8_t *address);
  void _readFlashAddress(const __FlashStringHelper *_address, uint8_t *address);
};
#endif