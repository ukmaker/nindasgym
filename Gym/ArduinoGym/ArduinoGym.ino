/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Blue wire is DIR, Green is STEP
#define DIR_PIN 8
#define STEP_PIN 9
#define STEP_DELAY_MS 6

#define MP3_TX_PIN A4
#define MP3_RX_PIN A3

#define OPEN_PIN A0
#define TOP_PIN A1
#define BOTTOM_PIN A2

#define SAMPLE_PIN A5
#define BUSY_PIN 2

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

#define LED_PIN 7

#define DOOR_CLOSED 0
#define DOOR_OPEN 2

#define LID_CLOSED 0
#define LID_RAISING 1
#define LID_OPEN 2
#define LID_LOWERING 3

// milliseconds until the line "Rising up..."
#define RISING_UP 50000

uint8_t door;
uint8_t lid;
unsigned long time;
uint8_t stepDiv;

SoftwareSerial mySoftwareSerial(MP3_RX_PIN, MP3_TX_PIN);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


void openLid() {
Serial.println("openLid");
           step(true);
}

void closeLid() {
 Serial.println("closeLid");
          step(false);
}

void step(bool up) {
  stepDiv++;
  if(stepDiv < 10) return;
  stepDiv = 0;
  digitalWrite(DIR_PIN, up ? LOW : HIGH);
  digitalWrite(STEP_PIN, HIGH);
  delay(STEP_DELAY_MS);
  digitalWrite(STEP_PIN, LOW);
  delay(STEP_DELAY_MS);
}

void setup() {

  Serial.begin(115200);

  pinMode(TOP_PIN, INPUT_PULLUP);
  pinMode(BOTTOM_PIN, INPUT_PULLUP);
  pinMode(OPEN_PIN, INPUT_PULLUP);
  pinMode(BUSY_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,1);
  delay(1000);
  digitalWrite(LED_PIN,0);
  delay(200);
  digitalWrite(LED_PIN,1);
  delay(200);
  digitalWrite(LED_PIN,0);
  delay(200);
  digitalWrite(LED_PIN,1);

  // wait to give the MP3 player time to initialize
  delay(3000);

  mySoftwareSerial.begin(9600);
  
  door = DOOR_CLOSED;
  lid = LID_CLOSED;
  time = millis();
  stepDiv = 0;

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
    delay(200);
  digitalWrite(LED_PIN,0);
  delay(200);
  digitalWrite(LED_PIN,1);
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(28);  //Set volume value. From 0 to 30
  myDFPlayer.EQ(5);
}

void loop() {

  if (digitalRead(OPEN_PIN) == 0) {
    if (door == DOOR_CLOSED) {
      door = DOOR_OPEN;
      myDFPlayer.play(1);  //Play the first mp3
      time = millis();
      lid = LID_CLOSED;
      Serial.println("Door opened");
    }

    if (door == DOOR_OPEN) {
      long volume = map(analogRead(SAMPLE_PIN), 0, 256, 0, 255);
      analogWrite(RED_PIN, volume);
      analogWrite(GREEN_PIN, volume);
      analogWrite(BLUE_PIN, volume);
    }

    if (door == DOOR_OPEN && (millis() - time) > RISING_UP) {
      if (lid == LID_CLOSED) {
        Serial.println("Start raising lid");
        lid = LID_RAISING;
      }
      if (lid == LID_RAISING) {
        if (digitalRead(TOP_PIN) == 0) {
         Serial.println("Raising lid");
         openLid();
        } else {
        Serial.println("Lid raised");
           lid = LID_OPEN;
        }
      }
      if(lid == LID_OPEN && digitalRead(BUSY_PIN)) {
        // Song is over
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 255);
      }
    }
  } else {
    if (door == DOOR_OPEN) {
      door = DOOR_CLOSED;
      myDFPlayer.stop();
      Serial.println("Door closed");
      lid = LID_LOWERING;
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
    }

    if (lid == LID_LOWERING) {
      Serial.println("Lowering lid");
      if (digitalRead(BOTTOM_PIN) == 0) {
        closeLid();

      } else {
        analogWrite(RED_PIN, 0);
        lid = LID_CLOSED;
      }
    }
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read());  //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
