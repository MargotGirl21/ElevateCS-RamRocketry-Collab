#include <Arduino.h>
#include "sensors/BNO055.h"
#include "sensors/BMP390.h"

void test_BNO055_initialization() {
    TEST_ASSERT_TRUE(initializeBNO055());
}

void test_BMP280_initialization() {
    TEST_ASSERT_TRUE(initializeBMP280());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_BNO055_initialization);
    RUN_TEST(test_BMP280_initialization);
    UNITY_END();
}

void loop() {}