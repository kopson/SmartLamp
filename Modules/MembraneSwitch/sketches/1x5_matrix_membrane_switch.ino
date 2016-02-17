
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A3);

  if(sensorValue > 800 && sensorValue < 850)
    Serial.println("AUTO");
  else if (sensorValue > 660 && sensorValue < 750)
    Serial.println("MENU");
  else if (sensorValue > 900 && sensorValue < 950)
    Serial.println("LEFT");
  else if (sensorValue > 560 && sensorValue < 650)
      Serial.println("RIGHT");
  else if (sensorValue > 500 && sensorValue < 550)
    Serial.println("POWER");
  else if (sensorValue > 10)
    Serial.println("ERROR");
    
  delay(200);
}
