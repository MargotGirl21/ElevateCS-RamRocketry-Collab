#ifndef BMP280_H
#define BMP280_H
#include <Arduino.h>
#include <Adafruit_BMP3XX.h>

class BMP390 {
private:
    Adafruit_BMP3XX sensor;
    float sea_level_pressure;
    float reference_altitude;
    bool reference_set;
    
    // Helper for initialization
    float calculateAverageAltitude(int samples, int delay_ms);

public:
    BMP390();
    
    // Initialize the sensor and optionally set reference altitude
    bool begin(bool set_reference = true);
    
    // Read sensor data (now includes relative altitude)
    bool readSensorData(float &temperature, float &pressure, float &absolute_altitude, float &relative_altitude);
    
    // Manual reference altitude setting
    void setReferenceAltitude(float altitude);
    float getReferenceAltitude() const;
    
    // Existing methods
    void setSeaLevelPressure(float pressure);
    float getSeaLevelPressure() const;
};

// Type alias for use in FlightController
using Altimeter = BMP390;

#endif
