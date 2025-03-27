#include "PIDController.h"

float PIDController::compute(float currentValue, float setpoint, float deltaTime) {
    // Calculate error
    float error = setpoint - currentValue;
    
    // Handle first run
    if (firstRun) {
        lastError = error;
        firstRun = false;
    }
    
    // Calculate P term
    float pTerm = kp * error;
    
    // Calculate I term
    integral += error * deltaTime;
    float iTerm = ki * integral;
    
    // Calculate D term
    float derivative = (error - lastError) / deltaTime;
    float dTerm = kd * derivative;
    
    // Save error for next iteration
    lastError = error;
    
    // Calculate total output
    float output = pTerm + iTerm + dTerm;
    
    // Clamp output to limits
    if (output > maxOutput) output = maxOutput;
    if (output < minOutput) output = minOutput;
    
    return output;
}

void PIDController::setTunings(float p, float i, float d) {
    kp = p;
    ki = i;
    kd = d;
}

void PIDController::setOutputLimits(float min, float max) {
    minOutput = min;
    maxOutput = max;
}

void PIDController::reset() {
    integral = 0;
    lastError = 0;
    firstRun = true;
}
