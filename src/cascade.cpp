#include "main.h"


// Number of preset positions
const int numStates = 3;

// Encoder target values for each state (centidegrees)
// State 0: Bottom, State 1: Mid, State 2: Top
// TODO: Replace these with actual encoder values
int states[numStates] = {0, 1080, 2000}; 

int currState = 0; // Tracks index in states[] array
int target = 0;    // Target position for the PID loop
bool isManualControl = false;

/*
 * Handles cycling through states when R1 is pressed:
 * R1: Bottom (0) -> Top (2) -> Mid (1) -> Bottom (0)
 */
void cycleState() {
    if (currState == 0) {
        currState = 2; // Bottom to Top
    } else if (currState == 2) {
        currState = 1; // Top to Middle
    } else if (currState == 1) {
        currState = 0; // Middle to Bottom
    }
    
    target = states[currState];
}

/**
 * Forces the lift state directly back to 0 (Bottom)
 */
void resetToBottom() {
    currState = 0;
    target = states[currState];
}

/**
 * Simple proportional control loop
*/
void cascadeControl() {
    double kp = 0.06;
    double hold = 10; // Power to fight gravity when the lift is raised
 
    double error = target - cascadeRotation.get_position();
    double velocity = kp * error;
    
    // Add hold power if we're aiming above the bottom
    if (target > 0) {
        velocity += hold;
    }
 
    // Keep power within the motor limits
    if (velocity > 127) velocity = 127;
    if (velocity < -127) velocity = -127;
 
    // Send output power to motors
    cascadeMotors.move(velocity);
}

void liftTaskLoop(void* param) {
    while (true) {
        // Run the control loop only when manual override is off
        if (!isManualControl) {
            cascadeControl();
        }
        pros::delay(20);
    }
}

void liftInit() {
    cascadeRotation.reset_position();
    cascadeMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void liftControls() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        cycleState();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        resetToBottom();
    }
}