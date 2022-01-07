#include <FastLED.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Distance
#define TRIG_PIN 23
#define ECHO_PIN 22

// Led
#define LED_BACK 16
#define NUM_LEDS 20

// Button
#define BUTTON_GOOD 27
#define BUTTON_MED 26
#define BUTTON_BAD 25

// Variables
float duration_us, distance_cm;
CRGB leds[NUM_LEDS];
const char* ssid = "Love.Peace.Unity.";
const char* password = "";

void setup() {
  Serial.begin (9600);

  // Distance
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Led
  pinMode(LED_BACK, OUTPUT);
  FastLED.addLeds<WS2812, LED_BACK, GRB>(leds, NUM_LEDS);

  // Button
  pinMode(BUTTON_GOOD, INPUT_PULLUP);
  pinMode(BUTTON_MED, INPUT_PULLUP);
  pinMode(BUTTON_BAD, INPUT_PULLUP);

   // WLAN
  delay(4000);
  WiFi.begin(ssid, password);

  // Wait till WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting WLAN");
  }

  Serial.println("Connected WLAN");
}

void sendData(String moodData) {
    // Check if Wifi is still connected
  if (WiFi.status() == WL_CONNECTED) {

    // HTTP Request
    HTTPClient http;
    http.begin("https://0xffd700.com/esppost.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String mood = "mood=" + moodData;
    int httpResponseCode = http.POST(mood);

    // Get POST return
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP code:");
      Serial.println(httpResponseCode);
      Serial.println("Answer:");
      Serial.println(response);
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  } else {
    Serial.println("Disconnected WLAN");
  }
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

    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255, 255, 255);
      FastLED.show();
    }
  } else {
    Serial.print("Background Led aus\n");

    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
  }

  // waits for button to be pressed
  if (digitalRead(BUTTON_GOOD) == LOW) {
    Serial.print("GOOD");
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
    sendData("2");
    delay(10000);
  }
  else if (digitalRead(BUTTON_MED) == LOW) {
    Serial.print("MED");
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255, 128, 0);
      FastLED.show();
    }
    sendData("1");
    delay(10000);
  }
  else if (digitalRead(BUTTON_BAD) == LOW) {
    Serial.print("BAD");
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }
    sendData("0");
    delay(10000);
  }

  delay(500);
}
