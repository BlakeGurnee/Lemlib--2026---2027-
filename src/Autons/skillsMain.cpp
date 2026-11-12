#include "main.h"

void skillsMain() 
{
  /*
    * The robot is in the -- quadrant
    * The robot is facing 270 degrees
    */
    
    // =========================================
    // INITIALIZATION
    // =========================================

    chassis.setPose(-7, -70, 0);

    // =========================================
    // STEP 1: ACTIVATE TOGGLE
    // =========================================

    // Raise lift to activate toggle
    lift(85);

    // Back up slightly while lifting
    // Starting heading is 0 degrees
    
    // Approach red goal from the south
    chassis.moveToPose(
        -10.5,
        -53,
        270,
        2500,
        {
            .lead = 0.3,
            .maxSpeed = 100
        },
        false
    );

    // Ensure robot faces the goal
    chassis.turnToHeading(
        270,
        700,
        {
            .maxSpeed = 75
        },
        false
    );

    // Final approach
    chassis.moveToPoint(
        -12.5,
        -53,
        1000,
        {
            .maxSpeed = 35,
            .minSpeed = 20
        },
        false
    );

    // Place pin
    lift(0);
    pros::delay(500);
    clawSwitch();



    // =========================================
    // END OF FIRST SECTION
    // =========================================
    


}