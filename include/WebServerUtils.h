#ifndef WEBSERVER_UTILS_H
#define WEBSERVER_UTILS_H

#include <ESP8266WebServer.h>
#include "MotorController.h" 



class WebServerUtils {
public:
    WebServerUtils(MotorController* motorController);
    void begin();
    void handleClient();
    // Другие методы для настройки и управления веб-сервером

private:
    ESP8266WebServer server;
    MotorController* motor;
};

#endif

//#include <ESP8266HTTPClient.h>