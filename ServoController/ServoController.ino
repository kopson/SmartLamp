#include <Servo.h>

#define ANGLE_0   450
#define ANGLE_90  1450
#define ANGLE_180 2450
#define AXIS_MIN  0
#define AXIS_MAX  1023
#define AXIS_MEAN 512
#define AXIS_MARGIN 50

Servo sg90;

int JoyStick_X = A0;    // x
int JoyStick_Y = A1;    // y
int JoyStick_Z = 3;     // key
int Servo_Data = 2;

void setup() { 
    sg90.attach(Servo_Data);
    pinMode(JoyStick_X, INPUT);
    pinMode(JoyStick_Y, INPUT);
    pinMode(JoyStick_Z, INPUT_PULLUP);
    Serial.begin(9600); // 9600 bps
    sg90.writeMicroseconds(ANGLE_90);
}

void loop() {
    int x, y, z;
    x = analogRead(JoyStick_X);
    y = analogRead(JoyStick_Y);
    z = digitalRead(JoyStick_Z);

    int mapped = map(x, AXIS_MIN, AXIS_MAX, ANGLE_0, ANGLE_180);

	sg90.writeMicroseconds(mapped);

    delay(100);
}

void servoCtrl(int x) {
	if(x < AXIS_MIN + AXIS_MARGIN) {
    	Serial.print(x, DEC);
    	Serial.println("MIN");
    	sg90.writeMicroseconds(ANGLE_0);
    } else if(x > AXIS_MAX - AXIS_MARGIN) {
    	Serial.print(x, DEC);
    	Serial.println("MAX");
    	sg90.writeMicroseconds(ANGLE_180);
    } else {
    	Serial.print(x, DEC);
    	Serial.println("MEAN");
    	sg90.writeMicroseconds(ANGLE_90);
    }
}