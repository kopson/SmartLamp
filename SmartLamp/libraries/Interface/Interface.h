#ifndef _INTERFACE_h_
#define _INTERFACE_h_

#include <LiquidCrystal.h> 
#include <OneWire.h>
#include <DS18B20.h>

class Interface
{
public:
    void initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows);
    void initTempSensor(DS18B20 *sensor, const byte *addr);
    void displayTemp(const byte row);

private:
    LiquidCrystal *_lcd;
    DS18B20 *_sensor;
    const byte *_addr;

};
#endif