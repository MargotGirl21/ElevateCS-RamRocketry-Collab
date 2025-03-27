# 🛰️ Ram Rocketry & ElevateCS: Avionics Guidance System
This project focuses on developing an onboard guidance system for high-powered rockets as part of the Ram Rocketry team. It is split into two key objectives:

# 🚀 Objective 1: Implementing a Kalman Fusion Filter
🔧 What it is:
A Kalman filter is an advanced algorithm that fuses noisy sensor data to estimate the true state of a system — in this case, the rocket’s orientation and motion.

🧠 Why it matters:
Rockets experience a lot of vibration and unpredictable motion. Raw data from sensors like gyroscopes and accelerometers can be noisy or drift over time. The Kalman filter takes all this data and intelligently smooths it out, providing a more accurate and stable estimate of things like pitch, roll, and yaw.

📌 Project Status:
RR's current Kalman fusion filter code (in C++) is under review. It has been written by past members but is not yet functional and requires debugging and validation. This is an active area of development and a great place for contributors to learn about:

- Sensor fusion

- Real-time signal processing

- Working with embedded systems and noisy data

# 🎯 Objective 2: Designing a PID Controller
🔧 What it is:
A PID controller (Proportional-Integral-Derivative) is a control loop algorithm that calculates how to adjust a system (like fin angles) to reach a target value (like a stable orientation).

🧠 Why it matters:
Once the Kalman filter provides clean orientation data, the PID controller takes over to compute real-time corrections. It helps adjust the rocket’s fins to minimize error, like tilting too far off course.

🌐 How it works:

- Proportional: Corrects based on how far the rocket is from the desired angle

- Integral: Corrects based on how long the error has persisted

- Derivative: Predicts future behavior based on current rate of change

📌 Project Status:
The PID controller will be developed after the Kalman filter is stable. It will use the filtered orientation data as input, and drive fin actuation via servo motors. This component is essential for autonomous flight stability.

 # Who This Is For
- New Members: Learn by contributing to real aerospace systems, understand core control theory and sensor fusion

- Recruiters/Reviewers: See clean, modular code with documented systems engineering principles, control logic, and filtering algorithms

- Collaborators: Clear interface points, open issues, and roadmaps for both debugging and expansion
