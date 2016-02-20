#include "Interface.h"

#define DEBUG 1

#define TEM_PRECISION 2
#define AUTO_MIN 800
#define AUTO_MAX 850
#define MENU_MIN 650
#define MENU_MAX 750
#define LEFT_MIN 900
#define LEFT_MAX 950
#define RIGHT_MIN 550
#define RIGHT_MAX 650
#define POWER_MIN 500
#define POWER_MAX 550
#define ZERO_MARGIN 10

void Interface::initSwitch(const byte pin) {
    _outputPin = pin;
    _status.init();
    pinMode(_outputPin, OUTPUT);
    analogWrite(_outputPin, 0);
#if DEBUG
    Serial.println("Interface::initSwitch");
#endif
}

void Interface::initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows) {
    _lcd = lcd;
    _lcd->begin(cols, rows);
    _lcd->clear();
#if DEBUG
    Serial.println("Interface::initDisplay");
#endif
}

void Interface::initTempSensor(DS18B20 *sensor, const byte *addr) {
    _sensor = sensor;
    _addr = addr;
    _sensor->begin();
    bool ret = _sensor->request(FA(_addr));
#if DEBUG
    if(ret)
        Serial.println("Interface::initTempSensor");
    else
        Serial.println("Interface::initTempSensor error");
#endif    
}

void Interface::initRTC(DS3231* rtc) {
    _rtc = rtc;
    _rtc->begin();
#if DEBUG    
    Serial.println("Interface::initRTC");
#endif    
}

void Interface::displayTemp(const byte row) {
    if (_sensor->available()) {
        float temperature = _sensor->readTemperature(FA(_addr));

        _lcd->setCursor(0, row);
        _lcd->print(String(temperature, TEM_PRECISION) + " 'C");

        _sensor->request(FA(_addr));
#if DEBUG        
        Serial.println("Interface::displayTemp");
#endif        
    }
}

void Interface::displayDate(const byte row) {
    _lcd->setCursor(0, row);
    _lcd->print(String(_rtc->getDateStr()) + " " + String(_rtc->getTimeStr()));
#if DEBUG    
    Serial.println("Interface::displayDate");
#endif    
}

void Interface::handleSwitch(const byte pin) {
    int analogValue = analogRead(pin);

    if(analogValue > AUTO_MIN && analogValue < AUTO_MAX) {
#if DEBUG        
        Serial.println("AUTO");
#endif        
    } else if (analogValue > MENU_MIN && analogValue < MENU_MAX) {
#if DEBUG        
        Serial.println("MENU");
#endif        
        handleMenu();
    } else if (analogValue > LEFT_MIN && analogValue < LEFT_MAX) {
#if DEBUG        
        Serial.println("LEFT");
#endif        
    } else if (analogValue > RIGHT_MIN && analogValue < RIGHT_MAX) {
#if DEBUG        
        Serial.println("RIGHT");
#endif        
    } else if (analogValue > POWER_MIN && analogValue < POWER_MAX) {
#if DEBUG        
        Serial.println("POWER");
#endif        
    } else if (analogValue > ZERO_MARGIN) {
#if DEBUG        
        Serial.println("ERROR");
#endif        
    } else {
#if DEBUG        
        Serial.println("RELEASED");
#endif        
        _status.invalidate();
    }
}

void Interface::handleMenu() {
    switch(_status.getState()) {
        case NORMAL:
            if(!_status.setState(MENU_SET_DATE))
                return;
            _lcd->clear();
            _lcd->setCursor(0, 1);
            _lcd->print("1. SET DATE");
#if DEBUG            
            Serial.println("MENU_SET_DATE");
#endif            
            break;
        case MENU_SET_DATE:
            if(!_status.setState(NORMAL))
                return;
            _lcd->clear();
            displayDate(0);
            displayTemp(1);
#if DEBUG            
            Serial.println("MENU_NORMAL");
#endif            
            break;
        default:
            _lcd->clear();
            _lcd->setCursor(0, 1);
            _lcd->print("Unknown status" + _status.getState());
#if DEBUG            
            Serial.println("UNKNOWN_STATUS");
#endif            
    }
}

bool Status::setState(byte st) {
    if(isNextSwitch)
        return false;
    state = st;
    isNextSwitch = true;
    return isNextSwitch;
}

byte Status::getState() {
    return state;
}

void Status::init() {
    state = NORMAL;
    isNextSwitch = true;
}

void Status::invalidate() {
    isNextSwitch = false;
}
