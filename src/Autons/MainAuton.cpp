#include "main.h"

/* 
---- Auton Mirroring Rules -----

    setPose always = setPose(mp(x, y, theta))

    move to point or turn to point always wrap Y coordinate in m() moveToPoint(x, m(y), t)

    turn to heading 0 or 180 always wrap in m() turnToHeading(m(0), t), If angle is 90 or 270 → leave it raw: turnToHeading(90, timeout)

    mechanisms never mirror intake.move(127)
*/

void mainAuton() 
{
    // Set Initial Pose
    chassis.setPose(mp(0, -70, 180));

    // Spin Toggel to Red
    // (Insert toggel mechanism code here)

    // Move Backwards
    chassis.moveToPoint(0, m(-54), 1000, {.forwards = false});

    // Turn to face goal #3
    chassis.turnToHeading(90, 4000);

    // Drive to goal #3
    chassis.moveToPoint(-20, m(-54), 1000, {.forwards = false});
    
    // Score in goal #3
    // (Insert scoring mechanism code here)

    // Spin off goal to face the pin and cup

    // Swing off goal
    chassis.swingToHeading(
        90,
        lemlib::DriveSide::RIGHT,
        800,
        {.maxSpeed = 60}
    );


    // Turn to pick up pin and cup aganst the wall
    //chassis.turnToHeading(190, 4000);

    // Drive to pin and cup
    //chassis.moveToPoint(23.5, -67, 1000);

    // Pick up pin and cup
    // (Insert pin and cup pickup mechanism code here)

    // Drive back to goal #3
   // chassis.moveToPoint(-23.5, -51, 1000);

    // Swing around the goal to face the pin
    // (Insert swing code here)

    // Drive to the pin and cup
   // chassis.moveToPoint(-45, -47.5, 1000);
}

