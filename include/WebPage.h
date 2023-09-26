#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <Arduino.h>
#include "MotorController.h"

String GetStyle()
{
    String style = "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    style += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    style += ".grid-container {\n";
    style += "    display: grid;\n";
    style += "    grid-template-columns: repeat(3, 1fr);\n";
    style += "    grid-gap: 10px;\n";
    style += "    text-align: center;\n";
    style += "}\n";
    style += ".grid-item {\n";
    style += "    width: 100px;\n";
    style += "    height: 100px;\n";
    style += "    background-color: #1abc9c;\n";
    style += "    border-radius: 20%;\n";
    style += "    display: flex;\n";
    style += "    align-items: center;\n";
    style += "    justify-content: center;\n";
    style += "    font-size: 24px;\n";
    style += "    color: white;\n";
    style += "    cursor: pointer;\n";
    style += "}\n";
    style += "</style>\n";
    return style;
}

String GetHeader(String title)
{
    String header = "<!DOCTYPE html> <html>\n";
    header += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    header += "<title>" + title + "</title>\n";
    header += GetStyle();
    header += "</head>\n";
    return header;
}

String functionName = "myFunction";

String GetScript()
{
    String script = "<script>\n";
    script += "var speed = 150;\n";

    script += "function " + functionName + "(action) { \n";
    script += "var data = {action: action,speed: speed};\n";
    script += "console.log(action)\n";
    script += "var ajax = new XMLHttpRequest();";
    script += "ajax.open('POST', '/action', true);\n ajax.setRequestHeader('Content-Type', 'application/json;charset=UTF-8'); \n ajax.send(JSON.stringify(data));\n";
    script += "}\n";
    script += "document.getElementById('speedSlider').addEventListener('input', function () {\n speed = this.value; \n document.getElementById('speedValue').textContent = speed; \n});";
    script += "</script>\n";
    return script;
}

std::map<String, std::tuple<std::string, std::string, std::string>> buttonInfoMap = {
    {"ACTION_FORWARD_LEFT", std::make_tuple(1, 1, "&#9650;")},
    {"ACTION_FORWARD", std::make_tuple(1, 2, "Forward")},
    {"ACTION_FORWARD_RIGHT", std::make_tuple(1, 3, "Forward Right")},
    {"ACTION_LEFT", std::make_tuple(2, 1, "Left")},
    {"ACTION_STOP", std::make_tuple(2, 2, "Stop")},
    {"ACTION_RIGHT", std::make_tuple(2, 3, "Right")},
    {"ACTION_BACKWARD_LEFT", std::make_tuple(3, 1, "Backward Left")},
    {"ACTION_BACKWARD", std::make_tuple(3, 2, "Backward")},
    {"ACTION_BACKWARD_RIGHT", std::make_tuple(3, 3, "Backward Right")},
};

String getOnAction(String actionName, String payload)
{
    return "" + actionName + "='" + functionName + "(\"" + payload + "\")'\n";
}

String GetButton(String text, String actionName)
{
    std::string name = std::get<2>(buttonInfoMap[actionName]);
    std::string column = std::get<0>(buttonInfoMap[actionName]);
    std::string row = std::get<1>(buttonInfoMap[actionName]);
    String button = "<div class='grid-item" + actionName + " ' type='button'\n";
    button += "style='grid-row:"+ row + ";grid-column:"+ column + ";'";
    button += getOnAction("onmousedown", actionName);
    button += getOnAction("ontouchstart", actionName);
    button += getOnAction("onmouseup", "ACTION_STOP");
    button += getOnAction("ontouchend", "ACTION_STOP");
    button += ">" + name + "</div>\n";
    return button;
}




String GetButtonContainer(const std::vector<String> &actionKeys)
{
    String buttonContainer = "<div class='grid-container'> \n";
    for (const auto &action : actionKeys)
    {
        buttonContainer += GetButton(action, action);
    }
    buttonContainer += "</div> \n";
    return buttonContainer;
}

String GetHTML(const std::vector<String> &actionKeys)
{
    String ptr = GetHeader("ESP8266 Web Server");

    ptr += "<body>\n";
    ptr += "<h1>ESP8266 Web Server</h1>\n";
    ptr += "<h3>Using Access Point(AP) Mode</h3>\n";
    ptr += "<span id='speedValue'>150</span>";
    ptr += GetButtonContainer(actionKeys);
    ptr += "<input type='range' id='speedSlider' min='0' max='254' value='150'>\n";

    ptr += GetScript();
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}

#endif