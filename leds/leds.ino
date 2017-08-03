const int LEDS_NUMBER = 4;
const int LED_PINS[LEDS_NUMBER] =  {2, 3, 4, 5};

const int BUTTONS_NUMBER = 4;
const int BUTTON_PINS[BUTTONS_NUMBER] = {8, 9, 10, 11};
const int BUTTON_PATTERNS[BUTTONS_NUMBER][LEDS_NUMBER] = {
  {1, 0, 1, 1},
  {0, 1, 1, 1},
  {0, 0, 1, 0},
  {0, 1, 1, 0},
};


const int CODE_LENGTH = 4;
const int CODE[CODE_LENGTH] = {3, 8, 2, 5};
const int BLINK_INTERVAL = 300;
const int DIGIT_INTERVAL = 1000;
const int CODE_INTERVAL = 4000;

int ledStates[LEDS_NUMBER] = {LOW, LOW, LOW, LOW};
int lastButtonStates[BUTTONS_NUMBER] = {LOW, LOW, LOW, LOW};
int mode = 0;

void setup() {
  // set the digital pin as output:
  for (int i = 0; i < LEDS_NUMBER; ++i) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < BUTTONS_NUMBER; ++i) {
    pinMode(BUTTON_PINS[i], INPUT);
  }
//  Serial.begin(9600);
}

void setAllLeds(int state) {
  for (int i = 0; i < LEDS_NUMBER; ++i) {
    digitalWrite(LED_PINS[i], state);
  }
}

void blinkNumber(int n) {
  for (int i = 0; i < n; ++i) {
    if (i > 0) delay(BLINK_INTERVAL);
    setAllLeds(HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK_INTERVAL);
    setAllLeds(LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void switchLeds(int patternNumber) {
  for (int i = 0; i < LEDS_NUMBER; ++i) {
    if (BUTTON_PATTERNS[patternNumber][i]) {
      ledStates[i] = ledStates[i] == LOW ? HIGH : LOW;
      digitalWrite(LED_PINS[i], ledStates[i]);
    }
  }
  
}

bool allLedsOn() {
  for (int i = 0; i < LEDS_NUMBER; ++i) {
    if (ledStates[i] == LOW) return false;
  }
  return true;
}

int iteration = 0;
void loop() {
  if (mode == 0) {
    iteration++;
    // Switching leds using pattern
    for (int i = 0; i < BUTTONS_NUMBER; ++i) {
      int newState = digitalRead(BUTTON_PINS[i]);
      if (newState == HIGH && lastButtonStates[i] == LOW) {
        switchLeds(i);
      }
      lastButtonStates[i] = newState;
    }
    if (iteration % 10 == 0) {
      for (int i = 0; i < LEDS_NUMBER; ++i) {
        Serial.print(ledStates[i], " ");
      }
      Serial.println();
    }
    delay(50); // Small delay to ignore bouncing
    
    if (allLedsOn()) {
      mode = 1;
    }
  }

  if (mode == 1) {
    // Showing code
    for (int i = 0; i < CODE_LENGTH; ++i) {
      blinkNumber(CODE[i]);
      if (i < CODE_LENGTH - 1) delay(DIGIT_INTERVAL);
    }
    delay(CODE_INTERVAL);
  }
}

