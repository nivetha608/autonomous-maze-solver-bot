# Autonomous Maze Solver Bot

## Overview

This project presents the design and implementation of an autonomous maze solving robot capable of navigating unknown environments without human intervention. The system integrates ultrasonic sensing, embedded control, and real time decision-making to achieve efficient path traversal.

The robot operates using a left-hand wall-following algorithm, allowing it to explore and solve simply connected mazes while avoiding obstacles dynamically.

---

## Hardware Components

* Arduino Uno / Nano
* L298N Motor Driver Module
* HC-SR04 Ultrasonic Sensors (x3)
* DC Motors with wheels
* Li-ion Battery Pack
* Chassis and wiring setup

---

## Working Principle

The robot continuously senses distances in three directions and classifies paths as open or blocked. Based on this, it makes movement decisions:

* Turn left if the left path is open
* Move forward if the front path is clear
* Turn right if only the right path is available
* Move backward if all directions are blocked

This ensures continuous navigation until the maze exit is reached.

---

## Navigation Algorithm

### Left-Hand Wall Following

The algorithm maintains contact with the left wall to guarantee reaching the exit in simply connected mazes.

#### Logical Flow:

1. Read sensor values (left, front, right)
2. If left is open → turn left
3. Else if front is open → move forward
4. Else if right is open → turn right
5. Else → move backward
6. Repeat continuously

---

## Observations

* Ultrasonic sensors provided reliable measurements with minor environmental sensitivity
* Turning accuracy slightly affected by wheel slippage
* System maintained stable operation under continuous feedback

---

## Limitations

* Works best in simply connected mazes
* No memory or mapping capability
* Performance affected by surface friction and sensor noise

---

## Future Improvements

* PID-based motor control for precise navigation
* Encoder integration for distance tracking
* Flood-fill algorithm for shortest path optimization
* SLAM-based mapping for complex environments
* Camera-based vision system for advanced navigation

---


## Author

Developed by Nivetha N
