#ifndef _INTERFACE_h_
#define _INTERFACE_h_

#include <LiquidCrystal.h> 
#include <OneWire.h>
#include <DS18B20.h>
#include <DS3231.h>
#include <MembraneSwitch.h>

#define DEBUG           0

#define NORMAL          0
#define MENU_SET_DATE   1
#define MENU_SET_PROG   2

#define HOUR            0
#define MIN             3
#define LED1            0
#define LED2            1
#define LED3            2

#define MAX_PWM         200

class Interface
{
public:
    void initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows);
    void initTempSensor(DS18B20 *sensor, const byte *addr);
    void initRTC(DS3231* rtc);
    void initSwitch(const byte ledPin, MembraneSwitch *mSwitch);

    void handleSwitch();

private:
    void displayTimeTemp();
    void displayTime();
    void setLED(bool increase, byte led);
    void displayLED();

    void handleMenu();
    void handlePower();
    void handleAuto();
    void handleLeft();
    void handleRight();

    void setTime(bool increase); 

    void menuSetTime();
    void menuSetProg();
    void menuSetNorm();

    LiquidCrystal       *_lcd;
    DS18B20             *_sensor;
    DS3231              *_rtc;
    MembraneSwitch      *_switch;

    const byte          *_addr;
    byte                state;
    bool                power;
    byte                _outputPin[3];
    byte                _cursor;
    byte                _brightness[3];

    byte                button;
    byte                _program;
};
#endif