#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Arduino.h>
#include <Servo.h>
#include "../sensors/IMU.h"

class ServoController {
private:
    Servo servo1, servo2, servo3, servo4;
    static const int SERVO_MIN = 0;
    static const int SERVO_MAX = 180;
    
    // Helper function to calculate servo angles
    int calculateServoAngle(float primary, float secondary);
    
public:
    ServoController();
    bool begin();
    void setControlSurfaces(float roll, float pitch, float yaw);
};

// Type alias for use in FlightController
using Servos = ServoController;

#endif  