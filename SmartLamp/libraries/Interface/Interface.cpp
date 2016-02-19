#include "Interface.h"

#define TEM_PRECISION 2

void Interface::initDisplay(LiquidCrystal *lcd, const byte cols, const byte rows) {
	_lcd = lcd;
    _lcd->begin(cols, rows);
    _lcd->clear();
    _lcd->setCursor(0, 0);
    _lcd->print("############");
}

void Interface::initTempSensor(DS18B20 *sensor, const byte *addr) {
	_sensor = sensor;
	_addr = addr;
    _sensor->begin();
    _sensor->request(FA(_addr));
}

void Interface::displayTemp(const byte row) {
    if (_sensor->available()) {
        float temperature = _sensor->readTemperature(FA(_addr));

		_lcd->setCursor(0, row);
    	_lcd->print(String(temperature, TEM_PRECISION) + " 'C");

        _sensor->request(FA(_addr));
    }
}
