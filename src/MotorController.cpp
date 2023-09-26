#include "MotorController.h"

MotorController::MotorController(int pinL1, int pinL2, int pinR1, int pinR2)
{
    L1 = pinL1;
    L2 = pinL2;
    R1 = pinR1;
    R2 = pinR2;

    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
}

void MotorController::stop()
{
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
}

void MotorController::move(int leftSpeed, int rightSpeed)
{
    Serial.print(
        leftSpeed);
    Serial.print(" : ");
    Serial.print(
        rightSpeed);
    Serial.println(
        "\n");
    int lms1 = (leftSpeed >= 0) ? leftSpeed : 0;
    int lms2 = (leftSpeed >= 0) ? 0 : leftSpeed * (-1);
    int rms1 = (rightSpeed >= 0) ? rightSpeed : 0;
    int rms2 = (rightSpeed >= 0) ? 0 : rightSpeed * (-1);
    analogWrite(L1, lms1);
    analogWrite(L2, lms2);
    analogWrite(R1, rms1);
    analogWrite(R2, rms2);
};

void MotorController::executeAction(MotorAction action, int speed)
{
    switch (action)
    {
    case ACTION_FORWARD:
        move(speed, speed);
        break;
    case ACTION_BACKWARD:
        move(speed * (-1), speed * (-1));
        break;
    case ACTION_STOP:
        stop();
        break;
    case ACTION_LEFT:
        move(speed * (-1), speed);
        break;
    case ACTION_RIGHT:
        move(speed, speed * (-1));
        break;
    case ACTION_FORWARD_LEFT:
        move(speed / 2, speed);
        break;
    case ACTION_FORWARD_RIGHT:
        move(speed, speed / 2);
        break;
    case ACTION_BACKWARD_LEFT:
        move(speed * (-1) / 2, speed * (-1));
        break;
    case ACTION_BACKWARD_RIGHT:
        move(speed * (-1), speed * (-1) / 2);
        break;
    case ACTION_INVALID:
    default:
        stop();
        break;
    }
}

const std::map<String, MotorAction> &MotorController::getActionsMap() const
{
    return actionMap;
}

MotorAction MotorController::getAction(const String &actionStr)
{
    auto it = actionMap.find(actionStr);
    if (it != actionMap.end())
    {
        return it->second;
    }
    else
    {
        return ACTION_INVALID;
    }
}