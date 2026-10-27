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
    chassis.setPose(mp(0, -70, 0));

    // Spin Toggel to Red
    // (Insert toggel mechanism code here)

    // Drive forward
    chassis.moveToPoint(0, m(-47.5), 500);

    // Turn to face goal #3
    chassis.turnToHeading(270, 500);

    // Drive to goal #3
    chassis.moveToPoint(-20, m(-47.5), 500);

    // Score in goal #3
    liftAndPlace();

    // Back up a bit
    chassis.moveToPoint(-12, m(-47.5), 500, {.forwards = false});

    // Turn to face the pin and cup against the wall
    chassis.turnToHeading(205, 500);

    // Drive to pin and cup
    chassis.moveToPoint(23, m(-67.5), 500, {.maxSpeed = 80});

    // Pick up pin and cup
    clawPiston.set_value(true); // Activate claw piston to grab pin and cup

    // Move back
    chassis.moveToPoint(-12, m(-47.5), 500, {.forwards = false, .maxSpeed = 80});

    // Turn to face goal #3
    chassis.turnToHeading(270, 500);

    // 

    /*
    // Swing off goal to face the pin and cup at the top
    chassis.swingToHeading(mh(0), mside(lemlib::DriveSide::LEFT), 1000,
                       {.direction = mdir(lemlib::AngularDirection::CW_CLOCKWISE)});

    
    // Drive to pin and cup
    chassis.moveToPoint(-23.5, m(-25), 500, {.maxSpeed = 80});

    // Pick up pin and cup
    clawPiston.set_value(true); // Activate claw piston to grab pin and cup

    // Turn Around to face goal #3
    chassis.turnToHeading(mh(180), 500);

    // Drive back to goal #3
    chassis.moveToPoint(-23.5, m(-43.5), 500);

    // Score in goal #3
    liftAndPlace();

    */

    /*
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
        mh(90),
        mside(lemlib::DriveSide::RIGHT),
        800,
        {.maxSpeed = 60}
    );
    */


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

