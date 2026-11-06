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
    chassis.setPose(mp(0, -70, 0));

    // Lift to 85 degrees to activate toggle
    lift(85);

    // Back up while lifting to ensure toggle is set
    chassis.moveToPoint(0, m(-70), 1000, {.maxSpeed = 60});

    // Delay to ensure it's accurate (shorten if low on time)
    pros::delay(800);

    lift(30);

    chassis.moveToPoint(0, m(-65), 1000, {.maxSpeed = 80});

    pros::delay(300);

    chassis.turnToHeading(320, 1000);

    pros::delay(500);

    chassis.moveToPoint(-18, -50, 1000);

    pros::delay(500);

    lift(0);

    pros::delay(500);

    clawSwitch();

    chassis.turnToHeading(270, 1000);

    pros::delay(300);

    chassis.setPose(mp(-18, -50, 270));

    chassis.moveToPoint(-5, -52, 1000, {.forwards = false});

    pros::delay(500);

    chassis.turnToHeading(310, 1000);

    pros::delay(500);

    chassis.moveToPoint(-25, -21, 1000, {.maxSpeed = 60});

    pros::delay(1200);

    dsr_system.perform_dsr();

    clawSwitch();

    pros::delay(200);

    chassis.moveToPoint(-5, -52, 1000, {.forwards = false, .maxSpeed = 60});

    pros::delay(500);

    chassis.turnToHeading(270, 1000);


}

/*
void mainAuton() 
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
    chassis.moveToPoint(20, m(-52), 1000, {.maxSpeed = 90, .minSpeed = 70});

    // Delay for accuracy
    pros::delay(500);

    // Move lift Down to score
    lift(0); 

    chassis.setPose(mp(20, -50, 90));

    // Wait for lift to reach position
    pros::delay(800); 

    // Toggle claw piston to release pin and cup
    clawSwitch(); 

    // Back up again to mid point
    chassis.moveToPoint(8, m(-50), 1000, {.forwards = false, .maxSpeed = 90});

    pros::delay(500);

    // Turn to face the second pin and cup against the wall
    chassis.turnToHeading(mh(140), 1000);

    // Drive to the pin and cup
    chassis.moveToPoint(30, m(-70), 1000, {.maxSpeed = 65});

    // Clamp and pickup the pin and cup

    // Delay (shorten if low on time)
    pros::delay(1000);

    // Toggle claw piston to grab pin and cup
    clawSwitch(); 

    // Move lift up to pick up pin and cup
    lift(60); 

    chassis.turnToHeading(140, 1000);

    chassis.moveToPoint(9.5, m(-47.5), 1000, {.forwards = false, .maxSpeed = 90});

    chassis.turnToHeading(mh(90), 1000);

    chassis.moveToPoint(20, m(-52), 1000, {.maxSpeed = 90, .minSpeed = 70});

    // Delay for accuracy
    pros::delay(500);

    // Move lift Down to score
    lift(0); 

    chassis.setPose(mp(20, -50, 90));

    // Wait for lift to reach position
    pros::delay(800); 

    // Toggle claw piston to release pin and cup
    clawSwitch();



    // Back up again to mid point

    // turn to face alliance goal

    // Drive to alliance goal

    // Place pin onto alliance goal


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
    chassis.turnToHeading(mh(90), 4000);

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
//}*/