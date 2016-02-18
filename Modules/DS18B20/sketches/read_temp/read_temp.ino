// DS18B20 temperature reader
#include <OneWire.h>
#include <DS18B20.h>

// DS18B20 pin no
const byte ONEWIRE_PIN = 8;

// DS18B20 address
const byte address[ADDR_SIZE] PROGMEM = {0x28, 0x5C, 0xAB, 0x52, 0x7, 0x0, 0x0, 0xAB};

OneWire oneWire(ONEWIRE_PIN);
DS18B20 sensor(&oneWire);

void setup() {
    while(!Serial);
    Serial.begin(9600);

    sensor.begin();
    sensor.request(FA(address));
}

void loop() {
    if (sensor.available()) {
        float temperature = sensor.readTemperature(FA(address));

        Serial.print(temperature);
        Serial.println(F(" 'C"));

        sensor.request(FA(address));
    }

    //...
}
