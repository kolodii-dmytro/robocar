#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Arduino.h>
#include <map>

enum MotorAction {
    ACTION_FORWARD,
    ACTION_BACKWARD,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_FORWARD_LEFT,
    ACTION_FORWARD_RIGHT,
    ACTION_BACKWARD_LEFT,
    ACTION_BACKWARD_RIGHT,
    ACTION_STOP,
    ACTION_INVALID
};



class MotorController {
public:
    MotorController(int pinL1, int pinL2, int pinR1, int pinR2);
    void stop();
    void move(int leftSpeed, int rightSpeed);
    void executeAction(MotorAction action, int speed);
    const std::map<String, MotorAction>& getActionsMap() const;
    MotorAction getAction(const String& actionStr);

private:
    int L1;
    int L2;
    int R1;
    int R2;
    std::map<String, MotorAction> actionMap = {
    {"ACTION_FORWARD_LEFT", ACTION_FORWARD_LEFT},
    {"ACTION_FORWARD", ACTION_FORWARD},
    {"ACTION_FORWARD_RIGHT", ACTION_FORWARD_RIGHT},
    {"ACTION_LEFT", ACTION_LEFT},
    {"ACTION_STOP", ACTION_STOP},
    {"ACTION_RIGHT", ACTION_RIGHT},
    {"ACTION_BACKWARD_LEFT", ACTION_BACKWARD_LEFT},
    {"ACTION_BACKWARD", ACTION_BACKWARD},
    {"ACTION_BACKWARD_RIGHT", ACTION_BACKWARD_RIGHT},
};
};


#endif