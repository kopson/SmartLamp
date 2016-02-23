#include "MembraneSwitch.h"

MembraneSwitch::MembraneSwitch(const byte pin) {
	buttonPin = pin;
}

void MembraneSwitch::begin() {
    pinMode(buttonPin, INPUT);
    lastButtonState = 0;
    lastDebounceTime = 0;
}

bool MembraneSwitch::getButton(byte *button) {
    int analogValue = analogRead(buttonPin);  
    byte tmpButtonState = 0;

    if (analogValue > AUTO_MIN && analogValue < AUTO_MAX) {     
        tmpButtonState = AUTO;  
    } else if (analogValue > MENU_MIN && analogValue < MENU_MAX) {       
        tmpButtonState = MENU;     
    } else if (analogValue > LEFT_MIN && analogValue < LEFT_MAX) {     
        tmpButtonState = LEFT; 
    } else if (analogValue > RIGHT_MIN && analogValue < RIGHT_MAX) { 
        tmpButtonState = RIGHT; 
    } else if (analogValue > POWER_MIN && analogValue < POWER_MAX) {    
        tmpButtonState = POWER;     
    } else {     
        tmpButtonState = RELEASE; 
    }

    // If the switch changed, due to noise or pressing:
    if (tmpButtonState != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
        lastButtonState = tmpButtonState;
    } 

    if ((millis() - lastDebounceTime) > DELAY) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:
        //lastButtonState = 0;
        if(*button != tmpButtonState) {
            *button = tmpButtonState;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

String MembraneSwitch::toString(byte button) {
    switch(button) {
        case AUTO:     
            return "AUTO";
        case MENU:    
            return "MENU";        
        case LEFT: 
            return "LEFT";    
        case RIGHT: 
            return "RIGHT";
        case POWER: 
            return "POWER";    
        case UNKNOWN_STATE: 
            return "UNKNOWN_STATE"; 
        case RELEASE: 
            return "RELEASE"; 
    }
    return "";
}
