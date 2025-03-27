#include <Arduino.h>
#include <unity.h>
#include "sensors/BNO055.h"
#include "sensors/BMP390.h"

void test_BNO055_init() {
    TEST_ASSERT_TRUE(BNO055.begin());
}

void test_BMP280_read() {
    float pressure = BMP280.readPressure();
    TEST_ASSERT_GREATER_THAN(300.0, pressure);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_BNO055_init);
    RUN_TEST(test_BMP280_read);
    UNITY_END();
}

void loop() {}