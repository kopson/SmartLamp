#include "Interface.h"

#define TEM_PRECISION 2

void Interface::initSwitch(const byte ledPin, MembraneSwitch *mSwitch) {
    _outputPin = ledPin;
    _switch = mSwitch;
    _switch->begin();
    pinMode(_outputPin, OUTPUT);
    analogWrite(_outputPin, 0);
#if DEBUG
    Serial.println("Interface::initSwitch");
#endif
}

void Interface::initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows) {
    _lcd = lcd;
    cursor = 0;
    state = NORMAL;
    power = true;
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
    _lcd->print(_rtc->getDateTimeStr());
#if DEBUG    
    Serial.println("Interface::displayDate");
#endif    
}

void Interface::handleSwitch() {
int button = _switch->getButton();
    if(_switch->available(button)) {
#if DEBUG  
        Serial.println(_switch->toString(button));
#endif        
        switch(button) {
            case MENU:
                handleMenu();
                break;
            case POWER:
                handlePower();  
                break;
            case AUTO:
                handleAuto();     
                break; 
            case LEFT:
                handleLeft();     
                break;
            case RIGHT:
                handleRight();       
                break; 
        }
    }
}

void Interface::handleLeft() {
    uint8_t date;
     switch(state) {
        case MENU_SET_DATE:
            switch(cursor) {
                case DAY:
                    date = _rtc->getTime().date;
                    if(date > 1)
                        --date;
                    _rtc->set(date, DS3231_DAY);
                    break;
                case MONTH:
                    date = _rtc->getTime().mon;
                    if(date > 1)
                        --date;
                    _rtc->set(date, DS3231_MONTH);
                    break;
                case YEAR:
                    date = _rtc->getTime().year;
                    if(date > 1)
                        --date;
                    _rtc->set(date + 2000, DS3231_YEAR);
                    break;
                case HOUR:
                    date = _rtc->getTime().hour;
                    if(date > 0)
                        --date;
                    _rtc->set(date, DS3231_HOUR);
                    break;
                case MIN:
                    date = _rtc->getTime().min;
                    if(date > 0)
                        --date;
                    _rtc->set(date, DS3231_MIN);
                    break;
                default:
                    break;  
            }
            displayDate(1);
            _lcd->blink();
        break;
    }
}

void Interface::handleRight() {
    uint8_t date;
     switch(state) {
        case MENU_SET_DATE:
            switch(cursor) {
                case DAY:
                    date = _rtc->getTime().date;
                    if(date < 31)
                        ++date;
                    _rtc->set(date, DS3231_DAY);
                    break;
                case MONTH:
                    date = _rtc->getTime().mon;
                    if(date < 12)
                        ++date;
                    _rtc->set(date, DS3231_MONTH);
                    break;
                case YEAR:
                    date = _rtc->getTime().year;
                    ++date;
                    _rtc->set(date + 2000, DS3231_YEAR);
                    break;
                case HOUR:
                    date = _rtc->getTime().hour;
                    if(date < 24)
                        ++date;
                    _rtc->set(date, DS3231_HOUR);
                    break;
                case MIN:
                    date = _rtc->getTime().min;
                    if(date < 60)
                        ++date;
                    _rtc->set(date, DS3231_MIN);
                    break;
            }
            displayDate(1);
            _lcd->blink();
        break;
    }
}

void Interface::handleAuto() {
#if DEBUG            
            Serial.println("Cursor " + cursor);
#endif  
    switch(state) {
        case MENU_SET_DATE:
            if (cursor == DAY) {
                cursor = MONTH;    
            } else if (cursor == MONTH) {
                cursor = YEAR;
            } else if (cursor == YEAR) {
                cursor = HOUR; 
            } else if (cursor == HOUR) {
                cursor = MIN;
            } else if (cursor == MIN) {
                cursor = DAY;
            }

            _lcd->setCursor(cursor, 1);
            _lcd->blink();
            break;
    }
}

void Interface::handlePower() {
    power = !power;
    if(!power) {
        _lcd->noDisplay();
        analogWrite(_outputPin, 0);
    }
    else {
        _lcd->display();
        analogWrite(_outputPin, 254);
    }
}

void Interface::handleMenu() {
    switch(state) {
        case NORMAL:
            state = MENU_SET_DATE;
            _lcd->clear();
            _lcd->setCursor(0, 0);
            _lcd->print("1. SET DATE");
            displayDate(1);
            cursor = 0;
            _lcd->setCursor(cursor, 1);
            _lcd->blink();
#if DEBUG            
            Serial.println("MENU_SET_DATE");
#endif            
            break;
        case MENU_SET_DATE:
           state = NORMAL;
            _lcd->clear();
            _lcd->noBlink();
            displayDate(0);
            displayTemp(1);
#if DEBUG            
            Serial.println("MENU_NORMAL");
#endif            
            break;
        default:
            _lcd->clear();
#if DEBUG            
            Serial.println("UNKNOWN_STATUS");
#endif            
    }
}
