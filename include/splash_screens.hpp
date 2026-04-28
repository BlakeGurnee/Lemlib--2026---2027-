#ifndef SPLASH_SCREENS_HPP
#define SPLASH_SCREENS_HPP

#include "main.h"

// Declare your converted images
LV_IMG_DECLARE(caffeine_splash);        // New splash screen image
LV_IMG_DECLARE(caffeine_match_start);   // New match start image

// CAFFEINE Color Scheme - Coffee themed
#define ESPRESSO_BLACK lv_color_make(20, 15, 10)      // Dark background
#define COFFEE_BROWN lv_color_make(101, 67, 33)       // Coffee brown
#define CREAM_LATTE lv_color_make(245, 235, 220)      // Cream/beige
#define CARAMEL_GOLD lv_color_make(200, 145, 50)      // Golden accent
#define STEAM_WHITE lv_color_make(255, 255, 255)      // Pure white
#define DARK_ROAST lv_color_make(60, 40, 20)          // Darker brown

// Alliance colors (keep standard for clarity)
#define ALLIANCE_RED lv_color_make(200, 0, 0)
#define ALLIANCE_BLUE lv_color_make(0, 100, 200)

// Global variables
extern int autonSelection;
extern bool autonConfirmed;

// Function declarations
void showSplashScreen();
void createAutonSelector();
void showMatchStartScreen();

#endif