#pragma once

#include "main.h"
#include "lemlib/api.hpp"
#include "TitanReset/TitanReset.hpp"

// -------- MOTORS -------- //
extern pros::Motor clawMotor;
extern pros::Motor liftMotor;


// -------- PNEUMATICS -------- //
extern pros::adi::Pneumatics matchloadPiston;
extern pros::adi::Pneumatics descorePiston;
extern pros::adi::Pneumatics centerGoalPiston;

// -------- SENSORS --------//
extern pros::AIVision ai_sensor;
extern pros::Rotation claw_sensor;

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