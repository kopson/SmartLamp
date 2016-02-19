#include "Interface.h"

#define TEM_PRECISION 2

void Interface::initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows) {
	_lcd = lcd;
    _lcd->begin(cols, rows);
    _lcd->clear();
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

void Interface::displayTemp(const byte row) {
    if (_sensor->available()) {
        float temperature = _sensor->readTemperature(FA(_addr));

		_lcd->setCursor(0, row);
    	_lcd->print(String(temperature, TEM_PRECISION) + " 'C");

        _sensor->request(FA(_addr));
    }
}

void Interface::displayDate(const byte row) {
    _lcd->setCursor(0, row);
    _lcd->print(String(_rtc->getDateStr()) + " " + String(_rtc->getTimeStr()));
}