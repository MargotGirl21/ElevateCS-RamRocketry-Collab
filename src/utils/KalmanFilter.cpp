/**
 * @file KalmanFilter.cpp
 * @brief Implementation of a Kalman Filter for angle estimation
 * 
 * This Kalman Filter implementation is designed to estimate angles (roll, pitch, yaw) 
 * by fusing accelerometer and gyroscope measurements. It uses a 2-state model
 * (angle and bias) with proper time integration.
 */

#include "KalmanFilter.h"
#include <Arduino.h>

/**
 * @brief Constructs a new Kalman Filter with specified noise parameters
 * 
 * @param Q_angle Process noise variance for the angle
 * @param Q_bias Process noise variance for the bias
 * @param R_measure Measurement noise variance
 */
KalmanFilter::KalmanFilter(float Q_angle, float Q_bias, float R_measure) 
    : Q_angle(Q_angle)
    , Q_bias(Q_bias)
    , R_measure(R_measure)
    , angle(0.0f)
    , bias(0.0f)
    , initialized(false) {
    // Initialize error covariance matrix P to zeros
    P[0][0] = 0.0f;
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 0.0f;
}

/**
 * @brief Initializes the Kalman Filter with starting values
 * 
 * @param angle Initial angle estimate
 * @param bias Initial bias estimate
 */
void KalmanFilter::init(float angle, float bias) {
    this->angle = angle;
    this->bias = bias;
    
    // Initialize with high uncertainty in angle and moderate uncertainty in bias
    P[0][0] = 10.0f;  // Higher initial uncertainty in angle
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 1.0f;  // Moderate initial uncertainty in bias
    
    initialized = true;
}

/**
 * @brief Updates the angle estimate using the Kalman Filter algorithm
 * 
 * This method performs both the prediction and update steps of the Kalman Filter.
 * The prediction step projects the state ahead using the system model,
 * while the update step corrects the prediction using the measurement.
 * 
 * @param measurement The measured angle from the sensor
 * @param gyroRate The measured gyro rate from the sensor
 * @param deltaTime Time elapsed since the last update in seconds
 * @return float The filtered angle estimate
 */
float KalmanFilter::update(float measurement, float gyroRate, float deltaTime) {
    if (!initialized) {
        init(measurement);
        return measurement;
    }

    // Predict step
    // State prediction using gyro rate and bias
    float rate = gyroRate - bias;
    angle += rate * deltaTime;

    // Compute state transition matrix elements
    float F[2][2] = {
        {1.0f, -deltaTime},
        {0.0f, 1.0f}
    };

    // Update error covariance matrix for prediction
    // P = F*P*F' + Q
    float P_temp[2][2];
    
    // First compute F*P
    P_temp[0][0] = P[0][0] + (-deltaTime * P[1][0]);
    P_temp[0][1] = P[0][1] + (-deltaTime * P[1][1]);
    P_temp[1][0] = P[1][0];
    P_temp[1][1] = P[1][1];

    // Then compute (F*P)*F' + Q
    P[0][0] = P_temp[0][0] + (-deltaTime * P_temp[0][1]) + Q_angle;
    P[0][1] = P_temp[0][1];
    P[1][0] = P_temp[1][0];
    P[1][1] = P_temp[1][1] + Q_bias * deltaTime;

    // Update step
    // Innovation and its covariance
    float innovation = measurement - angle;
    float S = P[0][0] + R_measure;

    // Kalman gain
    float K[2];
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    // State update
    angle += K[0] * innovation;
    bias += K[1] * innovation;

    // Covariance update using Joseph form for better numerical stability
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] = (1.0f - K[0]) * P00_temp;
    P[0][1] = (1.0f - K[0]) * P01_temp;
    P[1][0] = -K[1] * P00_temp + P[1][0];
    P[1][1] = -K[1] * P01_temp + P[1][1];

    return angle;
}
