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

    // Spin Toggel to Red
    chassis.moveToPoint(0, m(-55), 1500);

    chassis.turnToHeading(m(180), 1000);

    chassis.moveToPoint(0, m(-70), 1000);

    chassis.moveToPoint(0, m(-60), 1000, {.forwards = false});

    chassis.moveToPoint(0, m(-70), 500);

    chassis.moveToPoint(0, m(-60), 1000, {.forwards = false});

    // Move Backwards
    chassis.moveToPoint(0, m(-47.5), 1000, {.forwards = false});

    // Turn to face goal #3
    chassis.turnToHeading(90, 4000);

    // Drive to goal #3
    chassis.moveToPoint(-20, m(-47.5), 1000, {.maxSpeed = 80});

    // Score in goal #3
    setLift(127); // Move lift up to score

    pros::delay(500); // Wait for lift to reach position

    setLift(-127); // Stop lift motors

    pros::delay(500); // Wait for lift to stop moving

    clawSwitch(); // Toggle claw piston to release pin and cup

    // Back up a bit
    chassis.moveToPoint(-12, m(-47.5), 1000, {.forwards = false, .maxSpeed = 80});
}