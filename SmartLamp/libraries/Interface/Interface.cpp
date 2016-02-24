#include "Interface.h"

void Interface::initSwitch(const byte ledPin, MembraneSwitch *mSwitch) {
    _outputPin[0] = ledPin;
    _outputPin[1] = ledPin;
    _outputPin[2] = ledPin;
    _switch = mSwitch;
    _switch->begin();
    button = 0;
    _program = 0;

    for (int i = 0; i < 3; ++i) {
        _brightness[i] = 0;
        pinMode(_outputPin[i], OUTPUT);
        analogWrite(_outputPin[i], _brightness[i]);
    }
}

void Interface::initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows) {
    _lcd = lcd;
    _cursor = 0;
    state = NORMAL;
    power = true;
    _lcd->begin(cols, rows);
    _lcd->clear();
    displayLED();
}

void Interface::initTempSensor(DS18B20 *sensor, const byte *addr) {
    _sensor = sensor;
    _addr = addr;
    _sensor->begin();
    _sensor->request(FA(_addr));  
}

void Interface::initRTC(DS3231* rtc) {
    _rtc = rtc;
    _rtc->begin(); 
}

void Interface::displayTimeTemp() {
    static byte temp = 0;
    _lcd->setCursor(0, 0);
    _lcd->print(_rtc->getTimeStr());
    _lcd->print(" ");

    if (_sensor->available()) {
        temp = _sensor->readTemperature(FA(_addr));
        _sensor->request(FA(_addr));   
    }
    _lcd->print(String(temp) + "'C");
    _lcd->print(" ");
    if (_program > 0) {
        _lcd->print("P" + _program);
    } 
}

void Interface::displayLED(){
    _lcd->setCursor(0, 1);
    for(int i = 0; i < 3; ++i) {
    if (_cursor == i)
        _lcd->print("#" + String(_brightness[i] / 2) + "% ");
    else
        _lcd->print(" " + String(_brightness[i] / 2) + "% ");
    }
}

void Interface::displayTime() {
    _lcd->setCursor(0, 1);
    _lcd->print(_rtc->getTimeStr()); 
}

void Interface::setLED(bool increase, byte i) {
    if (increase && _brightness[i] < MAX_PWM)
        _brightness[i] += 2;
    else if (!increase && _brightness[i] > 0)
        _brightness[i] -= 2;
    analogWrite(_outputPin[i], _brightness[i]);
    displayLED();
}

void Interface::handleSwitch() {
    if (_switch->getButton(&button)) {       
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
    } else {
        if (state == NORMAL) {
            displayTimeTemp();
        }
    }
}

void Interface::setTime(bool increase) {
    uint8_t date;
    switch (_cursor) {
        case HOUR:
            date = _rtc->getTime().hour;
            if (!increase && date > 0)
                --date;
            else if (increase && date < 24)
                ++date;
            _rtc->set(date, DS3231_HOUR);
            break;
        case MIN:
            date = _rtc->getTime().min;
            if (!increase && date > 0)
                --date;
            else if (increase && date < 60)
                ++date;
            _rtc->set(date, DS3231_MIN);
            break;
        default:
            break;  
    }
    displayTime();
    _lcd->setCursor(_cursor, 1);
    _lcd->blink();
}

void Interface::handleLeft() {
    switch (state) {
        case MENU_SET_DATE:
            setTime(false);
            break;
        case MENU_SET_PROG:
            _lcd->setCursor(0, 1);
            if (_program > 0)
                --_program;
            _lcd->print(_program);
            break;
        case NORMAL:
            setLED(false, _cursor);
            break;
    }
}

void Interface::handleRight() {
    switch (state) {
        case MENU_SET_DATE:
            setTime(true);
            break;
        case MENU_SET_PROG:
            _lcd->setCursor(0, 1);
            if (_program < 8)
                ++_program;
            _lcd->print(_program);
            break;
        case NORMAL:
            setLED(true, _cursor);
            break;
    }
}

void Interface::handleAuto() {
    switch (state) {
        case NORMAL:
            if (_cursor == LED1) {
                _cursor = LED2;
            } else if (_cursor == LED2) {
                _cursor = LED3;
            } else if (_cursor == LED3) {
                _cursor = LED1;
            }
            displayLED();
            break;
        case MENU_SET_DATE:
            if (_cursor == HOUR) {
                _cursor = MIN;
            } else if (_cursor == MIN) {
                _cursor = HOUR;
            }

            _lcd->setCursor(_cursor, 1);
            _lcd->blink();
            break;
    }
}

void Interface::handlePower() {
    power = !power;
    if (!power) {
        _lcd->noDisplay();
        for (int i = 0; i < 3; ++i) {
            analogWrite(_outputPin[i], 0);
        }
    } else {
        _lcd->display();
        for (int i = 0; i < 3; ++i) {
            analogWrite(_outputPin[i], _brightness[i]);
        }
        menuSetNorm();
    }
}

void Interface::menuSetTime() {
    state = MENU_SET_DATE;
    _lcd->clear();
    _lcd->setCursor(0, 0);
    _lcd->print("SET TIME");
    displayTime();
    _cursor = 0;
    _lcd->setCursor(_cursor, 1);
    _lcd->blink(); 
}

void Interface::menuSetProg() {
    state = MENU_SET_PROG;
    _lcd->clear();
    _lcd->setCursor(0, 0);
    _lcd->print("SET PROGRAM");
    _lcd->setCursor(0, 1);
    _lcd->print(_program);
    _lcd->noBlink(); 
}

void Interface::menuSetNorm() {
    state = NORMAL;
    displayTimeTemp();
    displayLED();
}

void Interface::handleMenu() {
    switch (state) {
        case NORMAL:
            menuSetTime();
            break;
        case MENU_SET_DATE:
            if (_cursor != 0) {
                menuSetNorm(); 
            } else {    
                menuSetProg();
            }
            break;   
        case MENU_SET_PROG:
            menuSetNorm();            
            break;
        default:
            _lcd->clear();          
    }
}
