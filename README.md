# Vehicle Safety and Passenger Comfort System with AI-Enhanced ADAS

This repository contains the code and documentation for the Vehicle Safety and Passenger Comfort System with AI-Enhanced Advanced Driver Assistance Systems (ADAS) project. This project aims to enhance vehicle safety and passenger comfort using AI technologies and ADAS features implemented on a small car prototype.

## Table of Contents

  - [Introduction](#introduction)
  - [Features](#features)
  - [Hardware Components](#hardware-components)
  - [Software Architecture](#software-architecture)
  - [Installation](#installation)
  - [Project Structure](#project-structure)

## Introduction

The Vehicle Safety and Passenger Comfort System integrates multiple ADAS features to improve driving safety and enhance passenger comfort. This project utilizes AI for lane detection and driver monitoring, providing functionalities such as Adaptive Cruise Control (ACC), Automatic Emergency Braking (AEB), Lane Keeping Assistance (LKA), and a Driver Monitoring System (DMS).

## Features

- **Adaptive Cruise Control (ACC)**: Automatically adjusts the vehicle's speed to maintain a safe distance from the vehicle ahead.
- **Automatic Emergency Braking (AEB)**: Detects obstacles and applies the brakes to prevent collisions.
- **Lane Keeping Assistance (LKA)**: Detects lane markings and helps keep the vehicle in its lane.
- **Driver Monitoring System (DMS)**: Monitors the driver's eyes to detect drowsiness or distraction using eye aspect ratio (EAR) detection.

## Hardware Components

- **STM32F103C8T6 MCU**: Responsible for implementing AEB and ACC features.
- **ESP32 CAM Development Board**: Captures road images and forwards them to the lane detection algorithm.
- **Ultrasonic Sensors**: Used for distance measurement in ACC and AEB.
- **Servo Motors**: Used for steering control in LKA.

## Software Architecture

The project uses a layered software architecture on the STM32 board, manually implementing all drivers from scratch. FreeRTOS is used for scheduling tasks with a fixed priority scheduler. The ESP32 CAM development board streams live video and communicates with the STM32 board using the UART protocol.

## Installation

To set up the project, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/ahmed-elshamy23/Vehicle-Safety-and-Passenger-Comfort-System-With-AI-Enhanced-ADAS.git
    ```
2. Load the STM32CubeIde project located in "STM32 IDE Project (new C8)" directory into the IDE, build it and burn it on the STM32F103C8T6 board.
3. Load the ESP32-CAM code located in "ESP32 Final Code" directory and burn it on the ESP32-CAM board with your Wi-Fi and MQTT credentials.

## Project Structure

```plaintext
Vehicle-Safety-and-Passenger-Comfort-System-With-AI-Enhanced-ADAS/
│
├── Main ECU Application/             # Source code for STM32 board
├── ESP32 Final Code/                 # Source code for ESP32-CAM board
├── STM32 IDE Project (new C8)/       # STM32CubeIde project (for plug and play)
├── AI Models/                        # Python code for face recognition, LKA and DMS
├── System Tasks.xml                  # SimSo-generated file for real-time system tasks
└── README.md                         # Project README file
