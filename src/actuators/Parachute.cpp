#include "Parachute.h"

// Configuration constants
constexpr int PARACHUTE_SERVO_PIN = 6;  // Example pin number
constexpr float DEPLOY_ALTITUDE_THRESHOLD = 100.0f;  // Deploy at 100m

ParachuteController::ParachuteController() 
    : deployed(false)
    , servoPin(PARACHUTE_SERVO_PIN) {
}

bool ParachuteController::begin() {
    pinMode(servoPin, OUTPUT);
    digitalWrite(servoPin, LOW);  // Ensure parachute is not deployed on startup
    return true;
}

void ParachuteController::update(float altitude) {
    if (altitude > DEPLOY_ALTITUDE_THRESHOLD && !deployed) {
        digitalWrite(servoPin, HIGH);
        deployed = true;
        Serial.print(F("Parachute deployed at altitude: "));
        Serial.print(altitude);
        Serial.println(F(" meters"));
    }
}