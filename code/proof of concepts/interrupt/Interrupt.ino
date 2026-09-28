const int buttonPin = 2;
const int ledPin    = 6;

volatile bool running = true;      

unsigned long previousMillis = 0;
const long interval = 500;

volatile unsigned long lastButtonTime = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), stopLed, FALLING);
}

void loop() {
  if (running) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin)); // toggle LED
    }
  } else {
    digitalWrite(ledPin, LOW); // LED uit
  }
}

void stopLed() {
  unsigned long currentTime = millis();
  if (currentTime - lastButtonTime > 50) {
    running = false;
    lastButtonTime = currentTime;
  }
}