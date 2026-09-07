#define BLYNK_TEMPLATE_ID "TMPL3FZcDj0jZ"
#define BLYNK_TEMPLATE_NAME "Smart Energy Safety"
#define BLYNK_AUTH_TOKEN "_IBLmrZ4jCoJNgJKZWUsOiJQgwn5iVKX"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- WiFi ----------
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------- PIN CONFIGURATION ----------
#define DHTPIN 4
#define DHTTYPE DHT22

#define RELAY_PIN 18
#define LED_PIN 19
#define BUZZER_PIN 5

#define PIR_PIN 27
#define LDR_PIN 34
#define GAS_PIN 35

// ---------- OBJECTS ----------
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

// ---------- THRESHOLDS ----------
#define TEMP_LIMIT 30.0
#define LDR_LIMIT 2000
#define GAS_LIMIT 2500

// ---------- SEND DATA TO BLYNK ----------
void sendSensorData()
{
  // ---------- READ SENSORS ----------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int pirValue = digitalRead(PIR_PIN);
  int ldrValue = analogRead(LDR_PIN);
  int gasValue = analogRead(GAS_PIN);

  // ---------- DHT ERROR ----------
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT22 ERROR!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT22 ERROR!");

    return;
  }

  // ---------- OCCUPANCY ----------
  bool personDetected = (pirValue == HIGH);

  // ---------- SMART FAN ----------
  bool fanON = false;

  if (personDetected && temperature > TEMP_LIMIT)
  {
    fanON = true;
  }

  digitalWrite(RELAY_PIN, fanON ? HIGH : LOW);

  // ---------- SMART LIGHT ----------
  bool lightON = false;

  if (personDetected && ldrValue < LDR_LIMIT)
  {
    lightON = true;
  }

  digitalWrite(LED_PIN, lightON ? HIGH : LOW);

  // ---------- GAS SAFETY ----------
  bool gasAlert = (gasValue > GAS_LIMIT);

  if (gasAlert)
  {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // =================================================
  // SEND DATA TO BLYNK
  // =================================================

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, personDetected ? 1 : 0);
  Blynk.virtualWrite(V3, fanON ? 1 : 0);
  Blynk.virtualWrite(V4, lightON ? 1 : 0);
  Blynk.virtualWrite(V5, gasValue);
  Blynk.virtualWrite(V6, gasAlert ? 1 : 0);

  // ---------- SERIAL MONITOR ----------
  Serial.println("==========================");

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Occupancy: ");
  Serial.println(personDetected ? "OCCUPIED" : "EMPTY");

  Serial.print("LDR: ");
  Serial.println(ldrValue);

  Serial.print("Gas: ");
  Serial.println(gasValue);

  Serial.print("Fan: ");
  Serial.println(fanON ? "ON" : "OFF");

  Serial.print("Light: ");
  Serial.println(lightON ? "ON" : "OFF");

  Serial.print("Gas Status: ");
  Serial.println(gasAlert ? "DANGER" : "SAFE");

  // ---------- LCD ----------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);

  if (gasAlert)
  {
    lcd.print("GAS ALERT!");
  }
  else
  {
    lcd.print("P:");
    lcd.print(personDetected ? "ON " : "OFF");

    lcd.print(" F:");
    lcd.print(fanON ? "ON " : "OFF");

    lcd.print(" L:");
    lcd.print(lightON ? "ON" : "OFF");
  }
}

// ---------- SETUP ----------
void setup()
{
  Serial.begin(115200);

  // ---------- PIN MODES ----------
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // ---------- DHT ----------
  dht.begin();

  // ---------- I2C ----------
  Wire.begin(21, 22);

  // ---------- LCD ----------
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SMART ENERGY");

  lcd.setCursor(0, 1);
  lcd.print("SAFETY SYSTEM");

  delay(2000);

  lcd.clear();

  // ---------- BLYNK ----------
  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk Connected!");

  // Send sensor data every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

// ---------- LOOP ----------
void loop()
{
  Blynk.run();
  timer.run();
}