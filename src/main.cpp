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

    // Initialize the LCD and show the splash screen
     pros::lcd::initialize();
     showSplashScreen();

    chassis.calibrate(); // calibrate sensors

	

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
        case 1:
            // Red Left Main
            MIRROR = true;
            dsr_system.perform_dsr_init(tr_quadrant::NEG_POS, 270);
            MainAuton();
            break;
            
        case 2:
            // Red Right Main
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270);
            MainAuton();
            break;
            
        case 3:
            // Red Left Elim
            MIRROR = true;
            dsr_system.perform_dsr_init(tr_quadrant::NEG_POS, 270);
            ElimAuton();
            break;
            
        case 4:
            // Red Right Elim
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270);
            ElimAuton();
            break;
            
        case 5:
            // Red SWP
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270);
            swp();
            break;
            
        case 6:
            // Blue Left Main
            MIRROR = true;
            dsr_system.perform_dsr_init(tr_quadrant::POS_NEG, 270);
            MainAuton();
            break;
            
        case 7:
            // Blue Right Main
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, 270);
            MainAuton();
            break;
            
        case 8:
            // Blue Left Elim
            MIRROR = true;
            dsr_system.perform_dsr_init(tr_quadrant::POS_NEG, 270);
            ElimAuton();
            break;
            
        case 9:
            // Blue Right Elim
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, 270);
            ElimAuton();
            break;
            
        case 10:
            // Blue SWP
            MIRROR = false;
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, 270);
            swp();
            break;

        case 11:
            // SKILLS
            pros::lcd::print(0, "Running SKILLS");
            skillsMain();
            break;
            
        default:
            // No selection
            pros::lcd::print(0, "No auton selected!");
            break;
    }
}