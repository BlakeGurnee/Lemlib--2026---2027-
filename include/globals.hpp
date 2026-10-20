#pragma once

#include "main.h"
#include "lemlib/api.hpp"
#include "TitanReset/TitanReset.hpp"

// -------- MOTORS -------- //
extern pros::Motor intakeMotor;
extern pros::MotorGroup liftMotors;

extern bool intakeActive;
extern bool liftActive;

// -------- PNEUMATICS -------- //
extern bool clawExtended;
extern pros::adi::DigitalOut clawPiston;

// -------- Lift Variables --------//
extern bool liftGoingToTarget;
extern double liftTarget;
extern double kP;

// -------- SENSORS --------//
extern pros::AIVision ai_sensor;
extern pros::Rotation liftSensor;

// -------- Variables -------- //
// The current max drive speed (out of 127), shared between auton and driver control
inline float drive_speed = 127;

// Regular/full speed — 115, not the motor's absolute max of 127
inline const float DRIVE_SPEED_MAX = 127;

// -------- ESSENTIAL DRIVETRAIN COMPONENTS -------- //

// controller
extern pros::Controller controller;

// motors
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// sensors
extern pros::Imu imu;
extern pros::Rotation horizontalEnc;
extern pros::Rotation verticalEnc;

// tracking wheels
extern lemlib::TrackingWheel horizontal;
extern lemlib::TrackingWheel vertical;

// drivetrain + chassis
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::OdomSensors sensors;
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;

// -- TITAN RESET -- //
extern tr_sensor north;
extern tr_sensor east;
extern tr_sensor south;
extern tr_sensor west;
extern tr_chassis dsr_system;