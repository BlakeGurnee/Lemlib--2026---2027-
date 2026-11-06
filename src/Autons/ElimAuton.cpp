#include "main.h"

/* 
---- Auton Mirroring Rules -----

    setPose always = setPose(mp(x, y, theta))

    move to point or turn to point always wrap Y coordinate in m() moveToPoint(x, m(y), t)

    turn to heading 0 or 180 always wrap in m() turnToHeading(m(0), t), If angle is 90 or 270 → leave it raw: turnToHeading(90, timeout)

    mechanisms never mirror intake.move(127)
*/


void elimAuton() 
{

    // Set Initial Pose
    chassis.setPose(mp(0, -70, 0));

    // Lift to 85 degrees to activate toggle
    lift(85);

    // Back up while lifting to ensure toggle is set
    chassis.moveToPoint(0, m(-70), 1000, {.maxSpeed = 60});

    // Delay to ensure it's accurate (shorten if low on time)
    pros::delay(1000);

    lift(30);

    // Move to central point in between goals
    chassis.moveToPoint(0, m(-52), 1000, {.maxSpeed = 75});

    // Delay to give time to set and for accuracy
    pros::delay(500);

    // Turn to the alliance goal
    chassis.turnToHeading(mh(270), 1000);

    // Wait till turn finishes
    pros::delay(500);

    // Drive to goal #3
    chassis.moveToPoint(-20, m(-50), 1000, {.maxSpeed = 85});

    // Delay
    pros::delay(450);

    // Move lift Down to score
    lift(0); 

    // Wait for lift to reach position
    pros::delay(500); 

    // Toggle claw piston to release pin and cup
    clawSwitch(); 

    // Move backwards and prepare to get pin on the wall
    chassis.moveToPoint(-8, m(-50), 1000, {.forwards = false, .maxSpeed = 70});

    chassis.turnToHeading((320), 1000);

    chassis.moveToPose(-50, m(24), (340), 1000, {.maxSpeed = 55});

    pros::delay(800);

    clawSwitch();
    // Set Initial Pose
    chassis.setPose(mp(0, -70, 0));

    // Lift to 85 degrees to activate toggle
    lift(85);

    // Back up while lifting to ensure toggle is set
    chassis.moveToPoint(0, m(-70), 1000, {.maxSpeed = 60});

    // Delay to ensure it's accurate (shorten if low on time)
    pros::delay(1000);

    // Move to central point in between goals
    chassis.moveToPoint(0, m(-52), 1000, {.maxSpeed = 60});

    // Delay to give time to set and for accuracy
    pros::delay(500);

    // Turn to the alliance goal
    chassis.turnToHeading(mh(270), 1000);

    // Wait till turn finishes
    pros::delay(500);

    // Drive to goal #3
    chassis.moveToPoint(-20, m(-50), 1000, {.maxSpeed = 70});

    // Delay
    pros::delay(500);

    // Move lift Down to score
    lift(0); 

    // Wait for lift to reach position
    pros::delay(800); 

    // Toggle claw piston to release pin and cup
    clawSwitch(); 

    // Move backwards and prepare to get pin on the wall
    chassis.moveToPoint(-10, m(-50), 1000, {.forwards = false, .maxSpeed = 50});

    // Turn to face the pin on the wall
    chassis.turnToHeading(mh(220), 1000);

    // Small delay
    pros::delay(500);

    // Move to the pin on the wall
    chassis.moveToPoint(-30, m(-75), 1000, {.maxSpeed = 65});

    // Delay (shorten if low on time)
    pros::delay(1000);

    // Toggle claw piston to grab pin and cup
    clawSwitch(); 

    // Move lift up to pick up pin and cup
    lift(60); 

    chassis.turnToHeading(220, 1000);

    // Move back to mid point in between goals
    chassis.moveToPoint(0, m(-50), 1000, {.forwards = false, .maxSpeed = 80});

    // Turn to face alliance goal
    chassis.turnToHeading(mh(90), 1000, {.maxSpeed = 80});

    // Move to the alliance goal
    chassis.moveToPoint(20, m(-52), 1000, {.maxSpeed = 90});

    // Delay for accuracy
    pros::delay(500);

    // Move lift Down to score
    lift(0); 

    //chassis.setPose(mp(20, -52, 90));

    // Wait for lift to reach position
    pros::delay(800); 

    // Toggle claw piston to release pin and cup
    clawSwitch(); 

    // Back up again to mid point
    chassis.moveToPoint(10, m(-50), 1000, {.forwards = false, .maxSpeed = 80});
}