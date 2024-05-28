#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define RS_PIN PA0
#define RW_PIN PA1
#define ENABLE_PIN PA2
#define D4_PIN PA3
#define D5_PIN PA4
#define D6_PIN PA5
#define D7_PIN PA6
#define ONEWIRE_BUS PB3

#define DHTPIN PB4
#define DHTTYPE DHT11

LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONEWIRE_BUS);
DallasTemperature sensor(&oneWire);

void setup()
{
  sensor.begin();
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // old sensor 2
  sensor.requestTemperatures();
  float t2 = sensor.getTempCByIndex(0);

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float t_avg = (t + t2) / 2;

  float hic = dht.computeHeatIndex(t_avg, h, false);

  lcd.setCursor(0, 0);
  // print the temperature in Celsius
  lcd.print("T:");
  lcd.print(t);
  lcd.print(" ");
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(temp);
  lcd.print("HI:");
  lcd.print(hic);
  lcd.print(" ");
  lcd.print("d:");
  lcd.print(t-t2);

  delay(1500);
}