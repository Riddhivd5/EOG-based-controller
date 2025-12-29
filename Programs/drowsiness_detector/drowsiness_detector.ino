const int sensorPin = 34;

const int blinkLedPin = 2;
const int alarmPin = 4;

int triggerLevel = 1900;
unsigned long drowsinessThreshold = 1000;

bool isBlinking = false;
unsigned long blinkStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(blinkLedPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  
  digitalWrite(blinkLedPin, LOW);
  digitalWrite(alarmPin, LOW);
  
  Serial.println("Drowsiness Detector Initialized.");
  Serial.print("Trigger Level: "); Serial.println(triggerLevel);
  Serial.print("Drowsy Threshold: "); Serial.println(drowsinessThreshold);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  unsigned long currentTime = millis();

  if (sensorValue > triggerLevel && !isBlinking) {
    isBlinking = true;
    blinkStartTime = currentTime;
    
    digitalWrite(blinkLedPin, HIGH); 
  }

  if (sensorValue < triggerLevel && isBlinking) {
    isBlinking = false;
    
    unsigned long blinkDuration = currentTime - blinkStartTime;
    
    digitalWrite(blinkLedPin, LOW);

    Serial.print("Blink Duration: ");
    Serial.print(blinkDuration);
    Serial.println(" ms");

    if (blinkDuration > drowsinessThreshold) {
      Serial.println("DROWSINESS DETECTED");
      
      for (int i = 0; i < 3; i++) {
        digitalWrite(alarmPin, HIGH);
        delay(250);
        digitalWrite(alarmPin, LOW);
        delay(150);
      }
    }
  }
}