#include <Timer.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <LiquidCrystal.h> 

#define DEBUG           0
 
#define ONEWIRE_PIN     8
#define DIODE_PIN       9
#define ANALOG_READ_PIN A0

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

Timer t;

#define MAX_ANALOG      1023
#define MAX_PWM         255
#define LCD_TIMEOUT     4000 //msec
#define UPDATE_TIMEOUT  100 //msec

// Adres czujnika
byte address[8] = {0x28, 0x5C, 0xAB, 0x52, 0x7, 0x0, 0x0, 0xAB};

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int prevAverage = 0;

int brightness;

bool screenLedInit;
bool screenTempInit;

int afterEvent;
int tickEvent;

void initLCDTemp() {

  t.stop(tickEvent);
  
#if DEBUG  
  Serial.println("Reset tick event");
#endif
  
  if(screenTempInit)
    return;

#if DEBUG  
  Serial.println("initLCDTemp");
#endif
  
  screenTempInit = true;
  screenLedInit = false;
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp. wody:");

  updateTemp();
}

void updateTemp() {
  
  if (sensors.available()) {
    float temperature = sensors.readTemperature(address);

#if DEBUG
    Serial.print(temperature);
    Serial.println(F(" 'C"));
#endif

    if (screenTempInit) {
      lcd.setCursor(0, 1);
      lcd.print(String(temperature, 2) + " 'C ");
    }
    sensors.request(address);
  }
}

void initLCDDiode() {

  if(screenLedInit)
    return;

  tickEvent = t.every(UPDATE_TIMEOUT, updateDiode);

#if DEBUG
  Serial.println("initLCDDiode");
#endif

  screenLedInit = true;
  screenTempInit = false;
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moc diody:");

  updateDiode();
}

void updateDiode() {
  
  lcd.setCursor(0, 1);
  float led = (float) brightness * 100.00 / MAX_PWM;
    
  lcd.print(String(led, 1) + " % ");

#if DEBUG    
  Serial.print("Brightness ");
  Serial.print(brightness);
  Serial.print(" average ");
  Serial.println(average);
#endif
}

void setup() {

  screenTempInit = false;
  screenLedInit = false;

#if DEBUG
  while(!Serial);
  Serial.begin(9600);
#endif

  sensors.begin();
  sensors.request(address);

  initLCDTemp();

  pinMode(DIODE_PIN, OUTPUT);

  average = analogRead(ANALOG_READ_PIN);
  prevAverage = average;
  brightness = map(average, 0, MAX_ANALOG, 0, MAX_PWM);
  analogWrite(DIODE_PIN, brightness);
    
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = average;
    total += average;
  }
}

void loop() {
  
  updateTemp();

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(ANALOG_READ_PIN);

  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  
  if(abs(prevAverage - average) > 2) {
    
    brightness = map(average, 0, MAX_ANALOG, 0, MAX_PWM);
    analogWrite(DIODE_PIN, brightness);
    t.stop(afterEvent); 
    afterEvent = t.after(LCD_TIMEOUT, initLCDTemp);

    initLCDDiode();
    prevAverage = average;
  }

  delay(50);
  t.update();
}
