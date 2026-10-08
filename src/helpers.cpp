#include "main.h"

void setIntake(int intakePower) {
    intakeMotor.move(intakePower);
}

void setCascade(int cascadePower) {
    cascadeMotors.move(cascadePower);
}



