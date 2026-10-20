#include "main.h"
#include "globals.hpp"

// -------- MOTORS --------//
pros::Motor intakeMotor(6, pros::v5::MotorGears::blue); // Motor is a blue motor on port 4 and is reversed
pros::MotorGroup liftMotors({20, -11}, pros::v5::MotorGears::red); // Motor group for the lift, motors are on ports 20 and 11 and one of them is reversed

bool intakeActive = false; // Intake is not active by default
bool liftActive = false; // Lift is not moving to a target by default

// -------- PNEUMATICS --------//
bool clawExtended = false; // Piston is retracted by default
pros::adi::DigitalOut clawPiston('D'); // Piston is on port D

// -------- Lift Variables --------//
bool liftGoingToTarget = false;   // true = lift is moving to a position
double liftTarget = 0;            // where we want the lift (degrees)
double kP = 3;                   // bigger = faster/stronger, too big = shaky

// -------- SENSORS --------//
pros::AIVision ai_sensor(10); // Sensor for detecting AprilTags (Implementaion coming soon!)
pros::Rotation liftSensor(16); // Lift rotation sensor on port 16


// -------- Essential Drivetrain Components --------//

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors \\ 

// Left motor group
pros::MotorGroup leftMotors({-18, -9}); // left motors are on ports 18 and 9, they are both reversed

// right motor group
pros::MotorGroup rightMotors({3, 2});

// IMU
pros::Imu imu(1);

// horizontal tracking wheel encoder
pros::Rotation horizontalEnc(17);

// vertical tracking wheel encoder
pros::Rotation verticalEnc(15);

// horizontal tracking wheel
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, -0.996);

// vertical tracking wheel
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, -0.858);

// drivetrain
lemlib::Drivetrain drivetrain(
    &leftMotors, 
    &rightMotors,
    11.5, // Track Width
    lemlib::Omniwheel::NEW_275, // Wheel Size
    450, // RPM
    2 // Horrizontal Drift
);

// controllers
lemlib::ControllerSettings linearController(10, 0, 3, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angularController(2, 0, 10, 3, 1, 100, 3, 500, 0);

// sensors
lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu); // chassis with odom

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


    // -------- SENSORS --------//

// parallel offset, perpendicular offset, port
tr_sensor north({5.823, -4.694}, 10);
tr_sensor east({5.137, 3.23}, 11);
tr_sensor south({4.861, 5.25}, 12);
tr_sensor west({5.137, 3.744}, 13);

// dsr system
tr_chassis dsr_system(&chassis, {&north, &east, &south, &west});

// tr_chassis dsr_system(&chassis, {&north, &east, &south, &west}, tr_fields::metal); if you want to use the metal field, uncomment this line and comment out the line above it
