#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RS_PIN PA0
#define RW_PIN PA1
#define ENABLE_PIN PA2
#define D4_PIN PA3
#define D5_PIN PA4
#define D6_PIN PA5
#define D7_PIN PA6
#define ONEWIRE_BUS PB4

LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
OneWire oneWire(ONEWIRE_BUS);
DallasTemperature sensor(&oneWire);

void setup()
{
  sensor.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
}

void loop()
{
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(temp);
  lcd.print("C");
  delay(1000);
}