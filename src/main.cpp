#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "TitanReset/TitanReset.hpp"

pros::Task* liftTask = nullptr;
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
    

    liftInit(); // lift must be fully down when the robot powers on
    //pros::Task liftTask(liftTaskLoop);
	

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
            MIRROR = true; // Set Auton Mirroring to true for Red Left Main
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, -270); // Set DSR system to the correct quadrant and heading for Red Left Main
            mainAuton();
            break;

        case 2: // Red Right Main (source)
            pros::lcd::print(0, "Running Red Right Main");
            MIRROR = false; // Set Auton Mirroring to false for Red Right Main
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270); // Set DSR system to the correct quadrant and heading for Red Right Main
            mainAuton();
            break;

        case 3: // Red Left Elim
            pros::lcd::print(0, "Running Red Left Elim");
            MIRROR = true; // Set Auton Mirroring to true for Red Left Elim
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, -270); // Set DSR system to the correct quadrant and heading for Red Left Elim
            elimAuton();
            break;

        case 4: // Red Right Elim (source)
            pros::lcd::print(0, "Running Red Right Elim");
            MIRROR = false; // Set Auton Mirroring to false for Red Right Elim
            dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270); // Set DSR system to the correct quadrant and heading for Red Right Elim
            elimAuton();
            break;

        case 5: // Red SWP
            pros::lcd::print(0, "Running Red SWP");
            SWP();
            break;

        case 6: // Blue Left Main
            pros::lcd::print(0, "Running Blue Left Main");
            MIRROR = true; // Set Auton Mirroring to true for Blue Left Main
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, -270); // Set DSR system to the correct quadrant and heading for Blue Left Main
            mainAuton();
            break;

        case 7: // Blue Right Main
            pros::lcd::print(0, "Running Blue Right Main");
            MIRROR = true; // Set Auton Mirroring to true for Blue Right Main
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, -270); // Set DSR system to the correct quadrant and heading for Blue Right Main
            mainAuton();
            break;

        case 8: // Blue Left Elim
            pros::lcd::print(0, "Running Blue Left Elim");
            MIRROR = true; // Set Auton Mirroring to true for Blue Left Elim
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, -270); // Set DSR system to the correct quadrant and heading for Blue Left Elim
            elimAuton();
            break;

        case 9: // Blue Right Elim
            pros::lcd::print(0, "Running Blue Right Elim");
            MIRROR = true; // Set Auton Mirroring to true for Blue Right Elim
            dsr_system.perform_dsr_init(tr_quadrant::POS_POS, -270); // Set DSR system to the correct quadrant and heading for Blue Right Elim
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

   // =========================================================
  // DRIVE SPEED
 // B = Regular → Medium → Slow
// =========================================================
  
  // 0 = regular, 1 = medium, 2 = slow — cycles in that order each press
  int speedMode = 0;

  while (true) {

        // Three way speed rotation with the B button. Each press cycles through the three modes.
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            // Move to the next mode, wrapping back to 0 after 2
            speedMode = (speedMode + 1) % 3;

            if (speedMode == 0) {
                drive_speed = DRIVE_SPEED_MAX; // Regular 
                controller.print(0, 0, "Regular Speed");
            } else if (speedMode == 1) {
                drive_speed = DRIVE_SPEED_MAX * 0.85; // Medium Speed
                controller.print(0, 0, "Medium Speed");
            } else {
                drive_speed = DRIVE_SPEED_MAX * 0.80; // Slow Speed
                controller.print(0, 0, "Slow Speed");
            }
        }

        // =========================================================
        // DRIVE
        // =========================================================

        // Retrieve joystick values for tank control.
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // Scale joystick input down if slow mode is on
        float speedRatio = drive_speed / DRIVE_SPEED_MAX;

        leftY = leftY * speedRatio;
        rightY = rightY * speedRatio;

        chassis.tank(leftY, rightY);
    

        // =========================================================
        // INTAKE
        // L1 = Toggle IN
        // L2 = Hold OUT
        // =========================================================

        if (controller.get_digital_new_press(DIGITAL_L1)) {
            intakeActive = !intakeActive;
        }

        if (controller.get_digital(DIGITAL_L2)) {
            setIntake(-127);  // Intake out while L2 is held
        }
        else if (intakeActive) {
            setIntake(127);   // Intake in if toggle is active
        }
        else {
            setIntake(0);     // Intake off
        }


        // ================================
        // LIFT
        // R1 = Lift Manual Up
        // R2 = Lift Manual Down
        // 
        // ================================

        // Lift Manual Control //
        if (controller.get_digital(DIGITAL_R1)) {
            setLift(127); // Lift up while R1 is held
            liftGoingToTarget = false; // Cancel any target movement
        } 
        else if (controller.get_digital(DIGITAL_R2)) {
            setLift(-127); // Lift down while R2 is held
            liftGoingToTarget = false; // Cancel any target movement
        } 
        else if (!liftGoingToTarget) {
            setLift(0); // Stop lift if no buttons are pressed and not moving to a target
        }

        // Lift Target Macro \\ 

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            // Cycle through lift target positions: top, middle, bottom

            liftGoingToTarget = true;
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            clawSwitch(); // Toggle claw piston
        }

         // A button: place sequence
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            place(); // Macro to place pin onto goal
        }

        // Move the lift toward its target
        if (liftGoingToTarget) {
            double error = liftTarget - getArmAngle();
            liftMotors.move(error * kP);
        }

 
    /* Testing without a comp switch only
    if (controller.get_digital(DIGITAL_B) && controller.get_digital(DIGITAL_DOWN)) // Have the auton run if we hit the B and Down button makes it so we don't need to have a comp switch to test autons
    {
      autonomous();
    }
    */

    // =========================================================
    // LOOP DELAY
    // =========================================================

    pros::delay(20);
  }
}