#include "main.h"

/* 
---- Auton Mirroring Rules -----
Function Rule Example
moveToPoint plain x, m(y) moveToPoint(-48, m(-24), t)
turnToPointplain x, m(y) turnToPoint(-48, m(-24), t)
turnToHeading 0° or 180° needs m() turnToHeading(m(0), t)
turnToHeading 90° or 270° no m() turnToHeading(90, t)
setPose always mp() setPose(mp(-62, -15, 90))
mechanisms never mirror intake.move(127)
*/

void MainAuton() 
{
    chassis.setPose(mp(-62, -15, 90));
}

