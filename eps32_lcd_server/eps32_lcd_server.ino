/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <stdlib.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "secrets.h"

const int humidityLed = 17;
const int temperatureLed = 16;

bool humididyLedStatus = LOW;
bool temperatureLedStatus = LOW;

int lcdColumns = 16;
int lcdRows = 2;

#define I2C_SDA 23
#define I2C_SCL 19

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

#define DHTTYPE DHT11

#define DHTPIN 4

DHT_Unified dht(DHTPIN, DHTTYPE);

AsyncWebServer server(80);

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
    <form action="/get">
      temperature target: <input type="text" name="input1">
      <input type="submit" value="Submit">
    </form><br>
    <form action="/get">
      humidity target: <input type="text" name="input2">
      <input type="submit" value="Submit">
    </form><br>
  </body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

int targetTemperature = 25;
int targetHumidity = 50;

uint32_t delayMS;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL, 100000);
  pinMode(humidityLed, OUTPUT);
  pinMode(temperatureLed, OUTPUT);
    // initialize LCD
  lcd.init();
    // turn on LCD backlight                      
  lcd.backlight();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    String inputValue;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputValue = request->getParam(PARAM_INPUT_1)->value();
      targetTemperature = atoi(PARAM_INPUT_1);
    request->send(200, "text/html", "You set your target temperature to" 
                                     + inputValue +
                                     "<br><a href=\"/\">Return to Home Page</a>");
    } else if (request->hasParam(PARAM_INPUT_2)) {
      inputValue = request->getParam(PARAM_INPUT_2)->value();
      targetHumidity = atoi(PARAM_INPUT_2);
      request->send(200, "text/html", "You set your target humidity to" 
                                     + inputValue +
                                     "<br><a href=\"/\">Return to Home Page</a>");
    }
    else {
      targetHumidity = 50;
      targetTemperature = 25;
    }
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(event.temperature);
    lcd.print("C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
  }

  if (targetTemperature < event.temperature) {
    digitalWrite(temperatureLed, HIGH);
  } else {
    digitalWrite(temperatureLed, LOW);
  }

  if (targetHumidity < event.relative_humidity) {
    digitalWrite(humidityLed, HIGH);
  } else {
    digitalWrite(humidityLed, LOW);
  }
}
