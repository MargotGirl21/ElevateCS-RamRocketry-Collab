#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Altimeter.h"

BMP390::BMP390() : sea_level_pressure(101325.0f), reference_altitude(0.0f), reference_set(false) {
    // Constructor initialization
}

float BMP390::calculateAverageAltitude(int samples, int delay_ms) {
    float sum = 0;
    for (int i = 0; i < samples; i++) {
        if (!sensor.performReading()) {
            Serial.println(F("Failed to read BMP390"));
            continue;
        }
        sum += sensor.readAltitude(sea_level_pressure);
        delay(delay_ms);
    }
    return sum / samples;
}

bool BMP390::begin(bool set_reference) {
    // Initialize I2C on Teensy 4.1 pins
    Wire.begin();
    Wire.setSDA(18);
    Wire.setSCL(19);
    
    if (!sensor.begin_I2C()) {
        Serial.println(F("Could not find a valid BMP3XX sensor"));
        return false;
    }

    // Configure the sensor
    sensor.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    sensor.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    sensor.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    sensor.setOutputDataRate(BMP3_ODR_50_HZ);

    if (set_reference) {
        reference_altitude = calculateAverageAltitude(10, 100);
        reference_set = true;
        Serial.print(F("Reference altitude set to: "));
        Serial.print(reference_altitude);
        Serial.println(F(" meters"));
    }

    Serial.println(F("BMP390 initialized successfully"));
    return true;
}

bool BMP390::readSensorData(float &temperature, float &pressure, float &absolute_altitude, float &relative_altitude) {
    if (!sensor.performReading()) {
        Serial.println(F("Failed to read BMP390"));
        return false;
    }

    temperature = sensor.temperature;
    pressure = sensor.pressure / 100.0; // Convert to hPa
    absolute_altitude = sensor.readAltitude(sea_level_pressure);
    relative_altitude = absolute_altitude - reference_altitude;

    // Debug output
    Serial.print(F("BMP390 Readings - Temperature: "));
    Serial.print(temperature);
    Serial.print(F("°C, Pressure: "));
    Serial.print(pressure);
    Serial.print(F(" hPa, Absolute Altitude: "));
    Serial.print(absolute_altitude);
    Serial.print(F(" m, Relative Altitude: "));
    Serial.print(relative_altitude);
    Serial.println(F(" m"));

    return true;
}

void BMP390::setReferenceAltitude(float altitude) {
    reference_altitude = altitude;
    reference_set = true;
}

float BMP390::getReferenceAltitude() const {
    return reference_altitude;
}

void BMP390::setSeaLevelPressure(float pressure) {
    sea_level_pressure = pressure;
}

float BMP390::getSeaLevelPressure() const {
    return sea_level_pressure;
}

