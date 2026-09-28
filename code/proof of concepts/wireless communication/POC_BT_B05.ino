const int bluetoothRX = 1;   
const int bluetoothTX = 0;

void setup() {
  Serial.begin(9600);      // PC ↔ Serial Monitor
  Serial1.begin(9600);     // HC-05 ↔ Arduino

  Serial.println("Wacht op Bluetooth...");
}

bool connected = false;

void loop() {
  // Ontvang data van Bluetooth
  if (Serial1.available()) {
    if (!connected) {
      connected = true;
      Serial.println("Bluetooth verbonden!");
    }

    char c = Serial1.read();
    Serial.print("Ontvangen: ");
    Serial.println(c);
  }

  // Verstuur data van Serial Monitor naar Bluetooth
  if (Serial.available()) {
    char c = Serial.read();
    Serial1.write(c);
  }
}