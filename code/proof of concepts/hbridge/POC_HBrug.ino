// 1) Vooruit: volle snelheid -> langzaam (255 -> 0)
// 2) Kort pauze
// 3) Achteruit: langzaam -> volle snelheid (0 -> 255)
// 4) 1 seconde pauze, dan opnieuw

const int PIN_AIN1 = 7;
const int PIN_AIN2 = 8;
const int PIN_PWMA = 11;

const int PIN_BIN1 = 9;
const int PIN_BIN2 = 10;
const int PIN_PWMB = 5;

const int PIN_STBY = 6;

const int STEP = 5;
const int STEP_DELAY = 25;
const int SHORT_PAUSE_MS = 300;
const int PAUSE_MS = 1000;
const int MOTOR_B_DELAY = 300;  // eenvoudige vertraging

void setup() {
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_PWMA, OUTPUT);

  pinMode(PIN_BIN1, OUTPUT);
  pinMode(PIN_BIN2, OUTPUT);
  pinMode(PIN_PWMB, OUTPUT);

  pinMode(PIN_STBY, OUTPUT);
  digitalWrite(PIN_STBY, HIGH);
}

void loop() {
  // --- Vooruit ---
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, LOW);
  digitalWrite(PIN_BIN1, HIGH);
  digitalWrite(PIN_BIN2, LOW);

  // Motor A start direct
  for (int s = 255; s >= 0; s -= STEP) {
    analogWrite(PIN_PWMA, s);
    delay(STEP_DELAY);
  }

  // Kleine vertraging vóór motor B
  delay(MOTOR_B_DELAY);

  for (int s = 255; s >= 0; s -= STEP) {
    analogWrite(PIN_PWMB, s);
    delay(STEP_DELAY);
  }

  // korte pauze
  analogWrite(PIN_PWMA, 0);
  analogWrite(PIN_PWMB, 0);
  delay(SHORT_PAUSE_MS);

  // --- Achteruit ---
  digitalWrite(PIN_AIN1, LOW);
  digitalWrite(PIN_AIN2, HIGH);
  digitalWrite(PIN_BIN1, LOW);
  digitalWrite(PIN_BIN2, HIGH);

  // Motor A start weer direct
  for (int s = 0; s <= 255; s += STEP) {
    analogWrite(PIN_PWMA, s);
    delay(STEP_DELAY);
  }

  // Motor B wacht even
  delay(MOTOR_B_DELAY);

  for (int s = 0; s <= 255; s += STEP) {
    analogWrite(PIN_PWMB, s);
    delay(STEP_DELAY);
  }

  // Pauze tussen herhalingen
  analogWrite(PIN_PWMA, 0);
  analogWrite(PIN_PWMB, 0);
  delay(PAUSE_MS);
}