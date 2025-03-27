#ifndef FLIGHTCONTROLLER_H
#define FLIGHTCONTROLLER_H

#include <Arduino.h>
#include "sensors/IMU.h"
#include "sensors/Altimeter.h"
#include "actuators/Servos.h"
#include "actuators/Parachute.h"
#include "utils/PIDController.h"
#include "utils/KalmanFilter.h"

class FlightController {
private:
    // Sensors
    IMU imu;
    Altimeter altimeter;
    
    // Actuators
    Servos servos;
    Parachute parachute;
    
    // Control
    PIDController pidRoll;
    PIDController pidPitch;
    PIDController pidYaw;
    
    // Kalman filters for sensor fusion
    KalmanFilter kalmanRoll;
    KalmanFilter kalmanPitch;
    KalmanFilter kalmanYaw;
    KalmanFilter kalmanAltitude;
    
    // State
    float targetRoll = 0;
    float targetPitch = 0;
    float targetYaw = 0;
    
    // Raw sensor values
    float rawRoll = 0, rawPitch = 0, rawYaw = 0;
    float rawRollRate = 0, rawPitchRate = 0, rawYawRate = 0;  // Added gyro rates
    float rawTemp = 0, rawPressure = 0, rawAltitude = 0, rawRelAltitude = 0;
    
    // Filtered values
    float filteredRoll = 0, filteredPitch = 0, filteredYaw = 0;
    float filteredAltitude = 0;
    
    unsigned long lastUpdateTime;
    bool debugMode = false;

public:
    FlightController();
    bool begin();
    void update();
    void setTargetOrientation(float roll, float pitch, float yaw);
    
    // Debug methods
    void enableDebugPrinting(bool enable) { debugMode = enable; }
    void printSensorData() const;
    
    // Kalman filter tuning
    void setIMUKalmanParameters(float Q_angle, float Q_bias, float R_measure);
    void setAltitudeKalmanParameters(float Q_angle, float Q_bias, float R_measure);
};

#endif 