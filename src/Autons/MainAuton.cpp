#include "main.h"

/*
---- Auton Mirroring Rules (Y-flip) -----

    setPose always = setPose(mp(x, y, theta))

    move to point or turn to point always wrap Y coordinate in m()
    moveToPoint(x, m(y), t)

    move to pose wraps Y in m() and heading in mh()
    moveToPose(x, m(y), mh(theta), t)

    turn to heading or swing to heading always wrap EVERY angle in mh(), including 90 and 270
    turnToHeading(mh(0), t)

    explicit turn directions wrap in mdir(), swing sides wrap in mside()
    swingToHeading(mh(0), mside(DriveSide::LEFT), t, {.direction = mdir(AngularDirection::CW_CLOCKWISE)})

    forward/backward moves never mirror

    mechanisms never mirror intake.move(127)

    set MIRROR in every auton case, true or false
*/

void mainAuton() 
{
    // Initialize DSR system           
    dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 0);

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
    chassis.waitUntilDone();

    // Delay to give time to set and for accuracy
    pros::delay(500);

    // Turn to the alliance goal
    chassis.turnToHeading(mh(270), 1000);
    chassis.waitUntilDone();

    // Align to goal #3 with AI Vision and score
    alignAndScore(3);

    // Ensure still facing the goal
    chassis.turnToHeading(mh(270), 1000);
    chassis.waitUntilDone();
   
    // Perform DSR
    dsr_system.perform_dsr();
    //chassis.setPose(mp(0, -54, 270));

    // Move backwards to prepare to get the pin on the line
    chassis.moveToPoint(-10, m(-54), 1000, {.forwards = false});
    chassis.waitUntilDone();

    // Turn to face the pin on the line
    chassis.turnToHeading(mh(310), 1000);
    chassis.waitUntilDone();

    // Move to the pin on the line
    chassis.moveToPoint(-30, m(-27), 1000, {.maxSpeed = 60});
    chassis.waitUntilDone();

    // Toggle claw piston to grab pin and cup
    clawSwitch();

    // Delay
    pros::delay(200);

    // Turn around to face the goal
    chassis.turnToHeading(mh(180), 1000);
    chassis.waitUntilDone();    

    // Move back to the central point in between goals
    chassis.moveToPoint(-5, m(-52), 1000, {.forwards = false, .maxSpeed = 60});

    // While doing that lift
    lift(60);

    // Delay
    pros::delay(500);

    // Turn to face goal #3
    chassis.turnToHeading(mh(270), 1000);

    // Align to goal #3 with AI Vision and score
    alignAndScore(3);

    // Delay
    pros::delay(500);

    // Move lift back up to prepare for next action
   // lift(30);
}