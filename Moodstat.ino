#include <FastLED.h>

// Distance
#define TRIG_PIN 23 
#define ECHO_PIN 22 

// Led
#define LED_BACK 16
#define NUM_LEDS_BACK 20
#define LED_GOOD 17
#define LED_MED 18
#define LED_BAD 19

// Button
#define BUTTON_GOOD 27
#define BUTTON_MED 26
#define BUTTON_BAD 25

// Variables
float duration_us, distance_cm;
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin (9600);

  // Distance
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Led
  pinMode(LED_BACK, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS_BACK);
  pinMode(LED_GOOD, OUTPUT);
  pinMode(LED_MED, OUTPUT);
  pinMode(LED_BAD, OUTPUT);

  //Button
  pinMode(BUTTON_GOOD, INPUT_PULLUP);
  pinMode(BUTTON_MED, INPUT_PULLUP);
  pinMode(BUTTON_BAD, INPUT_PULLUP);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print distance
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // if a person stands befor the Moodstat
  if (distance_cm < 20) {

     Serial.print("Background Led an\n");
    
     for (int i = 0; i<20; i++) {
       leds[i] = CRGB(255, 0, 0);
       FastLED.show();
     }
  } else {
     Serial.print("Background Led aus\n");
    
     for (int i = 0; i<20; i++) {
       leds[i] = CRGB(0, 0, 0);
       FastLED.show();
     }
      
  // waits for button to be pressed
  if (digitalRead(BUTTON_GOOD) == LOW) {
    Serial.print("GOOD");
    digitalWrite(LED_BACK, HIGH);
    delay(1000);
    digitalWrite(LED_BACK, LOW);
    } 
   else if (digitalRead(BUTTON_MED) == LOW) {
      Serial.print("MED");
      digitalWrite(LED_BACK, HIGH);
      delay(1000);
      digitalWrite(LED_BACK, LOW);
      }
   else if (digitalRead(BUTTON_BAD) == LOW) {
      Serial.print("BAD");
      digitalWrite(LED_BACK,HIGH);
      delay(1000);
      digitalWrite(LED_BACK, LOW);
      }
    }

  delay(500);
}
