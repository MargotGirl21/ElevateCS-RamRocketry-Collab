#include "FlightController.h"

// Initial Kalman filter parameters - these can be tuned
constexpr float DEFAULT_Q_ANGLE = 0.001f;
constexpr float DEFAULT_Q_BIAS = 0.003f;
constexpr float DEFAULT_R_MEASURE = 0.03f;

// Initial PID parameters - these should be tuned for your specific rocket
constexpr float DEFAULT_PID_P = 1.0f;
constexpr float DEFAULT_PID_I = 0.1f;
constexpr float DEFAULT_PID_D = 0.05f;
constexpr float DEFAULT_PID_MIN = -45.0f;  // Maximum servo deflection in degrees
constexpr float DEFAULT_PID_MAX = 45.0f;   // Maximum servo deflection in degrees

FlightController::FlightController()
    : kalmanRoll(DEFAULT_Q_ANGLE, DEFAULT_Q_BIAS, DEFAULT_R_MEASURE)
    , kalmanPitch(DEFAULT_Q_ANGLE, DEFAULT_Q_BIAS, DEFAULT_R_MEASURE)
    , kalmanYaw(DEFAULT_Q_ANGLE, DEFAULT_Q_BIAS, DEFAULT_R_MEASURE)
    , kalmanAltitude(DEFAULT_Q_ANGLE, DEFAULT_Q_BIAS, DEFAULT_R_MEASURE)
    , pidRoll(DEFAULT_PID_P, DEFAULT_PID_I, DEFAULT_PID_D, DEFAULT_PID_MIN, DEFAULT_PID_MAX)
    , pidPitch(DEFAULT_PID_P, DEFAULT_PID_I, DEFAULT_PID_D, DEFAULT_PID_MIN, DEFAULT_PID_MAX)
    , pidYaw(DEFAULT_PID_P, DEFAULT_PID_I, DEFAULT_PID_D, DEFAULT_PID_MIN, DEFAULT_PID_MAX) {
}

bool FlightController::begin() {
    bool success = true;
    
    Serial.println(F("Starting Flight Controller initialization..."));
    
    // Initialize sensors
    Serial.print(F("Initializing IMU... "));
    if (!imu.begin()) {
        Serial.println(F("FAILED"));
        success = false;
    } else {
        Serial.println(F("OK"));
    }
    
    Serial.print(F("Initializing Altimeter... "));
    if (!altimeter.begin()) {
        Serial.println(F("FAILED"));
        success = false;
    } else {
        Serial.println(F("OK"));
    }
    
    // Initialize actuators
    Serial.print(F("Initializing Servos... "));
    if (!servos.begin()) {
        Serial.println(F("FAILED"));
        success = false;
    } else {
        Serial.println(F("OK"));
    }
    
    Serial.print(F("Initializing Parachute... "));
    if (!parachute.begin()) {
        Serial.println(F("FAILED"));
        success = false;
    } else {
        Serial.println(F("OK"));
    }
    
    // Get initial sensor readings if everything initialized correctly
    if (success) {
        Serial.println(F("Getting initial sensor readings..."));
        
        // Read initial IMU values
        Serial.print(F("Reading IMU... "));
        if (imu.readSensorData(rawRoll, rawPitch, rawYaw)) {
            Serial.print(F("OK (Roll: "));
            Serial.print(rawRoll);
            Serial.print(F(", Pitch: "));
            Serial.print(rawPitch);
            Serial.print(F(", Yaw: "));
            Serial.print(rawYaw);
            Serial.println(F(")"));
            
            // Initialize Kalman filters for IMU
            kalmanRoll.init(rawRoll);
            kalmanPitch.init(rawPitch);
            kalmanYaw.init(rawYaw);
        } else {
            Serial.println(F("FAILED"));
            success = false;
        }
        
        // Read initial altitude
        Serial.print(F("Reading Altimeter... "));
        float temp, pressure, absAlt;
        if (altimeter.readSensorData(temp, pressure, absAlt, rawRelAltitude)) {
            Serial.print(F("OK (Temp: "));
            Serial.print(temp);
            Serial.print(F("°C, Pressure: "));
            Serial.print(pressure);
            Serial.print(F("hPa, Alt: "));
            Serial.print(rawRelAltitude);
            Serial.println(F("m)"));
            
            // Initialize Kalman filter for altitude
            kalmanAltitude.init(rawRelAltitude);
        } else {
            Serial.println(F("FAILED"));
            success = false;
        }
    }
    
    lastUpdateTime = millis();
    
    if (success) {
        Serial.println(F("Flight Controller initialization successful!"));
    } else {
        Serial.println(F("Flight Controller initialization FAILED!"));
    }
    
    return success;
}

