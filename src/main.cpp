#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "TitanReset/TitanReset.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::delay(500);

    chassis.calibrate(); // calibrate chassis

    // Initialize the LCD and show the splash screen
    pros::lcd::initialize();
    showSplashScreen();
	

	controller.rumble(".");

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
	/*
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
	*/
}

/**
 * Runs while the robot is disabled
 */
void disabled() {
}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
// ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() 
{
	 // Show match start screen
    showMatchStartScreen();
    
    // Run the selected autonomous routine
    switch(autonSelection) {
        case 1: // Red Left Main
            pros::lcd::print(0, "Running Red Left Main");
            MIRROR = true;
            mainAuton();
            break;

        case 2: // Red Right Main (source)
            pros::lcd::print(0, "Running Red Right Main");
            MIRROR = false;
            mainAuton();
            break;

        case 3: // Red Left Elim
            pros::lcd::print(0, "Running Red Left Elim");
            MIRROR = true;
            elimAuton();
            break;

        case 4: // Red Right Elim (source)
            pros::lcd::print(0, "Running Red Right Elim");
            MIRROR = false;
            elimAuton();
            break;

        case 5: // Red SWP
            pros::lcd::print(0, "Running Red SWP");
            SWP();
            break;

        case 6: // Blue Left Main
            pros::lcd::print(0, "Running Blue Left Main");
            MIRROR = true;
            mainAuton();
            break;

        case 7: // Blue Right Main
            pros::lcd::print(0, "Running Blue Right Main");
            MIRROR = true;
            mainAuton();
            break;

        case 8: // Blue Left Elim
            pros::lcd::print(0, "Running Blue Left Elim");
            MIRROR = true;
            elimAuton();
            break;

        case 9: // Blue Right Elim
            pros::lcd::print(0, "Running Blue Right Elim");
            MIRROR = true;
            elimAuton();
            break;

        case 10: // Blue SWP
            pros::lcd::print(0, "Running Blue SWP");
            SWP();
            break;

        case 11: // SKILLS
            pros::lcd::print(0, "Running SKILLS");
            skillsMain();
            break;

        default:
            pros::lcd::print(0, "No auton selected!");
            break;
    }
}

void opcontrol() {
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  
  // Boolean to track whether slow mode is currently on or off
  bool slowModeOn = false;

  while (true) {

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            slowModeOn = !slowModeOn;

            if (slowModeOn) {
                drive_speed = DRIVE_SPEED_MAX * 0.7;
            } else {
                drive_speed = DRIVE_SPEED_MAX;
            }
        }

        // Retrieve joystick values for tank control.
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // Scale joystick input down if slow mode is on
        float speedRatio = drive_speed / DRIVE_SPEED_MAX;
        leftY = leftY * speedRatio;
        rightY = rightY * speedRatio;

        chassis.tank(leftY, rightY);
 
    
    
    /* Testing without a comp switch only
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) // Have the auton run if we hit the B and Down button makes it so we don't need to have a comp switch to test autons
    {
      autonomous();
    }
    */

    pros::delay(20);
  }
}