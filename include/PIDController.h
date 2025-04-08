#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController {
private:
    float kp;         // Proportional gain
    float ki;         // Integral gain
    float kd;         // Derivative gain
    float minOutput;  // Minimum output value
    float maxOutput;  // Maximum output value
    
    float integral;
    float lastError;
    bool firstRun;

public:
    PIDController(float p = 1.0f, float i = 0.0f, float d = 0.0f, float min = -1.0f, float max = 1.0f)
        : kp(p), ki(i), kd(d), minOutput(min), maxOutput(max), integral(0), lastError(0), firstRun(true) {}
    
    // Compute PID output
    float compute(float currentValue, float setpoint, float deltaTime);
    
    // Parameter setters
    void setTunings(float p, float i, float d);
    void setOutputLimits(float min, float max);
    void reset();
};

#endif 