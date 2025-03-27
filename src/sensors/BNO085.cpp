#include "sensors/BNO085.h"
#include <math.h>
#include <Logger.h>

void quatToEuler(imu::Quaternion q, float& roll, float& pitch, float& yaw) {
    double qw = q.w();
    double qx = q.x();
    double qy = q.y();
    double qz = q.z();

    double sinr_cosp = 2*(qw*qx+qy*qz);
    double cosr_cosp = 1-2*(qx*qx+qy*qy);
    roll = atan2(sinr_cosp, cosr_cosp);

    double sinp = 2*(qw*qy-qz*qx);
    if (fabs(sinp) >=1)
        pitch = copysign(M_PI /2, sinp); 
    else 
        pitch = asin(sinp);

    double siny_cosp = 2*(qw*qz+qx*qy);
    double cosy_cosp = 1-2*(qy*qy+qz*qz);
    yaw = atan2(siny_cosp, cosy_cosp);
}

void readAccelerometer() {
    imu::Vector<3> accel = bno.getAccel();
    float ax = accel.x();
    float ay = accel.y();
    float az = accel.z();
    float magnitude = sqrt(ax * ax + ay * ay + az * az);

    Logger.info("Accelerometer - X: %f, Y: %f, Z: %f, Magnitude: %f", ax, ay, az, magnitude);
}

void readBNO085() {
    imu::Quaternion quat = bno.getQuat();

    //dummy values
    //imu::Quaternion quat(0.707, 0.0, 0.707, 0.0);

    float roll, pitch, yaw;

    quatToEuler(quat, roll, pitch, yaw);

    roll = roll*180.0/M_PI;
    pitch = pitch*180.0/M_PI;
    yaw = yaw*180.0/M_PI;

    imu::Vector<3> euler = bno.getVector(Adafruit_BNO085::VECTOR_EULER);
    // Process quaternion or Euler angles as needed
    Logger.info("BNO085 Readings - Heading: %f, Roll: %f, Pitch: %f", euler.x(), euler.y(), euler.z());
}

