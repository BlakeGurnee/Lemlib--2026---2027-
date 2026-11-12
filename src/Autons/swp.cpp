#include "main.h"

void SWP() 
{
   /*
    * The robot is in the -- quadrant
    * The robot is facing 270 degrees
    */
    
    chassis.setPose(mp(0, -70, 0));

    lift(85);

    pros::delay(1000);

    chassis.moveToPoint(0, m(-54), 1500, {.maxSpeed = 60});
    chassis.waitUntilDone();

    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
}