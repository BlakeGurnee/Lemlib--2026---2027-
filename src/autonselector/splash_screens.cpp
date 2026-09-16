#include "splash_screens.hpp"

// Global variables
int autonSelection = 0;
bool autonConfirmed = false;

// All 11 choices (10 match autons + Skills), in switch-case order.
// autonSelection ends up being (index + 1), matching your switch(autonSelection) exactly.
static const char* kAutonLabels[11] = {
    "Red Left Main", "Red Right Main", "Red Left Elim", "Red Right Elim", "Red SWP",
    "Blue Left Main", "Blue Right Main", "Blue Left Elim", "Blue Right Elim", "Blue SWP",
    "Skills",
};
// Static, compiled-in route pictures (same mechanism as caffeine_splash /
// caffeine_match_start below -- converted via the LVGL image converter,
// no SD card or gif involved). See CHANGES.md for how these were made.
static const lv_img_dsc_t* kAutonRouteImages[11] = {
    &route_red_left_main, &route_red_right_main, &route_red_left_elim,
    &route_red_right_elim, &route_red_swp, &route_blue_left_main,
    &route_blue_right_main, &route_blue_left_elim, &route_blue_right_elim,
    &route_blue_swp, &route_skills,
};
// Accent bar color per row: red alliance / blue alliance / skills (coffee tan).
static lv_color_t accentColorFor(int index) {
    if (index < 5) return ALLIANCE_RED;
    if (index < 10) return ALLIANCE_BLUE;
    return CAFFEINE_TAN;
}

// Store objects globally so click handlers and selectIndex() can reach them
static lv_obj_t* autonButtons[11];
static lv_obj_t* fieldImg;
static int selectedIndex = -1;   // -1 == nothing chosen yet

static void selectIndex(int index);

static void selectIndex(int index) {
    if (index < 0 || index >= 11 || index == selectedIndex) return;

    if (selectedIndex >= 0) {
        // restore the previous row to its unselected alliance/skills color
        lv_obj_t* prev = autonButtons[selectedIndex];
        lv_obj_set_style_bg_color(prev, CAFFEINE_ESPRESSO, 0);
        lv_obj_set_style_border_color(prev, accentColorFor(selectedIndex), 0);
        lv_obj_set_style_border_width(prev, 2, 0);
        lv_obj_set_style_text_color(prev, CAFFEINE_CREAM, 0);
    }

    selectedIndex = index;
    autonSelection = index + 1;  // matches your switch(autonSelection) case numbers 1-11
    autonConfirmed = (index == 10);  // Skills auto-confirms, same as your original behavior

    lv_obj_t* cur = autonButtons[index];
    lv_obj_set_style_bg_color(cur, CAFFEINE_ORANGE, 0);
    lv_obj_set_style_border_color(cur, CAFFEINE_CREAM, 0);
    lv_obj_set_style_border_width(cur, 3, 0);
    lv_obj_set_style_text_color(cur, CAFFEINE_ESPRESSO, 0);
    lv_obj_scroll_to_view(cur, LV_ANIM_ON);

    lv_img_set_src(fieldImg, kAutonRouteImages[index]);
}

// Button click event handlers
static void continueClicked(lv_event_t* e) {
    createAutonSelector();
}

static void rowClicked(lv_event_t* e) {
    intptr_t idx = reinterpret_cast<intptr_t>(lv_event_get_user_data(e));
    selectIndex(static_cast<int>(idx));
}

static void upClicked(lv_event_t* e) {
    selectIndex(selectedIndex <= 0 ? 0 : selectedIndex - 1);
}

static void downClicked(lv_event_t* e) {
    int next = selectedIndex < 0 ? 0 : selectedIndex + 1;
    if (next > 10) next = 10;
    selectIndex(next);
}

static void confirmClicked(lv_event_t* e) {
    autonConfirmed = true;
}

