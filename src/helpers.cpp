#include "main.h"

// Lift controller tuning
const double LIFT_KP = 250.0;
const double LIFT_TOLERANCE = 2.0;

// Sets the intake motors to the specified power
void setIntake(int intakePower) {
    intakeMotor.move(intakePower);
}

// Sets the lift motors to the specified power
void setLift(int liftPower) {
    liftMotors.move(liftPower);
}

// Returns the current angle of the lift in degrees
double getArmAngle() {
    return liftSensor.get_position() / 100.0;
}

// Sets a target for the lift controller
void lift(int liftPosition) {
    liftTarget = liftPosition;
    liftGoingToTarget = true;
}

// Waits until the lift reaches its target position
void waitForLift() {
    while (liftGoingToTarget) {
        pros::delay(10);
    }
}

// Lift controller task
void liftControlTask() {
    while (true) {
        if (liftGoingToTarget) {
            double error = liftTarget - getArmAngle();

            if (std::fabs(error) <= LIFT_TOLERANCE) {
                liftMotors.move_voltage(0);
                liftMotors.brake();
                liftGoingToTarget = false;
            } else {
                double output = LIFT_KP * error;

                // Limit output to +/- 12 volts
                if (output > 12000) output = 12000;
                if (output < -12000) output = -12000;

                liftMotors.move_voltage(static_cast<int>(output));
            }
        }

        pros::delay(10);
    }
}

// ----- Place sequence ----- //
// This function performs the sequence to place a pin onto a goal
void place() {
    liftGoingToTarget = false;
    pros::delay(20);

    // Lower the lift slightly
    liftMotors.move_voltage(-8000);
    pros::delay(200);

    // Stop the lift
    liftMotors.brake();

    // Open the claw and synchronize its state
    clawExtended = false;
    clawPiston.set_value(false);                     // stop lift
}

void liftAndPlace() {
    liftGoingToTarget = false;                 // Cancel any target movement
    liftMotors.move_voltage(8000);           // forward at 8 volts
    pros::delay(200);                         // wait 0.2 seconds
    liftMotors.move_voltage(-8000);           // reverse at 8 volts
    pros::delay(200);                         // wait 0.2 seconds
    clawSwitch();                             // Toggle claw piston
    liftMotors.brake();                       // stop lift
}


// This function zeros the lift by moving it down until it hits the bottom limit and then resets the sensor position
void zeroLift() {
    setLift(-127); // Move the lift down at full speed
    pros::delay(300); // Wait for 0.3 seconds to ensure the lift is moving down
    setLift(0); // Stop the lift motors
    // Once the lift has hit the bottom, stop the motors and reset the sensor position
    liftSensor.reset_position();
}

// Initializes the lift by setting the brake mode, resetting the sensor, and zeroing the lift
void liftInit() {
    liftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftSensor.reset_position();
    zeroLift();
}

// This function toggles the state of the claw piston
void clawSwitch() {
    clawExtended = !clawExtended;
    clawPiston.set_value(clawExtended);
}