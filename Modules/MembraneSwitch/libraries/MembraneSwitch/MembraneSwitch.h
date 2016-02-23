#ifndef _MEMBRANE_SWITCH_h_
#define _MEMBRANE_SWITCH_h_

#include <inttypes.h>
#include <Arduino.h>

#define AUTO_MIN 750
#define AUTO_MAX 850
#define MENU_MIN 650
#define MENU_MAX 750
#define LEFT_MIN 850
#define LEFT_MAX 950
#define RIGHT_MIN 550
#define RIGHT_MAX 650
#define POWER_MIN 450
#define POWER_MAX 550
#define ZERO_MARGIN 50

#define AUTO 1
#define MENU 2
#define LEFT 3
#define RIGHT 4
#define POWER 5
#define UNKNOWN_STATE 6
#define RELEASE 0

#define DELAY 100 

class MembraneSwitch
{
public:
	MembraneSwitch(const byte pin);
	void begin();
	bool getButton(byte *button);
	String toString(byte button);
private:
	byte buttonPin;
	byte lastButtonState;     // previous state of the button
 	long lastDebounceTime;  // the last time the output pin was toggled
};
#endif