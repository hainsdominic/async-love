#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SSD1306Wire.h>
#include <BoxWifi.h>
#include "credentials.h"

#define MINUTE_IN_MS 60000

enum class BoxState
{
  FETCH,
  WAIT,
  READ
};

BoxState currentState = BoxState::FETCH;

const int lightSensorPin = A0;
const int ledPin = D3;
const int closedBoxThreshold = 400;
const int baudRate = 9600;

const char *ssid = mySSID;
const char *password = myPassword;

SSD1306Wire oled(0x3C, D2, D1);
BoxWifi box(ssid, password);

void fadeOn(unsigned int time, int increament)
{
  for (byte value = 0; value < 255; value += increament)
  {
    analogWrite(ledPin, value);
    delay(time / (255 / 5));
  }
}

void fadeOff(unsigned int time, int decreament)
{
  for (byte value = 255; value > 0; value -= decreament)
  {
    analogWrite(ledPin, value);
    delay(time / (255 / 5));
  }
}

void setup()
{
  oled.init();
  oled.flipScreenVertically();
  oled.setColor(WHITE);
  oled.setTextAlignment(TEXT_ALIGN_LEFT);
  oled.setFont(ArialMT_Plain_16);
  oled.clear();
  oled.drawString(15, 30, "WELCOME <3");
  oled.display();

  pinMode(ledPin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  Serial.begin(baudRate);

  box.setGistUrl(myGist);
  box.connect();
}

void loop()
{
  int lightValue;
  switch (currentState)
  {
  case BoxState::FETCH: // fetch the new message
    box.updateMessage();
    if (box.isMessageNew())
    {
      currentState = BoxState::WAIT;
    }
    else
    {
      // If the message is not new, wait for a minute
      delay(MINUTE_IN_MS);
    }
    break;
  case BoxState::WAIT: // wait until the message is read on the display
    lightValue = analogRead(lightSensorPin);

    while (lightValue < closedBoxThreshold)
    {
      fadeOn(1000, 5);
      fadeOff(1000, 5);
      lightValue = analogRead(lightSensorPin);
    }
    analogWrite(ledPin, LOW);
    currentState = BoxState::READ;
    break;
  case BoxState::READ: // display the message
    Serial.println("drawing");
    delay(1000);
    lightValue = analogRead(lightSensorPin);

    oled.clear();
    oled.drawStringMaxWidth(0, 15, 128, box.getCurrentMessage());
    oled.display();

    if (lightValue < closedBoxThreshold)
    {
      oled.clear();
      oled.display();
      currentState = BoxState::FETCH;
    }
    break;
  }

  delay(500);
}