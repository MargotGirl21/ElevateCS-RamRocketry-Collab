#ifndef PARACHUTECONTROLLER_H
#define PARACHUTECONTROLLER_H

#include <Arduino.h>
#include <Adafruit_BMP3xx.h>

class ParachuteController {
private:
    bool deployed;
    int servoPin;

public:
    ParachuteController();
    bool begin();
    void update(float altitude);
    bool isDeployed() const { return deployed; }
};

// Type alias for use in FlightController
using Parachute = ParachuteController;

#endif