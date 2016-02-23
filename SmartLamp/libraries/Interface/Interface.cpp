#include "Interface.h"

#define TEM_PRECISION 2

bool timeoutExpired = true;

void Interface::initSwitch(const byte ledPin, MembraneSwitch *mSwitch) {
    _outputPin = ledPin;
    _switch = mSwitch;
    _switch->begin();
    button = 0;
    program = 0;
    pinMode(_outputPin, OUTPUT);
    brightness = 0;
    analogWrite(_outputPin, brightness);
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
    timeoutEvent = 0;
#if DEBUG
    Serial.println("Interface::initDisplay");
#endif
}

void Interface::initTempSensor(DS18B20 *sensor, const byte *addr) {
    _sensor = sensor;
    _addr = addr;
    _sensor->begin();
    _sensor->request(FA(_addr));
    timeoutExpired = true;
#if DEBUG
    Serial.println("Interface::initTempSensor");
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

void initLCDTemp() {
    timeoutExpired = true;
}

void Interface::displayLED(bool increase) {
    if(increase && brightness < MAX_PWM)
        brightness += 2;
    else if(!increase && brightness > 0)
        brightness -=2;
    analogWrite(_outputPin, brightness);
    _t.stop(timeoutEvent); 
    timeoutEvent = _t.after(LCD_TIMEOUT, initLCDTemp);
    _lcd->setCursor(0, 1);
    _lcd->print(String(brightness / 2) + " %         ");
    timeoutExpired = false;
}

void Interface::handleSwitch() {
    if(_switch->getButton(&button)) {       
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
        if(state == NORMAL) {
            displayDate(0);
            if(timeoutExpired)
                displayTemp(1);
        }
    }
    _t.update();
}

void Interface::setDate(bool increase) {
    uint8_t date;
    switch(cursor) {
        case DAY:
            date = _rtc->getTime().date;
            if(!increase && date > 1)
                --date;
            else if(increase && date < 31)
                ++date;
            _rtc->set(date, DS3231_DAY);
            break;
        case MONTH:
            date = _rtc->getTime().mon;
            if(!increase && date > 1)
                --date;
            else if (increase && date < 12)
                ++date;
            _rtc->set(date, DS3231_MONTH);
            break;
        case YEAR:
            date = _rtc->getTime().year;
            if(!increase && date > 1)
                --date;
            else if (increase)
                ++date;
            _rtc->set(date + 2000, DS3231_YEAR);
            break;
        case HOUR:
            date = _rtc->getTime().hour;
            if(!increase && date > 0)
                --date;
            else if (increase && date < 24)
                ++date;
            _rtc->set(date, DS3231_HOUR);
            break;
        case MIN:
            date = _rtc->getTime().min;
            if(!increase && date > 0)
                --date;
            else if (increase && date < 60)
                ++date;
            _rtc->set(date, DS3231_MIN);
            break;
        default:
            break;  
    }
    displayDate(1);
    _lcd->setCursor(cursor, 1);
    _lcd->blink();
}

void Interface::handleLeft() {
    switch(state) {
        case MENU_SET_DATE:
            setDate(false);
        break;
        case MENU_SET_PROG:
            _lcd->setCursor(0, 1);
            if(program > 1)
                --program;
            _lcd->print(program);
            _lcd->setCursor(0, 1);
            _lcd->blink();
            break;
        case NORMAL:
            displayLED(false);
        break;
    }
}

void Interface::handleRight() {
    switch(state) {
        case MENU_SET_DATE:
            setDate(true);
        break;
        case MENU_SET_PROG:
            _lcd->setCursor(0, 1);
            if(program < 8)
                ++program;
            _lcd->print(program);
            _lcd->setCursor(0, 1);
            _lcd->blink();
            break;
        case NORMAL:
            displayLED(true);
        break;
    }
}

void Interface::handleAuto() {
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
    } else {
        _lcd->display();
        analogWrite(_outputPin, brightness);
    }
}

void Interface::menuSetDate() {
    state = MENU_SET_DATE;
    _lcd->clear();
    _lcd->setCursor(0, 0);
    _lcd->print("SET DATE");
    displayDate(1);
    cursor = 0;
    _lcd->setCursor(cursor, 1);
    _lcd->blink(); 
}

void Interface::menuSetProg() {
    state = MENU_SET_PROG;
    _lcd->clear();
    _lcd->setCursor(0, 0);
    _lcd->print("SET PROGRAM");
    _lcd->setCursor(0, 1);
    _lcd->print(program);
    _lcd->blink(); 
}

void Interface::menuSetNorm() {
    state = NORMAL;
    _lcd->clear();
    _lcd->noBlink();
    displayDate(0);
    displayTemp(1);
}

void Interface::handleMenu() {
    switch(state) {
        case NORMAL:
            menuSetDate();
            break;
        case MENU_SET_DATE:
            if(cursor != 0) {
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
