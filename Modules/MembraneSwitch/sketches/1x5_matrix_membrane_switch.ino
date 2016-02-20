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

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int counter[UNKNOWN_STATE];
int globalCounter;

void setup() {
    Serial.begin(9600);
    pinMode(A3, INPUT);
    for (int i = 0; i < UNKNOWN_STATE; ++i) 
        counter[i] = 0;
    globalCounter = 0;
}

void loop() {
    int analogValue = analogRead(A3);
    //Serial.println(analogValue);   

    if (analogValue > AUTO_MIN && analogValue < AUTO_MAX) {     
        if (globalCounter++ >= 10 && counter[AUTO]++ >= 5)
            buttonState = AUTO;  
    } else if (analogValue > MENU_MIN && analogValue < MENU_MAX) {       
        if (globalCounter++ >= 10 && counter[MENU]++ >= 5)
            buttonState = MENU;     
    } else if (analogValue > LEFT_MIN && analogValue < LEFT_MAX) {     
        if (globalCounter++ >= 10 && counter[LEFT]++ >= 5)
            buttonState = LEFT; 
    } else if (analogValue > RIGHT_MIN && analogValue < RIGHT_MAX) { 
        if (globalCounter++ >= 10 && counter[RIGHT]++ >= 5)
            buttonState = RIGHT; 
    } else if (analogValue > POWER_MIN && analogValue < POWER_MAX) {    
        if (globalCounter++ >= 10 && counter[POWER]++ >= 5)
            buttonState = POWER;    
    } else if (analogValue > ZERO_MARGIN) {     
        if (globalCounter++ >= 10) {
            buttonState = UNKNOWN_STATE;   
        }    
    } else {     
        buttonState = RELEASE; 
    }

    if (buttonState != lastButtonState) {
        globalCounter = 0;
        for (int i = 0; i < UNKNOWN_STATE; ++i) 
            counter[i] = 0;
        switch(buttonState) {
            case AUTO:     
                Serial.println("AUTO");
                break;     
            case MENU:    
                Serial.println("MENU");      
                break;    
            case LEFT: 
                Serial.println("LEFT");
                break;         
            case RIGHT: 
                Serial.println("RIGHT");
                break;
            case POWER: 
                Serial.println("POWER");    
                break;
        }
        delay(100);
    }
    lastButtonState = buttonState;
}
