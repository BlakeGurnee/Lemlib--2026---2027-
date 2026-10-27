#include "main.h"

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

// ----- Place sequence ----- //
// This function performs the sequence to place a pin onto a goal
void place() {
    liftGoingToTarget = false;                 // Cancel any target movement
    liftMotors.move_voltage(-8000);           // reverse at 8 volts
    pros::delay(200);                         // wait 0.2 seconds
    clawPiston.set_value(false);              // Deactivate claw piston
    liftMotors.brake();                       // stop lift
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

void lift(int liftPosition) {
    liftGoingToTarget = true;                 // Enable target movement
    liftTarget = liftPosition;                // Set the desired lift position
}

// This function zeros the lift by moving it down until it hits the bottom limit and then resets the sensor position
void zeroLift() {
    liftSensor.reset_position(); // Reset the lift sensor position to zero
    setLift(-127); // Move the lift down at full speed
    pros::delay(300); // Wait for 0.3 seconds to ensure the lift is moving down

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