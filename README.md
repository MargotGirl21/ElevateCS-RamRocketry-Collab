# 🛰️ Ram Rocketry & ElevateCS: Avionics Guidance System

- Project Manager: Jackson Castleberry 

- Systems and Software Engineering Team Lead: Sabrina Ornelas

- Main Systems and Software Engineering Team: Deon Ornelas, Parker Volesky, Osarumen Okhiku, Ethan Wise, Kyle Smith Hanna

- CSU Facutly Advisor: Fabio De Abreu Santos


This project focuses on developing an onboard guidance system for high-powered rockets as part of the Ram Rocketry team. It is split into two key objectives:

# 🚀 Objective 1: Implementing a Kalman Fusion Filter
🔧 What it is:
A Kalman filter is an advanced algorithm that fuses noisy sensor data to estimate the true state of a system — in this case, the rocket’s orientation and motion.
![maxresdefault](https://github.com/user-attachments/assets/667f783c-323d-4abf-b7ba-3a1035c04ca0)

## 🧠 Why it matters:
Rockets experience a lot of vibration and unpredictable motion. Raw data from sensors like gyroscopes and accelerometers can be noisy or drift over time. The Kalman filter takes all this data and intelligently smooths it out, providing a more accurate and stable estimate of things like pitch, roll, and yaw.

## 📌 Project Status:
RR's current Kalman fusion filter code (in C++) is under review. It has been written by past members but is not yet functional and requires debugging and validation. This is an active area of development and a great place for contributors to learn about:

- Sensor fusion

- Real-time signal processing

- Working with embedded systems and noisy data

# 🎯 Objective 2: Designing a PID Controller
🔧 What it is:
A PID controller (Proportional-Integral-Derivative) is a control loop algorithm that calculates how to adjust a system (like fin angles) to reach a target value (like a stable orientation).

## 🧠 Why it matters:
Once the Kalman filter provides clean orientation data, the PID controller takes over to compute real-time corrections. It helps adjust the rocket’s fins to minimize error, like tilting too far off course.

## 🌐 How it works:

- Proportional: Corrects based on how far the rocket is from the desired angle

- Integral: Corrects based on how long the error has persisted

- Derivative: Predicts future behavior based on current rate of change

## 📌 Project Status:
The PID controller will be developed after the Kalman filter is stable. It will use the filtered orientation data as input, and drive fin actuation via servo motors. This component is essential for autonomous flight stability.

# Using a Model-Based Systems Approach
![Drawing (1)](https://github.com/user-attachments/assets/54074cd6-14a3-4245-a6a3-4441b74a597d)

# Data Flow
![Drawing (2)](https://github.com/user-attachments/assets/6a2e45cb-eb40-4718-8e49-44509a67b445)

# Resources for Contributors
- Teensy Tutorial and Link to Download Arduino: https://www.pjrc.com/teensy/tutorial.html

- Servo Library: https://docs.arduino.cc/libraries/servo/

- Servo Library: https://docs.arduino.cc/language-reference/en/functions/communication/wire/

- Wire Library: https://docs.platformio.org/en/latest/projectconf/index.html

- Flight Software Setup - Landing Model Rockets Ep. 8: https://youtu.be/ha-0-D1vHmY?si=jSYhp7M_27cIr6Y0

# 🎯 Who This Is For
This project is intended for:

- New ElevateCS members
interested in learning how control systems work, contributing to hands-on rocketry software, or getting experience with C++, sensor data, and embedded systems.

- Students curious about systems engineering
who want to see how early debugging, requirements analysis, and testing fit into the larger engineering lifecycle.

- Software or electrical engineering students
  wth an interest in real-time systems, Kalman filters, PID controllers, or flight stabilization.

- Open source contributors
looking to explore a modular and educational rocket control project.

# 🤝 How to Contribute
We’re currently in the debugging and early testing phase, and all help is welcome — from software and hardware work to documentation, research, and testing!

## 🧠 You can help with:

- Debugging and improving the existing Kalman fusion filter code

- Writing test cases and visualizations using real or simulated sensor data

- Documenting system behavior as we refine outputs (e.g., pitch/roll/yaw drift, latency, tuning needs)

- Learning and sharing knowledge about PID control, Teensy boards, or Arduino-based systems

# 🛠️ Getting Started (Coming Soon)
We’ll be publishing:

- A full setup guide for compiling and flashing Teensy microcontrollers

- Sensor data formats and CSV test files

- Code commenting and contribution style guide

# 💬 Interested in Joining?
Open an issue or start a discussion in the repo

Email us at contact.elevatecs@gmail.com or talk to any ElevateCS club officer

# 🧑‍🎓 New to GitHub or C++?
No problem — we’ll walk you through contributing and learning the tools. This project is beginner-friendly and a great intro to systems-based thinking.



