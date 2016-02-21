#ifndef _INTERFACE_h_
#define _INTERFACE_h_

#include <LiquidCrystal.h> 
#include <OneWire.h>
#include <DS18B20.h>
#include <DS3231.h>
#include <MembraneSwitch.h>

#define DEBUG 0

#define NORMAL          0
#define MENU_SET_DATE   1

#define DAY     0
#define MONTH   3
#define YEAR    6
#define HOUR    11
#define MIN     14

class Interface
{
public:
    void initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows);
    void initTempSensor(DS18B20 *sensor, const byte *addr);
    void displayTemp(const byte row);
    void initRTC(DS3231* rtc);
    void displayDate(const byte row);
    void handleSwitch();
    void handleMenu();
    void handlePower();
    void handleAuto();
    void handleLeft();
    void handleRight();
    void initSwitch(const byte ledPin, MembraneSwitch *mSwitch);

private:
    LiquidCrystal *_lcd;
    DS18B20 *_sensor;
    DS3231 *_rtc;
    MembraneSwitch *_switch;
    const byte *_addr;
    byte state;
    bool power;
    byte _outputPin;
    byte cursor;
};
#endif