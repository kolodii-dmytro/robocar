#include <ArduinoJson.h>
#include "WebServerUtils.h"
#include "MotorController.h"
#include "WebPage.h"

WebServerUtils::WebServerUtils(MotorController *motorController) : server(80), motor(motorController)
{
    // Инициализация веб-сервера
}

void WebServerUtils::begin()
{
    std::map<String, MotorAction> motorActions = motor->getActionsMap();
    std::vector<String> actionKeys;
    for (const auto &pair : motorActions)
    {
        actionKeys.push_back(pair.first);
    }

    String HTML = GetHTML(actionKeys);
    server.on("/", HTTP_GET, [this, HTML]()
              { 
            Serial.println("request on '/'");
            server.send(200, "text/html", HTML); });

    server.on("/action", [this, motorActions]()
              {
                  
                  String jsonPayload = (server.hasArg("plain") != false) ? server.arg("plain") : "{}";
                  DynamicJsonDocument jsonDoc(1024);
                  DeserializationError error = deserializeJson(jsonDoc, jsonPayload);
                  if (error)
                  {
                      // Ошибка разбора JSON
                      server.send(400, "text/plain", "Invalid JSON format");
                      return;
                  }
                  String actionName = jsonDoc["action"];
                  int speed = jsonDoc["speed"];

                  if (actionName != "")
                  {
                      MotorAction action = motor->getAction(actionName);
                      motor->executeAction(action, speed);
                      server.send(200, "text/plain", "Executed action: " + actionName);
                  }
                  else
                  {
                      server.send(400, "text/plain", "Invalid action: " + server.arg("plain"));
                  } });
    server.begin();
}

void WebServerUtils::handleClient()
{
    server.handleClient();
}
