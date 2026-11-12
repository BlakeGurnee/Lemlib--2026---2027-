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
    
    #include <cerrno>
#include <cstdio>

// ==========================================
// AI VISION INITIALIZATION
// ==========================================

    printf("\n");
    printf("========================================\n");
    printf("       AI VISION INITIALIZATION         \n");
    printf("========================================\n");

    // --------------------------------------
    // STEP 1: RESET SENSOR
    // --------------------------------------

    printf("\n[AIVISION] Resetting sensor...\n");

    errno = 0;
    int resetResult = aiVision.reset();
    int resetError = errno;

    printf("[AIVISION] Reset result: %d | errno: %d\n",
           resetResult, resetError);

    if (resetResult != PROS_SUCCESS) {
        printf("[ERROR] Failed to reset AI Vision!\n");
    }

    pros::delay(100);

    // --------------------------------------
// STEP 2: DISABLE UNNECESSARY DETECTION
// --------------------------------------

printf("\n[AIVISION] Disabling colors...\n");

errno = 0;
int disableColorsResult = aiVision.disable_detection_types(
    pros::AivisionModeType::colors
);
int disableColorsError = errno;

printf("[AIVISION] Disable colors: %d | errno: %d\n",
       disableColorsResult, disableColorsError);


printf("\n[AIVISION] Disabling objects...\n");

errno = 0;
int disableObjectsResult = aiVision.disable_detection_types(
    pros::AivisionModeType::objects
);
int disableObjectsError = errno;

printf("[AIVISION] Disable objects: %d | errno: %d\n",
       disableObjectsResult, disableObjectsError);

    // --------------------------------------
    // STEP 3: CONFIGURE APRILTAG FAMILY
    // --------------------------------------

    printf("\n[AIVISION] Configuring AprilTag family...\n");

    errno = 0;
    int familyResult = aiVision.set_tag_family(
        pros::AivisionTagFamily::tag_21H7,
        true
    );
    int familyError = errno;

    printf("[AIVISION] Tag family: 21H7\n");
    printf("[AIVISION] Family result: %d | errno: %d\n",
           familyResult, familyError);

    // --------------------------------------
    // STEP 4: ENABLE APRILTAG DETECTION
    // --------------------------------------

    printf("\n[AIVISION] Enabling AprilTag detection...\n");

    errno = 0;
    int enableResult = aiVision.enable_detection_types(
        pros::AivisionModeType::tags
    );
    int enableError = errno;

    printf("[AIVISION] Enable result: %d | errno: %d\n",
           enableResult, enableError);

    // --------------------------------------
    // STEP 5: VERIFY CONFIGURATION
    // --------------------------------------

    printf("\n[AIVISION] Verifying configuration...\n");

    errno = 0;
    int enabledModes = aiVision.get_enabled_detection_types();
    int verifyError = errno;

    printf("[AIVISION] Enabled detection modes: %d\n",
           enabledModes);

    printf("[AIVISION] Verification errno: %d\n",
           verifyError);

    if (enabledModes >= 0) {
        int tagMask = static_cast<int>(
            pros::AivisionModeType::tags
        );

        if (enabledModes & tagMask) {
            printf("[SUCCESS] AprilTag detection is ENABLED.\n");
        } else {
            printf("[ERROR] AprilTag detection is DISABLED!\n");
        }
    } else {
        printf("[ERROR] Could not read detection settings!\n");
    }

    // --------------------------------------
    // STEP 6: CHECK SENSOR RESPONSE
    // --------------------------------------

    printf("\n[AIVISION] Checking sensor response...\n");

    pros::delay(200);

    errno = 0;
    int objectCount = aiVision.get_object_count();
    int countError = errno;

    printf("[AIVISION] Current detected objects: %d\n",
           objectCount);

    printf("[AIVISION] Object count errno: %d\n",
           countError);

    if (objectCount == 0) {
        printf("[INFO] No objects currently detected.\n");
        printf("[INFO] This is normal if no tag is visible.\n");
    }

    if (objectCount < 0) {
        printf("[ERROR] Failed to retrieve object count!\n");
    }

    // --------------------------------------
    // FINISHED
    // --------------------------------------

    printf("\n========================================\n");
    printf("       AI VISION INITIALIZED            \n");
    printf("========================================\n\n");

    

    if (liftTask == nullptr) {
        liftTask = new pros::Task(liftControlTask);
    }


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
        case 1: // Red Right Main
            pros::lcd::print(0, "Running Red Right Main");
            MIRROR = false; // Set Auton Mirroring to false for Red Right Main
            mainAuton();
            break;
 
        case 2: // Red Left Main
            pros::lcd::print(0, "Running Red Left Main");
            MIRROR = true; // Set Auton Mirroring to true for Red Left Main
            mainAuton();
            break;
 
        case 3: // Blue Right Main
            pros::lcd::print(0, "Running Blue Right Main");
            MIRROR = true; // Set Auton Mirroring to true for Blue Right Main
            mainAuton();
            break;
 
        case 4: // Blue Left Main
            pros::lcd::print(0, "Running Blue Left Main");
            MIRROR = true; // Set Auton Mirroring to true for Blue Left Main
            mainAuton();
            break;
 
        case 5: // Red Right Elim (source)
            pros::lcd::print(0, "Running Red Right Elim");
            MIRROR = false; // Set Auton Mirroring to false for Red Right Elim
            elimAuton();
            break;
 
        case 6: // Red Left Elim
            pros::lcd::print(0, "Running Red Left Elim");
            MIRROR = true; // Set Auton Mirroring to true for Red Left Elim
            elimAuton();
            break;
 
        case 7: // Blue Right Elim
            pros::lcd::print(0, "Running Blue Right Elim");
            MIRROR = true; // Set Auton Mirroring to true for Blue Right Elim
            elimAuton();
            break;
 
        case 8: // Blue Left Elim
            pros::lcd::print(0, "Running Blue Left Elim");
            MIRROR = true; // Set Auton Mirroring to true for Blue Left Elim
            elimAuton();
            break;
 
        case 9: // Red SWP
            pros::lcd::print(0, "Running Red SWP");
            SWP();
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
  
  // 0 = regular, 1 = medium — cycles in that order each press
  int speedMode = 0;

  while (true) {

        // Three way speed rotation with the B button. Each press cycles through the three modes.
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            // Move to the next mode, wrapping back to 0 after 1
            speedMode = (speedMode + 1) % 2;

            if (speedMode == 0) {
                drive_speed = DRIVE_SPEED_MAX; // Regular 
                controller.print(0, 0, "Regular Speed");
            } else {
                drive_speed = DRIVE_SPEED_MAX * 0.85; // Medium Speed
                controller.print(0, 0, "Medium Speed");
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

        if (autonButton.get_new_press() && autonSelection != 0) {
            autonomous();   // runs your switch(autonSelection)
        }

        // Lift Target Macro \\ 

        // Y button: cycle through lift presets
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            liftPresetIndex = (liftPresetIndex + 1) % numLiftPresets;
            lift(liftPresets[liftPresetIndex]);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
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