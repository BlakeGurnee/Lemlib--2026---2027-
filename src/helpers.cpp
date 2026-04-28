#include "main.h"

// Set Intake function takes in an intake power and sets both the upper and lower intake to that power
void setIntake(int intakePower) 
{
  lowerIntake.move(intakePower);
  upperIntake.move(intakePower);
}

// Block Hold function sets the upper intake to a low power and the lower intake to full power to hold blocks in place
void blockHold()
{
  upperIntake.move(-50);
  lowerIntake.move(127);
}

// Mid Goal function sets the upper intake to 0 and the lower intake to full power to score on the mid goal
void midGoal()
{
  upperIntake.move(-100);
  lowerIntake.move(110);
}

// Low Goal function sets the upper intake to 0 and the lower intake to reverse slowly to score on the low goal
void lowGoal()
{
  upperIntake.move(0);
  lowerIntake.move(-100);
}

// Stop Intake function sets both the upper and lower intake to 0 to stop the intake
void stopIntake() 
{
  lowerIntake.move(0);
  upperIntake.move(0);
}

// Discard Block function takes in an intake power and sets the lower intake to that power and the upper intake to the negative of that power to discard blocks
void discardBlock(int intakePower)
{
  lowerIntake.move(intakePower);
  upperIntake.move(-intakePower);
}

// Descore Switch function toggles the descore piston between the extended and retracted position
void descoreSwitch()
{
 if (descorePiston.is_extended())
  {
    descorePiston.retract();
  }
 else
  {
    descorePiston.extend();
  }
}

// Matchload Switch function toggles the matchload piston between the extended and retracted position
void matchloadSwitch()
{
 if (matchloadPiston.is_extended())
  {
    matchloadPiston.retract();
  }
 else
  {
    matchloadPiston.extend();
  }
}

// Center Goal Switch function toggles the center goal piston between the extended and retracted position
void centerGoalSwitch()
{
 if (centerGoalPiston.is_extended())
  {
    setIntake(0); // Stop the intake to prevent scoring while toggling the center goal piston
    centerGoalPiston.retract();
  }
 else
  {
    midGoal();
    centerGoalPiston.extend();
  }
}

void driveInches(double inches, int speed)
  {
     double wheelDiameter = 2.75; // Diameter of the wheel in inches
     double wheelCircumference = wheelDiameter * M_PI; // Circumference of the wheel
     double degreesPerInch = 360.0 / wheelCircumference; // Degrees the wheel needs to turn to move 1 inch
     double targetDegrees = inches * degreesPerInch; // Total degrees the wheel needs to turn to move the desired distance

     leftMotors.move_relative(targetDegrees, speed);
     rightMotors.move_relative(targetDegrees, speed);
  }