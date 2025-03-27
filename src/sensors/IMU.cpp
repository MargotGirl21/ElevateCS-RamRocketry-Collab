#include "IMU.h"
#include <math.h>
#include <Wire.h>

BNO085::BNO085() : initialized(false) {
    // Constructor
}

bool BNO085::begin() {
    // Initialize I2C on Teensy 4.1 pins
    Wire.begin();
    Wire.setSDA(18);
    Wire.setSCL(19);
    Wire.setClock(400000); // Set I2C clock to 400kHz
    
    Serial.println(F("Starting BNO085 initialization..."));
    delay(50); // Give the sensor some time to power up
    
    if (!bno.begin_I2C()) {
        Serial.println(F("Failed to initialize BNO085 - check wiring and I2C address"));
        return false;
    }
    
    // Wait for sensor to stabilize
    delay(100);
    
    // Configure the sensor for quaternion and accelerometer output
    if (!bno.enableReport(SH2_GAME_ROTATION_VECTOR, 5000) || !bno.enableReport(SH2_/ACCELEROMETER, 5000)) { // 5000us = 200Hz report rate
        Serial.println(F("Failed to enable game rotation vector"));
        return false;
    }
    
    // Wait for reports to start flowing
    delay(100);
    
    // Try to read initial data to confirm sensor is working
    sh2_SensorValue_t value;
    uint8_t attempts = 0;
    const uint8_t maxAttempts = 10;
    
    while (attempts < maxAttempts) {
        if (bno.getSensorEvent(&value)) {
            initialized = true;
            Serial.println(F("BNO085 initialized successfully"));
            return true;
        }
        delay(10);
        attempts++;
    }
    
    Serial.println(F("Failed to read initial data from BNO085"));
    return false;
}

void BNO085::quatToEuler(const sh2_RotationVector_t& quat, float& roll, float& pitch, float& yaw) {
    double qw = quat.real;
    double qx = quat.i;
    double qy = quat.j;
    double qz = quat.k;

    // Roll (x-axis rotation)
    double sinr_cosp = 2 * (qw * qx + qy * qz);
    double cosr_cosp = 1 - 2 * (qx * qx + qy * qy);
    roll = atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    double sinp = 2 * (qw * qy - qz * qx);
    if (fabs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp);
    else
        pitch = asin(sinp);

    // Yaw (z-axis rotation)
    double siny_cosp = 2 * (qw * qz + qx * qy);
    double cosy_cosp = 1 - 2 * (qy * qy + qz * qz);
    yaw = atan2(siny_cosp, cosy_cosp);
}

bool BNO085::readSensorData(float& roll, float& pitch, float& yaw) {
    if (!initialized) {
        Serial.println(F("IMU not initialized"));
        return false;
    }

    uint8_t attempts = 0;
    const uint8_t maxAttempts = 5;
    bool gotQuat = false, gotAccel = false;
    
    while (attempts < maxAttempts && (!gotQuat || !gotAccel)) {
        if (bno.getSensorEvent(&sensorValue)) {
            if (sensorValue.sensorId == SH2_GAME_ROTATION_VECTOR) {
                // Convert quaternion to Euler angles
                quatToEuler(sensorValue.un.gameRotationVector, roll, pitch, yaw);

                // Convert radians to degrees
                roll = roll * 180.0 / M_PI;
                pitch = pitch * 180.0 / M_PI;
                yaw = yaw * 180.0 / M_PI;
                gotQuat = true;
            }
            else if (sensorValue.sensorId == SH2_ACCELEROMETER) { 
                ax = sensorValue.un.accelerometer.x;
                ay = sensorValue.un.accelerometer.y;
                az = sensorValue.un.accelerometer.z;
                gotAccel = true;
            }
            

        }
        delay(2);
        attempts++;
    }

    if (!gotQuat || !gotAccel) {
        Serial.prinln(F("Failed to read from BNO085"));
        return false;
    }
    return true;
}

   

