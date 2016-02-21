#include <MembraneSwitch.h>

#define BUTTON_PIN A3

MembraneSwitch mSwitch(BUTTON_PIN);

void setup() {
    Serial.begin(9600);
    mSwitch.begin();
}

void loop() {
    byte button = mSwitch.getButton();
    if(mSwitch.available(button))
        Serial.println(mSwitch.toString(button));
}
