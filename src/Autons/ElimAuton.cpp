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

    // Lower lift to 30 degrees
    lift(30);

    // Move to central point in between goals
    chassis.moveToPoint(0, m(-54), 1000, {.maxSpeed = 60});

    // Delay to give time to set and for accuracy
    pros::delay(500);

    // Turn to the alliance goal
    chassis.turnToHeading(mh(270), 1000);
    chassis.waitUntilDone();

    // Align to goal #3 with AI Vision and score
    alignAndScore(3);

    // Move backwards and prepare to get pin on the wall
    chassis.moveToPoint(-8, m(-54), 1000, {.forwards = false, .maxSpeed = 50});

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

    // Ensure the robot is facing the correct direction
    chassis.turnToHeading(mh(220), 1000);

    // Move back to mid point in between goals
    chassis.moveToPoint(0, m(-54), 1000, {.forwards = false, .maxSpeed = 80});
    chassis.waitUntilDone();

    // Turn to face neutral goal
    chassis.turnToHeading(mh(90), 1000, {.maxSpeed = 80});

    // Align to goal #2 with AI Vision and score
    alignAndScore(2);

    // Back up again to mid point
    chassis.moveToPoint(10, m(-54), 1000, {.forwards = false, .maxSpeed = 50});

    
    // Turn to face the second pin and cup against the wall
    //chassis.turnToHeading(140, 1000);

    // Drive to the pin and cup
    //chassis.moveToPoint(30, m(-75), 1000, {.maxSpeed = 65});


    // Clamp and pickup the pin and cup


    // Delay (shorten if low on time)
    //pros::delay(1000);


    // Toggle claw piston to grab pin and cup
    //clawSwitch();


    // Move lift up to pick up pin and cup
    //lift(60);
}