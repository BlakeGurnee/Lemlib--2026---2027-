#include "main.h"

void rotateClaw(int amount) 
{
  int target = amount;
  double kp = 0.5;
  double error = target - claw_sensor.get_position();
  double velocity = kp * error;
  clawMotor.move(velocity);
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