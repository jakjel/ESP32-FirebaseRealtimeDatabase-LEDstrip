#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Adafruit_NeoPixel.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Insert your network credentials - hot spot
#define WIFI_SSID "<Your Wifi SSID>"
#define WIFI_PASSWORD "<Your password>"

// Insert Firebase project API Key
#define API_KEY "<Your API Key>"

#define USER_EMAIL "<Your Firebase authentication user's email>"
#define USER_PASSWORD "<Your Firebase authentication user's password>"

#define LED_PIN 14     // GPIO 4
#define LED_COUNT 60  // Number of LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long sendDataPrevMillis = 0;
bool value;
bool lastValue = false;
bool signupOK = false;

// Define Firebase objects
FirebaseData Firebase_dataObject;
FirebaseAuth authentication;
FirebaseConfig config;

//Define Firebase Data object
FirebaseData fbdo;

String uid;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = "<Url of your Firebase Realtime Database>";  // Add your database URL here
  authentication.user.email = USER_EMAIL;
  authentication.user.password = USER_PASSWORD;

  Firebase.reconnectWiFi(true);
  Firebase_dataObject.setResponseSize(4096);
  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &authentication);

  Serial.println("Getting User UID");
  while ((authentication.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  uid = authentication.token.uid.c_str();
  if (uid) {
    signupOK = true;
  }
  Serial.print("User UID: ");
  Serial.println(uid);
}

void runLEDAnimation(bool status) {
  // Set all LEDs to white
  if (status) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    strip.show();
  } else {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(10, 10, 10));
    }
    strip.show();
  }
}

void loop() {
  static unsigned long previousFirebaseMillis = 0;
  const int firebaseInterval = 1000;  // Interval for Firebase requests in milliseconds

  // Check if it's time to update the Firebase status
  if (millis() - previousFirebaseMillis >= firebaseInterval) {
    previousFirebaseMillis = millis();

    if (signupOK) {
      if (Firebase.RTDB.getBool(&fbdo, "<Your value>")) {
        value = fbdo.boolData();
        runLEDAnimation(value);
        Serial.println("Value from database: " + String(value));
      } else {
        Serial.println(fbdo.errorReason());
      }
    }
  }
}

