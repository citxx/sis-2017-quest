const int RELAY_PIN = 2;
const int EMERGENCY_PIN = 3;
const int RED_LED_PIN = 8;
const int GREEN_LED_PIN = 9;
const int BUTTONS_NUMBER = 4;
const int BUTTON_PINS[BUTTONS_NUMBER] = {4, 5, 6, 7};
const int BLINK_INTERVALS[BUTTONS_NUMBER] = {0, 900, 300, 100};
const int INTERVAL = 30000;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(EMERGENCY_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  for (int i = 0; i < BUTTONS_NUMBER; ++i) {
    pinMode(BUTTON_PINS[i], INPUT);
  }
  
  digitalWrite(RED_LED_PIN, HIGH);
  Serial.begin(9600);
}

void unlock() {
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(INTERVAL);
  digitalWrite(RELAY_PIN, LOW);    
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {
  if (digitalRead(EMERGENCY_PIN) == HIGH) {
    unlock();
    return;
  }
  int activeButtonsCount = 0;
  for (int i = 0; i < BUTTONS_NUMBER; ++i) {
    activeButtonsCount += (digitalRead(BUTTON_PINS[i]) == HIGH);
  }
  if (activeButtonsCount == BUTTONS_NUMBER) {
    unlock();
    delay(50);
  } else {
    int interval = BLINK_INTERVALS[activeButtonsCount];
    if (interval) {
      digitalWrite(RED_LED_PIN, LOW);
      delay(interval);
      digitalWrite(RED_LED_PIN, HIGH);
      delay(interval);
    } else {
      delay(50);
    }
  }
}
