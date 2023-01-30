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

  String message = client.readString();
  int start = message.indexOf("\"") + 1;
  int end = message.lastIndexOf("\"");
  message = message.substring(start, end);
  Serial.println("The message is: " + message);
  oldMessage_ = currentMessage_;
  currentMessage_ = message;
}

bool BoxWifi::isMessageNew()
{
  return currentMessage_ != oldMessage_;
}

String BoxWifi::getCurrentMessage() const
{
  return currentMessage_;
}