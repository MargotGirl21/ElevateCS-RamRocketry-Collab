#ifndef BNO085_H
#define BNO085_H

#include <Arduino.h>
#include <Adafruit_BNO08x.h>

class BNO085 {
private:
    Adafruit_BNO08x bno;
    sh2_SensorValue_t sensorValue;
    bool initialized;

    void quatToEuler(const sh2_RotationVector_t& quat, float& roll, float& pitch, float& yaw);

public:
    BNO085();
    
    // Initialize the sensor
    bool begin();
    
    // Read the sensor data and convert to roll, pitch, yaw in degrees
    bool readSensorData(float& roll, float& pitch, float& yaw);
};

// Type alias for use in FlightController
using IMU = BNO085;

#endif