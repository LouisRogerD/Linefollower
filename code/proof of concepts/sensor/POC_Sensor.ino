// HY-S301 8x IR Sensor Module - Analog Light/Dark Detection
// Using 6 analog channels (A0–A5) on Arduino Leonardo

const int sensorPins[6] = {A0, A1, A2, A3, A4, A5};
int sensorValues[6];
const int IRpin = 8;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor (Leonardo only)
  pinMode(8,OUTPUT);
  Serial.println("HY-S301 Analog IR Sensor (6 channels on A0–A5) Ready");
}

void loop() {
  digitalWrite(8,HIGH);
  Serial.print("Sensor values: ");

  for (int i = 0; i < 6; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }

  Serial.println();

  delay(200);
}