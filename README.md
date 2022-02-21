# Moodstat

**[Live Demo](https://moodstat.0xffd700.com/)**

![grafik](https://user-images.githubusercontent.com/19951276/154872715-f1160b41-0135-481c-8139-8afab35fed81.png)

**In cooperation with [keiningenieur](https://github.com/keiningenieur) ♥** 


Haptic mood tracker that shows your current mood and statistics on a website. To give your friends subtle hints on when to bother you.

### Supplies

   -  [ESP Lolin V3](https://www.amazon.de/-/en/AZDelivery-NodeMCU-Lolin-V3-Parent/dp/B074Q2WM1Y/ref=sr_1_3?crid=2PQJ798VA5XTX&keywords=ESP+Lolin+V3&qid=1645361802&sprefix=esp+lolin+v3%2Caps%2C83&sr=8-3)
   -  [Ultrasonic Distance Sensor](https://www.amazon.de/-/en/Ultrasonic-Distance-Measuring-Mega2560-Duemilanove/dp/B07B66R1ZT/ref=sr_1_3?keywords=ultraschallsensor+arduino&qid=1645361758&sr=8-3)
   - [LED Strip](https://www.amazon.de/dp/B088FJF9XF/ref=cm_sw_r_apan_glt_i_TVXWF8QQZXHZ6PPYTNM0?_encoding=UTF8&psc=1&pldnSite=1)
   -  [Wooden Box](https://www.bauhaus.info/holzkisten/tabletteinsatz-lm/p/24652775)
   -  Anet A8 Heatbed Spring (6mm x  25mm)

### 3D Print

3D Print the thumbs, button brackets, power jack holder and sensor cover.

-  [👍 and 👎](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/ThumpsUp.stl)
-  [🖕](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/Middlefinger.stl)
-  [Button brackets](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/Housing_M.stl)
-  [Power jack mount](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/power_rack_adapter.stl)
-  [Mount](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/Mount.stl)
-  [Sensor cover](https://github.com/0xFFD700/Moodstat/blob/main/3D_Parts/Sensor_Cover.stl)

### Wood box

Cut 3 holes with a diameter of 32 mm into the wooden box and an opening for the distance sensor.

![grafik](https://user-images.githubusercontent.com/19951276/154872738-e952c6d4-649c-4034-8dc1-cecbea4dd874.png)

### Assemble

Screw the button holders into place and insert the springs.

![grafik](https://user-images.githubusercontent.com/19951276/154872743-23586dea-9a5a-4d76-ada4-d4f1040563d9.png)

### Electronic

Assemble the electronic as shown.

![grafik](https://user-images.githubusercontent.com/19951276/154872768-e021e224-59f9-4339-9acd-eaa601053eac.png)

![grafik](https://user-images.githubusercontent.com/19951276/154872776-3d18b02c-a51d-4d2c-a9cf-36915946b7ae.png)

| LED | |
| --- | --- |
| VCC | 5V |
| Din | D3 |
| GND | GND |

| Sensor | |
| --- | --- |
| VCC | 5V |
| Echo | D1 |
| Trig | D0 |
| GND | GND |

Buttons | |
| --- | --- |
| Button 1 | D5 |
| Button 2 | D6 |
| Button 3 | D7 |
| GND | GND |


### Glue

Glue everything in place.

![WhatsApp Image 2022-02-21 at 01 30 35](https://user-images.githubusercontent.com/19951276/154872609-41fc0842-4273-4bfb-8471-c1509efba57d.jpeg)


#### ESP Code

Insert your WiFi name and password, as well as a custom session ID and the fingerprint of your website. Upload the [ESP Code](https://github.com/0xFFD700/Moodstat/blob/main/Moodstat.ino).

```c
#include <FastLED.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

// Distance
#define TRIG_PIN 16
#define ECHO_PIN 5

// Led
#define LED_BACK 0
#define NUM_LEDS 20

// Button
#define BUTTON_GOOD 14
#define BUTTON_MED 13
#define BUTTON_BAD 12

// Variables
float duration_us, distance_cm;
CRGB leds[NUM_LEDS];
const char* ssid = "";
const char* password = "";
const char* fingerprint = "";


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

    String mood = "mood=" + moodData + "&ids=<session id>";

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

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 255, 255);
      FastLED.show();
    }
  } else {
    Serial.print("Background Led aus\n");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
  }

  // waits for button to be pressed
  // GOOD
  if (digitalRead(BUTTON_GOOD) == LOW) {
    Serial.print("GOOD");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 255, 0);
      FastLED.show();
    }
    sendData("2");
    delay(10000);
  }   // MEDIUM
  else if (digitalRead(BUTTON_MED) == LOW) {
    Serial.print("MED");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 128, 0);
      FastLED.show();
    }
    sendData("1");
    delay(10000);
  }   // BAD
  else if (digitalRead(BUTTON_BAD) == LOW) {
    Serial.print("BAD");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 0, 0);
      FastLED.show();
    }
    sendData("0");
    delay(10000);
  }

  delay(500);
}
```


### Webserver

Change the session ID in [esppost.php](https://github.com/0xFFD700/Moodstat/blob/main/Moodget/esppost.php) and upload it and the [Moodweb files](https://github.com/0xFFD700/Moodstat/tree/main/Moodweb) to your web server.

![grafik](https://user-images.githubusercontent.com/19951276/154872859-5f334e4e-315a-4677-8b1c-c5643cf67244.png)


```php
<?php

// Filters out GET requests
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	
    // Mood parameter
    $mood = $_POST["mood"];
    $ids = $_POST["ids"];

    // Validate SessionId
    if ($ids == <session id>) {

        //Get date
        date_default_timezone_set('Europe/Berlin');
        $Date = date("Y-m-d");
        $Time = date("h:i");
        $File = date("Y").".csv";

        //Validate Userinput
        if ($mood === "0" || $mood === "1" || $mood === "2") {

            //Date,Time,Mood
            $stringData = $Date.",".$Time.",".$mood.PHP_EOL;

            //Append to File
            $fp = fopen($File, 'a') or die("can't open file");
            fwrite($fp, $stringData);  
            fclose($fp);  

        } else {

            echo "Wrong Input";
        }
    }
}

?>
```
