#include <Wire.h> // library for I2C comunication

#include "WiFiUtils.h" // Включаем заголовочный файл с функцией connectToWiFi
#include "WebServerUtils.h"
#include "MotorController.h"

  #define L1 4  // Motor A pins
  #define L2 5
  #define R1 0  // Motor B pins
  #define R2 2


MotorController motor(L1, L2, R1, R2);
WebServerUtils webServer(&motor);


void setup(void)
{
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  delay(1000);
  Serial.begin(115200); 
  delay(10);
  Serial.println('\n');

  connectToWiFi();
  webServer.begin();
 

}


// the loop function runs over and over again forever
void loop()
{
  webServer.handleClient(); // Обработка клиентов веб-сервера
}
