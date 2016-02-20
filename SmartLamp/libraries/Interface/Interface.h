#ifndef _INTERFACE_h_
#define _INTERFACE_h_

#include <LiquidCrystal.h> 
#include <OneWire.h>
#include <DS18B20.h>
#include <DS3231.h>

#define DEBUG 1

class Status {
    #define NORMAL          0
    #define MENU_SET_DATE   1

public:
    bool setState(byte state);
    byte getState();
    void init();
    void invalidate();

private:
    byte state;
    bool isNextSwitch;

};

class Interface
{
public:
    void initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows);
    void initTempSensor(DS18B20 *sensor, const byte *addr);
    void displayTemp(const byte row);
    void initRTC(DS3231* rtc);
    void displayDate(const byte row);
    void handleSwitch(const byte pin);
    void handleMenu();
    void initSwitch(const byte pin);

private:
    LiquidCrystal *_lcd;
    DS18B20 *_sensor;
    DS3231 *_rtc;
    const byte *_addr;
    Status _status;
    byte _outputPin;
};
#endif