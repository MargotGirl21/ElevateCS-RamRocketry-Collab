#include "Servos.h"

ServoController::ServoController() {
    // Constructor implementation
}

bool ServoController::begin() {
    // Attach servos to their respective pins
    // You'll need to define these pins in your configuration
    servo1.attach(2);  // Example pin numbers
    servo2.attach(3);
    servo3.attach(4);
    servo4.attach(5);
    return true;
}

void ServoController::setControlSurfaces(float roll, float pitch, float yaw) {
    // Convert control inputs to servo angles
    int servo1Pos = calculateServoAngle(roll, pitch);
    int servo2Pos = calculateServoAngle(-roll, pitch);
    int servo3Pos = calculateServoAngle(yaw, -pitch);
    int servo4Pos = calculateServoAngle(-yaw, -pitch);

    // Apply to servos with constraints
    servo1.write(constrain(servo1Pos, SERVO_MIN, SERVO_MAX));
    servo2.write(constrain(servo2Pos, SERVO_MIN, SERVO_MAX));
    servo3.write(constrain(servo3Pos, SERVO_MIN, SERVO_MAX));
    servo4.write(constrain(servo4Pos, SERVO_MIN, SERVO_MAX));
}

// Helper function to calculate servo angles
int ServoController::calculateServoAngle(float primary, float secondary) {
    // Convert from control inputs (-1 to 1) to servo angles
    return map(constrain(primary + secondary, -1.0, 1.0) * 1000, 
              -1000, 1000, 
              SERVO_MIN, SERVO_MAX);
} 