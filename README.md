[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# The Maple Seed Drone Prototype
This repository shares the code developed to fly a simple Maple Seed Drone,  which was developed at the UFABC course "Engenharia Unificada" or "Unified Enginnering", taught in  the second trimester of 2019.

The prototype uses two Arduino microcontrollers, the first used as Maple Seed Drone on-board controller, and the second as RC controller.

The main goal of the project was getting the drone lift off the ground. The communication between the boards was achieved using a 433 MHz RF module, as shown below.

<p align="center">
<img src="docs/rf-module.png" width="300"/>
</p>

## The prototype

<p align="center">
<img src="docs/maple-seed-drone.png" width="400"/>
</p>

## Materials

<p align="center">
<img src="docs/drone-materials.png" width="600"/>
</p>

## Brief Code Explanation

Most of the code deals only with communication between the Receiver and Transmitter. The Transmitter board reads and processes analog data from a potentiometer (control stick) and sends it to Receiver board as input signal. The Receiver gets the message from the Transmitter and writes the data as PWM input to the motor. Then, this cycle is repeated in a loop until stopped. 

## Flying results

<p align="center">
<img src="docs/monocopter-flight.gif" width="600"/>
</p>

## Future Work

- Review the motor configuration;
- Integrate with IMU sensors (gyro / mag / accel), as well as a sonar for altitude ranging;
- Add a controllable flap to the wings;
- Design a controller for drone stabilization and maneuverability;

## License

This project is released under the MIT License. Please review the [License file](LICENSE) for more details.
