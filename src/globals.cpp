#include "main.h"
#include "globals.hpp"

// -------- MOTORS --------//
pros::Motor lowerIntake(-4, pros::v5::MotorGears::blue); // Motor is a blue motor on port 4 and is reversed
pros::Motor upperIntake(-5, pros::v5::MotorGears::blue); // Motor is a blue motor on port 5 and is reversed

// -------- PNEUMATICS --------//
pros::adi::Pneumatics descorePiston('A', false); // Starts descore in the false (Down) position when the code starts in port A
pros::adi::Pneumatics matchloadPiston('B', false); // Starts matchload in the false (Up) position when the code starts in port B
pros::adi::Pneumatics centerGoalPiston('C', false); // Starts center goal in the false (Down) position when the code starts in port C

// -------- SENSORS --------//
pros::AIVision ai_sensor(2);


// -------- Essential Drivetrain Components --------//

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
pros::MotorGroup leftMotors({-5, 4}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({6, -9}, pros::MotorGearset::blue);

// IMU
pros::Imu imu(10);

// tracking wheels
pros::Rotation horizontalEnc(20);
pros::Rotation verticalEnc(-11);

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    10,
    lemlib::Omniwheel::NEW_4,
    450,
    2
);

// controllers
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angularController(2, 0, 10, 3, 1, 100, 3, 500, 0);

// sensors
lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);

// curves
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);

// chassis
lemlib::Chassis chassis(
    drivetrain,
    linearController,
    angularController,
    sensors,
    &throttleCurve,
    &steerCurve
);

// -------- TitanReset Components --------- //

// sensors
tr_sensor north({5.823, -4.694}, 10);
tr_sensor east({5.137, 3.23}, 11);
tr_sensor south({4.861, 5.25}, 12);
tr_sensor west({5.137, 3.744}, 13);

// dsr system
tr_chassis dsr_system(&chassis, {&north, &east, &south, &west});