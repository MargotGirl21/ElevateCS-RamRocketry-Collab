#ifndef KALMANFILTER_H
#define KALMANFILTER_H

/**
 * @brief A Kalman Filter implementation for fusing accelerometer and gyroscope data
 * 
 * This filter estimates angle and gyro bias using a 2-state model.
 * It fuses accelerometer-derived angles with gyroscope measurements
 * to provide optimal angle estimates.
 */
class KalmanFilter {
public:
    /**
     * @brief Construct a new Kalman Filter
     * 
     * @param Q_angle Process noise variance for angle state
     * @param Q_bias Process noise variance for bias state
     * @param R_measure Measurement noise variance from accelerometer
     */
    KalmanFilter(float Q_angle = 0.001f, float Q_bias = 0.003f, float R_measure = 0.03f);

    /**
     * @brief Initialize the filter with starting values
     * 
     * @param angle Initial angle estimate (from accelerometer)
     * @param bias Initial gyro bias estimate (typically 0)
     */
    void init(float angle, float bias = 0.0f);

    /**
     * @brief Update the angle estimate using new measurements
     * 
     * @param measurement Angle measurement from accelerometer
     * @param gyroRate Angular rate measurement from gyroscope (rad/s)
     * @param deltaTime Time step since last update (seconds)
     * @return float Updated angle estimate
     */
    float update(float measurement, float gyroRate, float deltaTime);

    /**
     * @brief Check if the filter has been initialized
     */
    bool isInitialized() const { return initialized; }

    /**
     * @brief Get the current bias estimate
     */
    float getBias() const { return bias; }

private:
    float Q_angle;    // Process noise variance for the angle state
    float Q_bias;     // Process noise variance for the bias state
    float R_measure;  // Measurement noise variance (from accelerometer)

    float angle;      // Current angle estimate
    float bias;       // Current gyro bias estimate
    float P[2][2];    // Error covariance matrix
    bool initialized; // Initialization status
};

#endif