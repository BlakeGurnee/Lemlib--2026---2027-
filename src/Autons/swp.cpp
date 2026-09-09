#include "main.h"

void SWP() 
{
   /*
    * The robot is in the -- quadrant
    * The robot is facing 270 degrees
    */
    dsr_system.perform_dsr_init(tr_quadrant::NEG_NEG, 270);
}