const int ledPin = 2;

const int sensorPin = 34;
const int buttonPin = 13;

int triggerLevel = 1940;

int ledState = LOW;
int lastButtonState = HIGH;

unsigned long lastToggleTime = 0;
unsigned long inputCooldown = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  pinMode(buttonPin, INPUT_PULLUP);
  lastButtonState = digitalRead(buttonPin);
  
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  int newButtonState = digitalRead(buttonPin);
  unsigned long currentTime = millis();

  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(triggerLevel);

  if (currentTime - lastToggleTime < inputCooldown) {
    lastButtonState = newButtonState;
    delay(10);
    return;
  }

  if (newButtonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button pushed.");
    toggleLED(currentTime);
  } 
  else if (sensorValue > triggerLevel) {
    Serial.println("You blinked.");
    toggleLED(currentTime);
  }
  
  lastButtonState = newButtonState;
  
  delay(7);
}

void toggleLED(unsigned long time) {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
      
  lastToggleTime = time;
}