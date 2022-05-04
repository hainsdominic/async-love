#include "BoxWifi.h"

void BoxWifi::connect()
{
  WiFi.begin(ssid_, password_);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("...");
    delay(500);
  }

  Serial.println("Connected");
}

void BoxWifi::updateMessage()
{
  const int httpsPort = 443;
  const char *host = "lovebox-a935b-default-rtdb.firebaseio.com";

  WiFiClientSecure client;

  client.setInsecure();
  client.setTimeout(5000);

  if (!client.connect(host, httpsPort))
  {
    Serial.println("Connection failed");
    return;
  }

  client.print(String("GET ") + "/boxes/" + boxName_ + "/message.json" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("Request sent");

  // Skips the reading of the headers
  while (client.connected())
  {
    String temp = client.readStringUntil('\n');
    if (temp == "\r")
    {
      break;
    }
  }
  String payload = client.readStringUntil('\n');
  Serial.println("The payload is: " + payload);
  payload.replace("\"", "");
  oldMessage_ = currentMessage_;
  currentMessage_ = payload;
}

bool BoxWifi::isMessageNew()
{
  return currentMessage_ != oldMessage_;
}

String BoxWifi::getCurrentMessage() const
{
  return currentMessage_;
}