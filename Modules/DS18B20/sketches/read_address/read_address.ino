// DS18B20 serial number reader
#include <OneWire.h>

#define ADDR_SIZE 8

// DS18B20 pin no
const byte ONEWIRE_PIN = 8;

OneWire onewire(ONEWIRE_PIN);

void setup() {
    while(!Serial);
    Serial.begin(9600);
}

void loop() {
    byte address[ADDR_SIZE];

    onewire.reset_search();
    while(onewire.search(address)) {
        if (address[0] != 0x28) {
            continue;
        }

        if (OneWire::crc8(address, ADDR_SIZE - 1) != address[ADDR_SIZE - 1]) {
            Serial.println(F("Error: Incorrect address!"));
            break;
        }

        for (byte i = 0; i < ADDR_SIZE; i++) {
            Serial.print(F("0x"));
            Serial.print(address[i], HEX);

            if (i < ADDR_SIZE - 1) {
                Serial.print(F(", "));
            }
        }
        Serial.println();
    }

    while(1);
}
