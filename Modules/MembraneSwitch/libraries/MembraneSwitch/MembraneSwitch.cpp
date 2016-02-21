#include "MembraneSwitch.h"

MembraneSwitch::MembraneSwitch(const byte pin) {
	buttonPin = pin;
}

void MembraneSwitch::begin() {
    pinMode(buttonPin, INPUT);
    for (byte i = 0; i < UNKNOWN_STATE; ++i) 
        counter[i] = 0;
    buttonState = 0;
    lastButtonState = 0;
}

byte MembraneSwitch::getButton() {
    int analogValue = analogRead(buttonPin);  
    byte ret = 0;
    if (analogValue > AUTO_MIN && analogValue < AUTO_MAX) {     
        if (counter[AUTO]++ >= 5)
            buttonState = AUTO;  
    } else if (analogValue > MENU_MIN && analogValue < MENU_MAX) {       
        if (counter[MENU]++ >= 5)
            buttonState = MENU;     
    } else if (analogValue > LEFT_MIN && analogValue < LEFT_MAX) {     
        if (counter[LEFT]++ >= 5)
            buttonState = LEFT; 
    } else if (analogValue > RIGHT_MIN && analogValue < RIGHT_MAX) { 
        if (counter[RIGHT]++ >= 5)
            buttonState = RIGHT; 
    } else if (analogValue > POWER_MIN && analogValue < POWER_MAX) {    
        if (counter[POWER]++ >= 5)
            buttonState = POWER;     
    } else {     
        buttonState = RELEASE; 
    }

    if (buttonState != lastButtonState) {
        for (byte i = 0; i < UNKNOWN_STATE; ++i) 
            counter[i] = 0;
        ret = buttonState;
        delay(100);
    }
    lastButtonState = buttonState;
    return ret;
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

bool MembraneSwitch::available(byte button) {
	return button > RELEASE && button < UNKNOWN_STATE;
}