void FlightController::update() {
    unsigned long currentTime = millis();
    float deltaTime = (currentTime - lastUpdateTime) / 1000.0f; // Convert to seconds
    lastUpdateTime = currentTime;
    
    // Read raw IMU data including gyro rates
    if (imu.readSensorData(rawRoll, rawPitch, rawYaw, 
                          rawRollRate, rawPitchRate, rawYawRate)) {
        // Apply Kalman filtering to IMU data with gyro rates
        filteredRoll = kalmanRoll.update(rawRoll, rawRollRate, deltaTime);
        filteredPitch = kalmanPitch.update(rawPitch, rawPitchRate, deltaTime);
        filteredYaw = kalmanYaw.update(rawYaw, rawYawRate, deltaTime);
        
        if (debugMode) {
            Serial.print(F("Gyro Rates (deg/s) - Roll: "));
            Serial.print(rawRollRate);
            Serial.print(F(" Pitch: "));
            Serial.print(rawPitchRate);
            Serial.print(F(" Yaw: "));
            Serial.println(rawYawRate);
        }
    }
    
    // Read raw altimeter data
    float temp, pressure, absAlt;
    if (altimeter.readSensorData(temp, pressure, absAlt, rawRelAltitude)) {
        // For altitude, we don't have a rate sensor, so we pass 0 as the rate
        filteredAltitude = kalmanAltitude.update(rawRelAltitude, 0.0f, deltaTime);
    }
    
    // Update PID controllers with filtered values
    float rollOutput = pidRoll.compute(filteredRoll, targetRoll, deltaTime);
    float pitchOutput = pidPitch.compute(filteredPitch, targetPitch, deltaTime);
    float yawOutput = pidYaw.compute(filteredYaw, targetYaw, deltaTime);
    
    // Apply control outputs to servos
    servos.setControlSurfaces(rollOutput, pitchOutput, yawOutput);
    
    // Print debug data if enabled
    if (debugMode) {
        printSensorData();
    }
}

void FlightController::printSensorData() const {
    // Print IMU data
    Serial.println(F("=== IMU Data ==="));
    Serial.print(F("Roll  (deg) - Raw: ")); Serial.print(rawRoll);
    Serial.print(F(" Filtered: ")); Serial.println(filteredRoll);
    Serial.print(F(" Rate: ")); Serial.println(rawRollRate);
    
    Serial.print(F("Pitch (deg) - Raw: ")); Serial.print(rawPitch);
    Serial.print(F(" Filtered: ")); Serial.println(filteredPitch);
    Serial.print(F(" Rate: ")); Serial.println(rawPitchRate);
    
    Serial.print(F("Yaw   (deg) - Raw: ")); Serial.print(rawYaw);
    Serial.print(F(" Filtered: ")); Serial.println(filteredYaw);
    Serial.print(F(" Rate: ")); Serial.println(rawYawRate);
    
    // Print Altimeter data
    Serial.println(F("\n=== Altimeter Data ==="));
    Serial.print(F("Temperature (C): ")); Serial.println(rawTemp);
    Serial.print(F("Pressure (Pa): ")); Serial.println(rawPressure);
    Serial.print(F("Altitude (m) - Raw: ")); Serial.print(rawRelAltitude);
    Serial.print(F(" Filtered: ")); Serial.println(filteredAltitude);
    Serial.println();
}

void FlightController::setTargetOrientation(float roll, float pitch, float yaw) {
    targetRoll = roll;
    targetPitch = pitch;
    targetYaw = yaw;
}

void FlightController::setIMUKalmanParameters(float Q_angle, float Q_bias, float R_measure) {
    kalmanRoll = KalmanFilter(Q_angle, Q_bias, R_measure);
    kalmanPitch = KalmanFilter(Q_angle, Q_bias, R_measure);
    kalmanYaw = KalmanFilter(Q_angle, Q_bias, R_measure);
    
    // Reinitialize with current values
    kalmanRoll.init(rawRoll, 0);
    kalmanPitch.init(rawPitch, 0);
    kalmanYaw.init(rawYaw, 0);
}

void FlightController::setAltitudeKalmanParameters(float Q_angle, float Q_bias, float R_measure) {
    kalmanAltitude = KalmanFilter(Q_angle, Q_bias, R_measure);
    kalmanAltitude.init(rawRelAltitude, 0);
} 