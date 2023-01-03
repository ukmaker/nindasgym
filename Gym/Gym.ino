/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Blue wire is DIR, Green is STEP
#define DIR_PIN 8
#define STEP_PIN 9
#define STEP_DELAY_MS 6

// green red blue yellow

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

void step(bool up) {
    digitalWrite(DIR_PIN, up ? HIGH : LOW);
    digitalWrite(STEP_PIN, HIGH);
    delay(STEP_DELAY_MS);
    digitalWrite(STEP_PIN, LOW);
    delay(STEP_DELAY_MS);
}

void setup() {
  // Declare pins as output:
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Fade each colour up one by one
  analogWrite(RED_PIN,0);    
  analogWrite(GREEN_PIN,0);    
  analogWrite(BLUE_PIN,0);
      
  for(int i=0; i< 256; i++) {
    analogWrite(RED_PIN,i);
    delay(5);
    step(true);
  }
  for(int i=0; i< 256; i++) {
    analogWrite(GREEN_PIN,i);
    delay(5);
    step(false);
  }
  for(int i=0; i< 256; i++) {
    analogWrite(BLUE_PIN,i);
    delay(5);
  }
}
