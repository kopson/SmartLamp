#include <MembraneSwitch.h>

#define BUTTON_PIN A3

MembraneSwitch mSwitch(BUTTON_PIN);
byte button;

void setup() {
    Serial.begin(9600);
    mSwitch.begin();
    button = 0;
}

void loop() {
    bool pressed = mSwitch.getButton(&button);
    if(pressed)
        Serial.println(mSwitch.toString(button));
}
