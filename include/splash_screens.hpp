#ifndef SPLASH_SCREENS_HPP
#define SPLASH_SCREENS_HPP

#include "main.h"

// Declare your converted images
LV_IMG_DECLARE(caffeine_splash);
LV_IMG_DECLARE(caffeine_match_start);

// Static field-path route pictures, one per auton -- converted the exact
// same way as the two images above (via the LVGL image converter). See
// route_pictures/ and CHANGES.md for how to generate/convert these.
LV_IMG_DECLARE(route_red_left_main);
LV_IMG_DECLARE(route_red_right_main);
LV_IMG_DECLARE(route_red_left_elim);
LV_IMG_DECLARE(route_red_right_elim);
LV_IMG_DECLARE(route_red_swp);
LV_IMG_DECLARE(route_blue_left_main);
LV_IMG_DECLARE(route_blue_right_main);
LV_IMG_DECLARE(route_blue_left_elim);
LV_IMG_DECLARE(route_blue_right_elim);
LV_IMG_DECLARE(route_blue_swp);
LV_IMG_DECLARE(route_skills);

// Coffee cup icon in the middle column -- also a static compiled-in image.
LV_IMG_DECLARE(coffee_cup);

// Team colors - Caffeine (espresso brown, cream, coffee tan, orange)
#define CAFFEINE_ESPRESSO lv_color_make(45, 24, 20)     // dark espresso brown (background)
#define CAFFEINE_CREAM    lv_color_make(240, 234, 224)  // cream (text/borders)
#define CAFFEINE_ORANGE   lv_color_make(232, 163, 61)   // orange accent (selected state)
#define CAFFEINE_TAN      lv_color_make(160, 100, 60)   // coffee-cup tan (skills button)

// Alliance colors (kept distinct from team branding for readability)
#define ALLIANCE_RED  lv_color_make(200, 0, 0)
#define ALLIANCE_BLUE lv_color_make(0, 100, 200)

// Global variables
extern int autonSelection;
extern bool autonConfirmed;

// Function declarations
void showSplashScreen();
void createAutonSelector();
void showMatchStartScreen();

#endif
