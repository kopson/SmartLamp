// DS18B20 temperature reader

#include <OneWire.h>
#include <DS18B20.h>

#define ADDR_SIZE 8

// DS18B20 pin no
const byte ONEWIRE_PIN = 8;

// DS18B20 address
byte address[ADDR_SIZE] = {0x28, 0x5C, 0xAB, 0x52, 0x7, 0x0, 0x0, 0xAB};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

void setup() {
    while(!Serial);
    Serial.begin(9600);

    sensors.begin();
    sensors.request(address);
}

void loop() {
    if (sensors.available()) {
        float temperature = sensors.readTemperature(address);

        Serial.print(temperature);
        Serial.println(F(" 'C"));

        sensors.request(address);
    }

    //...
}
