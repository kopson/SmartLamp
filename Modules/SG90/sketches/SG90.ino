#include <Servo.h>

Servo sg90;

void setup() { 
    sg90.attach(2); 
}

void loop() {
    sg90.writeMicroseconds(450);   
    delay(500);
    sg90.writeMicroseconds(1450);   
    delay(500);      
    sg90.writeMicroseconds(2450);   
    delay(500);      
    sg90.writeMicroseconds(1450);   
    delay(500); 
}