// Small decorative coffee cup built from LVGL primitives -- no image asset needed.
static void buildCoffeeCup(lv_obj_t* parent) {
    lv_obj_t* cup = lv_obj_create(parent);
    lv_obj_remove_style_all(cup);
    lv_obj_set_size(cup, 60, 66);
    lv_obj_center(cup);
    lv_obj_clear_flag(cup, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(cup, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* lid = lv_obj_create(cup);
    lv_obj_remove_style_all(lid);
    lv_obj_set_size(lid, 44, 8);
    lv_obj_align(lid, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(lid, CAFFEINE_ESPRESSO, 0);
    lv_obj_set_style_bg_opa(lid, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(lid, 3, 0);

    lv_obj_t* band = lv_obj_create(cup);
    lv_obj_remove_style_all(band);
    lv_obj_set_size(band, 40, 12);
    lv_obj_align(band, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_style_bg_color(band, CAFFEINE_ESPRESSO, 0);
    lv_obj_set_style_bg_opa(band, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(band, 2, 0);

    lv_obj_t* body = lv_obj_create(cup);
    lv_obj_remove_style_all(body);
    lv_obj_set_size(body, 38, 34);
    lv_obj_align(body, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(body, CAFFEINE_CREAM, 0);
    lv_obj_set_style_bg_opa(body, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(body, 4, 0);

    lv_obj_t* bean = lv_obj_create(body);
    lv_obj_remove_style_all(bean);
    lv_obj_set_size(bean, 12, 18);
    lv_obj_center(bean);
    lv_obj_set_style_bg_color(bean, CAFFEINE_ESPRESSO, 0);
    lv_obj_set_style_bg_opa(bean, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(bean, LV_RADIUS_CIRCLE, 0);

    static lv_point_t creasePts[2] = {{0, -8}, {0, 8}};
    static lv_style_t creaseStyle;
    lv_style_init(&creaseStyle);
    lv_style_set_line_width(&creaseStyle, 2);
    lv_style_set_line_color(&creaseStyle, CAFFEINE_CREAM);
    lv_style_set_line_rounded(&creaseStyle, true);
    lv_obj_t* crease = lv_line_create(bean);
    lv_obj_add_style(crease, &creaseStyle, 0);
    lv_line_set_points(crease, creasePts, 2);
    lv_obj_align(crease, LV_ALIGN_CENTER, 6, 0);
}

// SPLASH SCREEN - Shows when robot turns on
void showSplashScreen() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    
    // Set background to espresso brown
    lv_obj_set_style_bg_color(scr, CAFFEINE_ESPRESSO, 0);
    
    // Display your first image
    lv_obj_t* splashImg = lv_img_create(scr);
    lv_img_set_src(splashImg, &caffeine_splash);
    lv_obj_align(splashImg, LV_ALIGN_CENTER, 0, -20);
    
    // Continue button
    lv_obj_t* continueBtn = lv_btn_create(scr);
    lv_obj_set_size(continueBtn, 150, 50);
    lv_obj_align(continueBtn, LV_ALIGN_CENTER, 0, 60);
    
    // Style the button
    lv_obj_set_style_bg_color(continueBtn, CAFFEINE_ESPRESSO, 0);
    lv_obj_set_style_border_color(continueBtn, CAFFEINE_CREAM, 0);
    lv_obj_set_style_border_width(continueBtn, 3, 0);
    lv_obj_set_style_radius(continueBtn, 10, 0);
    
    // Button label
    lv_obj_t* continueLabel = lv_label_create(continueBtn);
    lv_label_set_text(continueLabel, "Continue");
    lv_obj_set_style_text_color(continueLabel, CAFFEINE_CREAM, 0);
    lv_obj_center(continueLabel);
    
    // Add click event
    lv_obj_add_event_cb(continueBtn, continueClicked, LV_EVENT_CLICKED, NULL);
}

// AUTON SELECTOR - Choose your autonomous routine
// Layout matches the team's reference art: scrollable list on the left,
// up/down arrows + coffee cup in the middle, field-path preview on the right.
void createAutonSelector() {
    selectedIndex = -1;

    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    lv_obj_set_style_bg_color(scr, CAFFEINE_ESPRESSO, 0);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    // --- left: scrollable auton list -----------------------------------
    lv_obj_t* listCont = lv_obj_create(scr);
    lv_obj_set_pos(listCont, 6, 6);
    lv_obj_set_size(listCont, 170, 228);
    lv_obj_set_style_bg_opa(listCont, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(listCont, 0, 0);
    lv_obj_set_style_pad_all(listCont, 2, 0);
    lv_obj_set_style_pad_gap(listCont, 4, 0);
    lv_obj_set_flex_flow(listCont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(listCont, LV_DIR_VER);
    lv_obj_add_flag(listCont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(listCont, LV_SCROLLBAR_MODE_AUTO);

    for (int i = 0; i < 11; i++) {
        lv_obj_t* btn = lv_btn_create(listCont);
        autonButtons[i] = btn;
        lv_obj_set_size(btn, LV_PCT(100), 32);
        lv_obj_set_style_radius(btn, 6, 0);
        lv_obj_set_style_bg_color(btn, CAFFEINE_ESPRESSO, 0);
        lv_obj_set_style_border_color(btn, accentColorFor(i), 0);
        lv_obj_set_style_border_width(btn, 2, 0);
        lv_obj_set_style_pad_left(btn, 10, 0);
        lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, kAutonLabels[i]);
        lv_obj_set_style_text_color(label, CAFFEINE_CREAM, 0);
        lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);

        lv_obj_add_event_cb(btn, rowClicked, LV_EVENT_CLICKED,
                             reinterpret_cast<void*>(static_cast<intptr_t>(i)));
    }

    // --- middle: up arrow / coffee cup / down arrow ---------------------
    lv_obj_t* midCont = lv_obj_create(scr);
    lv_obj_set_pos(midCont, 182, 6);
    lv_obj_set_size(midCont, 70, 228);
    lv_obj_set_style_bg_opa(midCont, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(midCont, 0, 0);
    lv_obj_clear_flag(midCont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* upBtn = lv_btn_create(midCont);
    lv_obj_set_size(upBtn, 56, 46);
    lv_obj_align(upBtn, LV_ALIGN_TOP_MID, 0, 4);
    lv_obj_set_style_radius(upBtn, 10, 0);
    lv_obj_set_style_bg_color(upBtn, CAFFEINE_CREAM, 0);
    lv_obj_set_style_border_width(upBtn, 0, 0);
    lv_obj_add_event_cb(upBtn, upClicked, LV_EVENT_CLICKED, NULL);
    lv_obj_t* upLabel = lv_label_create(upBtn);
    lv_label_set_text(upLabel, LV_SYMBOL_UP);
    lv_obj_set_style_text_color(upLabel, CAFFEINE_ESPRESSO, 0);
    lv_obj_center(upLabel);

    lv_obj_t* downBtn = lv_btn_create(midCont);
    lv_obj_set_size(downBtn, 56, 46);
    lv_obj_align(downBtn, LV_ALIGN_BOTTOM_MID, 0, -4);
    lv_obj_set_style_radius(downBtn, 10, 0);
    lv_obj_set_style_bg_color(downBtn, CAFFEINE_CREAM, 0);
    lv_obj_set_style_border_width(downBtn, 0, 0);
    lv_obj_add_event_cb(downBtn, downClicked, LV_EVENT_CLICKED, NULL);
    lv_obj_t* downLabel = lv_label_create(downBtn);
    lv_label_set_text(downLabel, LV_SYMBOL_DOWN);
    lv_obj_set_style_text_color(downLabel, CAFFEINE_ESPRESSO, 0);
    lv_obj_center(downLabel);

    buildCoffeeCup(midCont);

    // --- right: field-path preview ---------------------------------------
    lv_obj_t* fieldCont = lv_obj_create(scr);
    lv_obj_set_pos(fieldCont, 258, 12);
    lv_obj_set_size(fieldCont, 216, 216);
    lv_obj_set_style_bg_opa(fieldCont, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(fieldCont, 2, 0);
    lv_obj_set_style_border_color(fieldCont, CAFFEINE_CREAM, 0);
    lv_obj_set_style_pad_all(fieldCont, 0, 0);
    lv_obj_clear_flag(fieldCont, LV_OBJ_FLAG_SCROLLABLE);

    fieldImg = lv_img_create(fieldCont);
    lv_obj_center(fieldImg);

    selectIndex(0);  // default to the first auton in the list
}

// MATCH START SCREEN - Shows when autonomous begins
void showMatchStartScreen() {
    lv_obj_t* scr = lv_obj_create(NULL);
    lv_scr_load(scr);
    
    // Set background to cream
    lv_obj_set_style_bg_color(scr, CAFFEINE_CREAM, 0);
    
    // Display your second image
    lv_obj_t* matchImg = lv_img_create(scr);
    lv_img_set_src(matchImg, &caffeine_match_start);
    lv_obj_align(matchImg, LV_ALIGN_CENTER, 0, 0);
}
