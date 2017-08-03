const int RELAY_PIN = 2;
const int BUTTONS_PIN = 3;
const int RED_LED_PIN = 8;
const int GREEN_LED_PIN = 9;
const int INTERVAL = 30000;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTONS_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
  digitalWrite(RED_LED_PIN, HIGH);
//  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTONS_PIN) == HIGH) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(INTERVAL);
    digitalWrite(RELAY_PIN, LOW);    
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    delay(50);
  }
}
