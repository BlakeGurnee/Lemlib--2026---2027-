#include "splash_screens.hpp"

// Global variables
int autonSelection = 0;
bool autonConfirmed = false;

// Store button objects globally so we can update them
static lv_obj_t* autonButtons[10];
static lv_obj_t* statusLabel;
static lv_obj_t* skillsBtn;

// Button click event handlers
static void continueClicked(lv_event_t* e) {
    createAutonSelector();
}

static void autonButtonClicked(lv_event_t* e) {
    // Get which button was clicked
    lv_obj_t* btn = lv_event_get_target(e);
    
    // Find which button it was
    for (int i = 0; i < 10; i++) {
        if (autonButtons[i] == btn) {
            autonSelection = i + 1;
            autonConfirmed = true;
            
            // Reset skills button to unselected
            lv_obj_set_style_bg_color(skillsBtn, COFFEE_BROWN, 0);
            lv_obj_set_style_border_color(skillsBtn, CARAMEL_GOLD, 0);
            lv_obj_set_style_border_width(skillsBtn, 3, 0);
            lv_obj_set_style_text_color(skillsBtn, STEAM_WHITE, 0);
            
            // Update button styles
            for (int j = 0; j < 10; j++) {
                if (j == i) {
                    // Selected style (caramel gold)
                    lv_obj_set_style_bg_color(autonButtons[j], CARAMEL_GOLD, 0);
                    lv_obj_set_style_border_color(autonButtons[j], STEAM_WHITE, 0);
                    lv_obj_set_style_border_width(autonButtons[j], 3, 0);
                    lv_obj_set_style_text_color(autonButtons[j], ESPRESSO_BLACK, 0);
                } else {
                    // Unselected style - red or blue based on alliance
                    if (j < 5) {
                        // Red alliance buttons
                        lv_obj_set_style_bg_color(autonButtons[j], lv_color_make(80, 20, 20), 0);
                        lv_obj_set_style_border_color(autonButtons[j], ALLIANCE_RED, 0);
                    } else {
                        // Blue alliance buttons
                        lv_obj_set_style_bg_color(autonButtons[j], lv_color_make(20, 30, 80), 0);
                        lv_obj_set_style_border_color(autonButtons[j], ALLIANCE_BLUE, 0);
                    }
                    lv_obj_set_style_border_width(autonButtons[j], 2, 0);
                    lv_obj_set_style_text_color(autonButtons[j], STEAM_WHITE, 0);
                }
            }
            
            // Update status text
            const char* statusTexts[] = {
                "Red Left Main", 
                "Red Right Main", 
                "Red Left Elim", 
                "Red Right Elim",
                "Red SWP",
                "Blue Left Main", 
                "Blue Right Main", 
                "Blue Left Elim", 
                "Blue Right Elim",
                "Blue SWP"
            };
            lv_label_set_text(statusLabel, statusTexts[i]);
            break;
        }
    }
}

static void skillsClicked(lv_event_t* e) {
    autonSelection = 11;  // Skills is selection #11
    autonConfirmed = true;
    
    // Update all match auton buttons to unselected
    for (int j = 0; j < 10; j++) {
        if (j < 5) {
            lv_obj_set_style_bg_color(autonButtons[j], lv_color_make(80, 20, 20), 0);
            lv_obj_set_style_border_color(autonButtons[j], ALLIANCE_RED, 0);
        } else {
            lv_obj_set_style_bg_color(autonButtons[j], lv_color_make(20, 30, 80), 0);
            lv_obj_set_style_border_color(autonButtons[j], ALLIANCE_BLUE, 0);
        }
        lv_obj_set_style_border_width(autonButtons[j], 2, 0);
        lv_obj_set_style_text_color(autonButtons[j], STEAM_WHITE, 0);
    }
    
    // Update status
    lv_label_set_text(statusLabel, "SKILLS");
    
    // Make the skills button look selected
    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_set_style_bg_color(btn, CARAMEL_GOLD, 0);
    lv_obj_set_style_border_color(btn, STEAM_WHITE, 0);
    lv_obj_set_style_border_width(btn, 4, 0);
    lv_obj_set_style_text_color(btn, ESPRESSO_BLACK, 0);
}

