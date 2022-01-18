#include <FastLED.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

// Distance
#define TRIG_PIN 5
#define ECHO_PIN 4

// Led
#define LED_BACK 23
#define NUM_LEDS 2

// Button
#define BUTTON_GOOD 14
#define BUTTON_MED 12
#define BUTTON_BAD 13

// Variables
float duration_us, distance_cm;
CRGB leds[NUM_LEDS];
const char* ssid = "";
const char* password = "";
const char* sessionId = "75982475702";
const char* fingerprint = "67 62 DA 5C A0 8F 22 6B 8B 6B F3 20 88 B4 F5 5F B5 23 9F 07";


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

  // WiFi
  delay(4000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait till WiFi is connected
  Serial.println("Connecting WLAN");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected WLAN");
}

void sendData(String moodData) {
  // Check if Wifi is still connected
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient https;

    BearSSL::WiFiClientSecure testclient;
    testclient.setInsecure();

    https.begin(testclient, "https://moodstat.0xffd700.com/esppost.php");
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String mood = "mood=" + moodData + "&ids=75982475702";

    int httpResponseCode = https.POST(mood);

    // Get POST return
    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.println("HTTP code:");
      Serial.println(httpResponseCode);
      Serial.println("Answer:");
      Serial.println(response);
    } else {
      Serial.print("Error: ");
      Serial.println(httpResponseCode);
    }

    https.end();

  } else {
    Serial.println("Disconnected WLAN");
  }
}

void loop() {
  // Trigger puls for Distance
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);

  distance_cm = 0.017 * duration_us;

  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // if a person stands close to Moodstat
  if (distance_cm < 25) {

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
  // GOOD
  if (digitalRead(BUTTON_GOOD) == LOW) {
    Serial.print("GOOD");
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
    sendData("2");
    delay(10000);
  }   // MEDIUM
  else if (digitalRead(BUTTON_MED) == LOW) {
    Serial.print("MED");
    for (int i = 0; i < 20; i++) {
      leds[i] = CRGB(255, 128, 0);
      FastLED.show();
    }
    sendData("1");
    delay(10000);
  }   // BAD
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
