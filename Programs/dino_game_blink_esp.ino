#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32-Dino", "Hackathon", 100);

const int sensorPin = 34;
const int ledPin = 2;

int triggerLevel = 1950;

unsigned long lastBlinkTime = 0;
unsigned long blinkCooldown = 500;

int ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    int sensorValue = analogRead(sensorPin);
    unsigned long currentTime = millis();

    Serial.print(sensorValue);
    Serial.print(" ");
    Serial.println(triggerLevel);

    if (sensorValue > triggerLevel && (currentTime - lastBlinkTime > blinkCooldown)) {
      bleKeyboard.write(' ');
      lastBlinkTime = currentTime;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
  delay(10);
}
