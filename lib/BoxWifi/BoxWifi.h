#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SSD1306Wire.h>

class BoxWifi
{
public:
  /**
   * @brief Construct a new Box Wifi object
   *
   * @param newSSID The SSID of the network
   * @param newPassword The password of the network
   */
  BoxWifi(const char *newSSID, const char *newPassword) : ssid_(newSSID), password_(newPassword){};

  /**
   * @brief Connect to the wifi network
   */
  void connect();

  /**
   * @brief Get the Message string hosted on gist
   */
  void updateMessage();

  /**
   * @brief Check if the message has changed
   *
   * @return True if the most recent message is different from the old one
   */
  bool isMessageNew();

  /**
   * @brief Get the Current Message string
   *
   * @return The current message string
   */
  String getCurrentMessage() const;

  /**
   * @brief Set the Gist URL
   *
   * @param newGistUrl The new Gist URL
   */
  void setGistUrl(const char *newGistUrl)
  {
    gistUrl_ = newGistUrl;
  }

private:
  const char *ssid_;
  const char *password_;
  String oldMessage_;
  String currentMessage_;
  String gistUrl_;
};