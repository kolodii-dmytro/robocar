#include "WiFiUtils.h"

void connectToWiFi() {
  const char* ssid = "MEO-615ED0";      // The SSID (name) of the Wi-Fi network you want to connect to
  const char* password = "3b58cbbed4";  // The password of the Wi-Fi network

  WiFi.begin(ssid, password);  // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}