// SPLASH SCREEN - Shows when robot turns on
void showSplashScreen() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    
    // Set background to espresso black
    lv_obj_set_style_bg_color(scr, ESPRESSO_BLACK, 0);
    
    // Display your splash image (create this in Canva)
    lv_obj_t* splashImg = lv_img_create(scr);
    lv_img_set_src(splashImg, &caffeine_splash);
    lv_obj_align(splashImg, LV_ALIGN_CENTER, 0, 0);
    
    // Continue button - positioned to cover the button in the image
    lv_obj_t* continueBtn = lv_btn_create(scr);
    lv_obj_set_size(continueBtn, 120, 45);
    lv_obj_align(continueBtn, LV_ALIGN_CENTER, 0, 35);  // Adjust this to match your image
    
    // Style the button - coffee theme
    lv_obj_set_style_bg_color(continueBtn, COFFEE_BROWN, 0);
    lv_obj_set_style_border_color(continueBtn, CARAMEL_GOLD, 0);
    lv_obj_set_style_border_width(continueBtn, 3, 0);
    lv_obj_set_style_radius(continueBtn, 8, 0);
    
    // Button label
    lv_obj_t* continueLabel = lv_label_create(continueBtn);
    lv_label_set_text(continueLabel, "Continue");
    lv_obj_set_style_text_color(continueLabel, CREAM_LATTE, 0);
    lv_obj_center(continueLabel);
    
    // Add click event
    lv_obj_add_event_cb(continueBtn, continueClicked, LV_EVENT_CLICKED, NULL);
}

