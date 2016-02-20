#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DS18B20.h>
#include <DS3231.h>
#include <Interface.h>

// #### PINS ####
#define LCD_RS_PIN  2
#define LCD_E_PIN   3
#define LCD_D4_PIN  4
#define LCD_D5_PIN  5
#define LCD_D6_PIN  6
#define LCD_D7_PIN  7

#define DS18B20_PIN     8
#define LED_DRIVER_PIN  9
#define SWITCH_PIN      A3

// #### PARAMETERS ####
#define LCD_ROWS 2
#define LCD_COLS 16

const byte address[ADDR_SIZE] PROGMEM = {0x28, 0x5C, 0xAB, 0x52, 0x7, 0x0, 0x0, 0xAB};

// #### COMPONENTS ####
Interface interface;
LiquidCrystal lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
OneWire oneWire(DS18B20_PIN);
DS18B20 sensor(&oneWire);
DS3231 rtc(SDA, SCL);

// #### IMPLEMENTATION ####

// #### MAIN PART ####
void setup() {
#if DEBUG 
    while(!Serial);
    Serial.begin(9600);
#endif

    interface.initDisplay(&lcd, LCD_COLS, LCD_ROWS);
    interface.initTempSensor(&sensor, address);
    interface.initRTC(&rtc);
    interface.initSwitch(LED_DRIVER_PIN);
    interface.displayDate(0);
    interface.displayTemp(1);
#if DEBUG     
    Serial.println("Initialized");
#endif    
}

void loop() {
    interface.handleSwitch(SWITCH_PIN);
    delay(500);
}