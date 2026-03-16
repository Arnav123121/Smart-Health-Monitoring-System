#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_ADXL345_U.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// === LCD Setup ===
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address for LCD is 0x27

// === WiFi Credentials ===
const char* ssid = "Redmi_Pad_SE";
const char* password = "ydyspmvf7kctij5";

// === Telegram Credentials ===
#define BOT_TOKEN "7661851693:AAGsbHfDIeZ0RV3GKNqCCkAnBFuv01Z5rfQ"
#define CHAT_ID "5665239219"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// === Sensor Pins ===
#define TEMP_PIN 13       // DS18B20
#define ECG_PIN 36        // Analog ECG Sensor
#define IR_PIN 32         // IR Blink Sensor
#define BUZZER_PIN 25
#define LED_PIN 26

// === Sensors ===
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// === Global Variables ===
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 10000;
int ecgValue;
float temperature;
int blinkStatus;
float ax, ay, az;

void printToSerial(float temperature, int ecgValue, int blinkStatus, float ax, float ay, float az) {
  Serial.println("=== Sensor Readings ===");
  Serial.print("🌡 Temp: "); Serial.print(temperature, 1); Serial.println(" °C");
  Serial.print("❤️ ECG: "); Serial.println(ecgValue);
  Serial.print("👁 Blink: "); Serial.println(blinkStatus ? "YES" : "NO");
  Serial.print("📐 AX: "); Serial.print(ax, 2); Serial.print(" AY: "); Serial.print(ay, 2); Serial.print(" AZ: "); Serial.println(az, 2);
  Serial.println("=======================");
  Serial.println();
  Serial.println(ecgValue); // For serial plotter
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  secured_client.setInsecure();
}

void setup() {
  Serial.begin(115200);

  // === I2C Init (default Wire on GPIO 21/22) ===
  Wire.begin();  // SDA = 21, SCL = 22 (default for ESP32)

  // === LCD Init ===
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Health Monitor");

  // === Pin Setup ===
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  tempSensor.begin();

  // === Accelerometer Init ===
  if (!accel.begin()) {
    Serial.println("ADXL345 not found. Check wiring.");
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("ADXL345 Error");
    while (1);
  }

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();  // Reconnect if disconnected
  }

  // === Read Sensors ===
  ecgValue = analogRead(ECG_PIN);
  tempSensor.requestTemperatures();
  temperature = tempSensor.getTempCByIndex(0);
  blinkStatus = digitalRead(IR_PIN);

  sensors_event_t event;
  accel.getEvent(&event);
  ax = event.acceleration.x;
  ay = event.acceleration.y;
  az = event.acceleration.z;

  // === LCD Display ===
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temperature, 1); lcd.print("C ");
  lcd.print("B:"); lcd.print(blinkStatus ? "Y" : "N");

  lcd.setCursor(0, 1);
  lcd.print("AX:"); lcd.print(ax, 0); lcd.print(" AY:"); lcd.print(ay, 0); lcd.print(" ");

  // === Alert System ===
  if (temperature > 38.0 || blinkStatus == 0) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("!! ALERT MODE !! ");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  // === Serial Monitor ===
  printToSerial(temperature, ecgValue, blinkStatus, ax, ay, az);

  // === Telegram Update ===
  if (millis() - lastSendTime > sendInterval) {
    String msg = "📡 *Health Parameters*\n";
    msg += "🌡 Temp: " + String(temperature, 1) + " °C\n";
    msg += "❤️ ECG: " + String(ecgValue) + "\n";
    msg += "👁 Blink: " + String(blinkStatus ? "YES" : "NO") + "\n";
    msg += "📐 AX: " + String(ax, 2) + " AY: " + String(ay, 2) + " AZ: " + String(az, 2);
    bot.sendMessage(CHAT_ID, msg, "Markdown");
    lastSendTime = millis();
  }

  delay(500);
}