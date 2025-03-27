#include <Arduino.h>
#include <unity.h>
#include "processing/KalmanFilter.h"

KalmanFilter kalmanRollTest(0.001, 0.003, 0.03);
KalmanFilter kalmanPitchTest(0.001, 0.003, 0.03);
KalmanFilter kalmanYawTest(0.001, 0.003, 0.03);
KalmanFilter kalmanAltitudeTest(0.001, 0.003, 0.03);

void test_initialization() {
    kalmanRollTest.init(0.0, 0.0);
    kalmanPitchTest.init(0.0, 0.0);
    kalmanYawTest.init(0.0, 0.0);
    kalmanAltitudeTest.init(0.0, 0.0);
    
    float rollResult = kalmanRollTest.update(0.0, 1.0);
    float pitchResult = kalmanPitchTest.update(0.0, 1.0);
    float yawResult = kalmanYawTest.update(0.0, 1.0);
    float altitudeResult = kalmanAltitudeTest.update(0.0, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(0.0, rollResult);
    TEST_ASSERT_EQUAL_FLOAT(0.0, pitchResult);
    TEST_ASSERT_EQUAL_FLOAT(0.0, yawResult);
    TEST_ASSERT_EQUAL_FLOAT(0.0, altitudeResult);
}

void test_update() {
    kalmanRollTest.init(0.0, 0.0);
    kalmanPitchTest.init(0.0, 0.0);
    kalmanYawTest.init(0.0, 0.0);
    kalmanAltitudeTest.init(0.0, 0.0);
    
    // Simulate measurements for Roll
    float rollMeasurement1 = 1.0;
    float filteredRoll1 = kalmanRollTest.update(rollMeasurement1, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 1.0, filteredRoll1);
    
    // Simulate measurements for Pitch
    float pitchMeasurement1 = 2.0;
    float filteredPitch1 = kalmanPitchTest.update(pitchMeasurement1, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 2.0, filteredPitch1);
    
    // Simulate measurements for Yaw
    float yawMeasurement1 = 3.0;
    float filteredYaw1 = kalmanYawTest.update(yawMeasurement1, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 3.0, filteredYaw1);
    
    // Simulate measurements for Altitude
    float altitudeMeasurement1 = 100.0;
    float filteredAltitude1 = kalmanAltitudeTest.update(altitudeMeasurement1, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(10.0, 100.0, filteredAltitude1);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_initialization);
    RUN_TEST(test_update);
    UNITY_END();
}

void loop() {}
