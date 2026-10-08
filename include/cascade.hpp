#include "main.h"

extern void cycleState();
extern void resetToBottom();
extern void cascadeControl();
extern void liftInit();
extern void liftControls();
extern void liftTaskLoop(void* param);
extern bool isManualControl;
extern pros::Task* liftTask;