// AUTON SELECTOR - Choose your autonomous routine
void createAutonSelector() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    
    // Set background to espresso black
    lv_obj_set_style_bg_color(scr, ESPRESSO_BLACK, 0);
    
    // Title
    lv_obj_t* title = lv_label_create(scr);
    lv_label_set_text(title, "AUTONOMOUS SELECTOR");
    lv_obj_set_style_text_color(title, CREAM_LATTE, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 3);
    
    // Team number and name
    lv_obj_t* teamLabel = lv_label_create(scr);
    lv_label_set_text(teamLabel, "8031C - CAFFEINE");
    lv_obj_set_style_text_color(teamLabel, CARAMEL_GOLD, 0);
    lv_obj_align(teamLabel, LV_ALIGN_TOP_MID, 0, 20);
    
    // RED ALLIANCE LABEL
    lv_obj_t* redLabel = lv_label_create(scr);
    lv_label_set_text(redLabel, "RED ALLIANCE");
    lv_obj_set_style_text_color(redLabel, ALLIANCE_RED, 0);
    lv_obj_set_pos(redLabel, 15, 38);
    
    // BLUE ALLIANCE LABEL
    lv_obj_t* blueLabel = lv_label_create(scr);
    lv_label_set_text(blueLabel, "BLUE ALLIANCE");
    lv_obj_set_style_text_color(blueLabel, ALLIANCE_BLUE, 0);
    lv_obj_set_pos(blueLabel, 360, 38);
    
    // Button text for all 10 autons
    const char* btnTexts[] = {
        "Left\nMain",      // Red
        "Right\nMain",
        "Left\nElim",
        "Right\nElim",
        "SWP",
        "Left\nMain",      // Blue
        "Right\nMain",
        "Left\nElim",
        "Right\nElim",
        "SWP"
    };
    
    // Create RED alliance buttons (5 buttons, left side)
    for (int i = 0; i < 5; i++) {
        autonButtons[i] = lv_btn_create(scr);
        lv_obj_set_size(autonButtons[i], 105, 32);
        
        // Position: vertical stack on left side
        lv_obj_set_pos(autonButtons[i], 5, 55 + i * 36);
        
        // Style button (red alliance)
        lv_obj_set_style_bg_color(autonButtons[i], lv_color_make(80, 20, 20), 0);
        lv_obj_set_style_border_color(autonButtons[i], ALLIANCE_RED, 0);
        lv_obj_set_style_border_width(autonButtons[i], 2, 0);
        lv_obj_set_style_radius(autonButtons[i], 5, 0);
        
        // Button label
        lv_obj_t* label = lv_label_create(autonButtons[i]);
        lv_label_set_text(label, btnTexts[i]);
        lv_obj_set_style_text_color(label, STEAM_WHITE, 0);
        lv_obj_center(label);
        
        // Add click event
        lv_obj_add_event_cb(autonButtons[i], autonButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    // Create BLUE alliance buttons (5 buttons, right side)
    for (int i = 5; i < 10; i++) {
        autonButtons[i] = lv_btn_create(scr);
        lv_obj_set_size(autonButtons[i], 105, 32);
        
        // Position: vertical stack on right side
        lv_obj_set_pos(autonButtons[i], 370, 55 + (i - 5) * 36);
        
        // Style button (blue alliance)
        lv_obj_set_style_bg_color(autonButtons[i], lv_color_make(20, 30, 80), 0);
        lv_obj_set_style_border_color(autonButtons[i], ALLIANCE_BLUE, 0);
        lv_obj_set_style_border_width(autonButtons[i], 2, 0);
        lv_obj_set_style_radius(autonButtons[i], 5, 0);
        
        // Button label
        lv_obj_t* label = lv_label_create(autonButtons[i]);
        lv_label_set_text(label, btnTexts[i]);
        lv_obj_set_style_text_color(label, STEAM_WHITE, 0);
        lv_obj_center(label);
        
        // Add click event
        lv_obj_add_event_cb(autonButtons[i], autonButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    // Status box (center, shows selection)
    lv_obj_t* statusBox = lv_obj_create(scr);
    lv_obj_set_size(statusBox, 230, 70);
    lv_obj_set_pos(statusBox, 125, 60);
    lv_obj_set_style_bg_color(statusBox, DARK_ROAST, 0);
    lv_obj_set_style_border_color(statusBox, CARAMEL_GOLD, 0);
    lv_obj_set_style_border_width(statusBox, 3, 0);
    lv_obj_set_style_radius(statusBox, 8, 0);
    
    // Status box title
    lv_obj_t* statusTitle = lv_label_create(statusBox);
    lv_label_set_text(statusTitle, "SELECTED:");
    lv_obj_set_style_text_color(statusTitle, CARAMEL_GOLD, 0);
    lv_obj_align(statusTitle, LV_ALIGN_TOP_MID, 0, 3);
    
    // Status label (what's selected)
    statusLabel = lv_label_create(statusBox);
    lv_label_set_text(statusLabel, "None");
    lv_obj_set_style_text_color(statusLabel, CREAM_LATTE, 0);
    lv_label_set_long_mode(statusLabel, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(statusLabel, 210);
    lv_obj_align(statusLabel, LV_ALIGN_CENTER, 0, 8);
    lv_obj_set_style_text_align(statusLabel, LV_TEXT_ALIGN_CENTER, 0);
    
    // SKILLS button (center bottom)
    skillsBtn = lv_btn_create(scr);
    lv_obj_set_size(skillsBtn, 230, 50);
    lv_obj_set_pos(skillsBtn, 125, 140);
    
    lv_obj_set_style_bg_color(skillsBtn, COFFEE_BROWN, 0);
    lv_obj_set_style_radius(skillsBtn, 8, 0);
    lv_obj_set_style_border_color(skillsBtn, CARAMEL_GOLD, 0);
    lv_obj_set_style_border_width(skillsBtn, 3, 0);
    
    lv_obj_t* skillsLabel = lv_label_create(skillsBtn);
    lv_label_set_text(skillsLabel, "SKILLS");
    lv_obj_set_style_text_color(skillsLabel, STEAM_WHITE, 0);
    lv_obj_center(skillsLabel);
    
    lv_obj_add_event_cb(skillsBtn, skillsClicked, LV_EVENT_CLICKED, NULL);
    
    // Info text at bottom
    lv_obj_t* infoLabel = lv_label_create(scr);
    lv_label_set_text(infoLabel, "Tap to select autonomous routine");
    lv_obj_set_style_text_color(infoLabel, lv_color_make(120, 100, 80), 0);
    lv_obj_align(infoLabel, LV_ALIGN_BOTTOM_MID, 0, -5);
}

// MATCH START SCREEN - Shows when autonomous begins
void showMatchStartScreen() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    
    // Set background to cream/latte color (or match your image background)
    lv_obj_set_style_bg_color(scr, CREAM_LATTE, 0);
    
    // Display your match start image
    lv_obj_t* matchImg = lv_img_create(scr);
    lv_img_set_src(matchImg, &caffeine_match_start);
    lv_obj_align(matchImg, LV_ALIGN_CENTER, 0, 0);
}