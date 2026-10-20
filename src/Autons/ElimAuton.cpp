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
    // (Insert toggel mechanism code here)
    chassis.moveToPoint(0, m(-55), 1500);

    chassis.turnToHeading(m(180), 1000);

    chassis.moveToPoint(0, m(-70), 1000);

    chassis.moveToPoint(0, m(-60), 1000, {.forwards = false});

    chassis.moveToPoint(0, m(-70), 500);

    chassis.moveToPoint(0, m(-60), 1000, {.forwards = false});
  
}