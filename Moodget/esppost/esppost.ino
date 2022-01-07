#include <WiFi.h>
#include <HTTPClient.h>

// Wifi config
const char* ssid = "Love.Peace.Unity.";
const char* password = "";
const char* sessionId = "75982475702";

void setup() {

  Serial.begin(9600);

  // Doesn´t work without the delay
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
    String mood = "mood=" + moodData + "&id=" + sessionId;
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
  sendData("2");

  delay(10000);
}
