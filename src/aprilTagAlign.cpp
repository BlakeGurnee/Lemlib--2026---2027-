#include "main.h"
#include "globals.hpp"
#include "pros/ai_vision.hpp"
#include <cmath>
#include <cstdint>

// ==========================================
// ALIGNMENT SETTINGS
// ==========================================

constexpr int CAMERA_CENTER_X = 160;

constexpr int TIMEOUT_MS = 5000;
constexpr int LOST_TAG_TIMEOUT_MS = 250;

// Approach speed settings
constexpr int FAST_SPEED = 65;
constexpr int SLOW_SPEED = 18;

// Average AprilTag side length in camera pixels
constexpr float SLOWDOWN_START_SIZE = 55.0f;
constexpr float TARGET_TAG_SIZE = 130.0f;

// Steering settings
constexpr int CENTER_TOLERANCE = 7;
constexpr float TURN_KP = 0.45f;
constexpr int MAX_TURN = 35;

// ==========================================
// HELPER FUNCTIONS
// ==========================================

static float edgeLength(int x1, int y1, int x2, int y2) {
    const float dx = static_cast<float>(x2 - x1);
    const float dy = static_cast<float>(y2 - y1);
    return std::sqrt(dx * dx + dy * dy);
}

static int clampDrive(int value) {
    if (value > 100) return 100;
    if (value < -100) return -100;
    return value;
}

// ==========================================
// APRILTAG DETECTION CONTROLS
// ==========================================

// Call once before an alignment attempt.
bool startDetection() {
    return aiVision.enable_detection_types(
        pros::AivisionModeType::tags
    ) == PROS_SUCCESS;
}

// Call after scoring or whenever AprilTag tracking is no longer needed.
bool stopDetection() {
    return aiVision.disable_detection_types(
        pros::AivisionModeType::tags
    ) == PROS_SUCCESS;
}

// ==========================================
// MAIN ALIGNMENT FUNCTION
// ==========================================

// Defaults to tag ID 3 when called as alignToGoal().
// Pass another ID, such as alignToGoal(4), to target a different tag.
bool alignToGoal(int targetTagID) {
    chassis.tank(0, 0, false);

    const uint32_t startTime = pros::millis();
    uint32_t lastSeenTime = 0;
    bool hasSeenTag = false;

    while (pros::millis() - startTime < TIMEOUT_MS) {
        const uint32_t now = pros::millis();
        const auto objects = aiVision.get_all_objects();

        bool foundTag = false;
        int centerX = CAMERA_CENTER_X;
        float largestTagSize = 0.0f;

        // Find the largest visible AprilTag with the requested ID.
        for (const auto& object : objects) {
            if (!pros::AIVision::is_type(
                    object, pros::AivisionDetectType::tag)) {
                continue;
            }

            if (object.id != targetTagID) {
                continue;
            }

            const auto& tag = object.object.tag;

            const float size = (
                edgeLength(tag.x0, tag.y0, tag.x1, tag.y1) +
                edgeLength(tag.x1, tag.y1, tag.x2, tag.y2) +
                edgeLength(tag.x2, tag.y2, tag.x3, tag.y3) +
                edgeLength(tag.x3, tag.y3, tag.x0, tag.y0)
            ) / 4.0f;

            const int tagCenterX = (
                tag.x0 + tag.x1 + tag.x2 + tag.x3
            ) / 4;

            if (size > largestTagSize) {
                largestTagSize = size;
                centerX = tagCenterX;
                foundTag = true;
            }
        }

        // If the requested tag is not visible, stop and wait briefly for it.
        if (!foundTag) {
            chassis.tank(0, 0, false);

            if (hasSeenTag &&
                now - lastSeenTime > LOST_TAG_TIMEOUT_MS) {
                return false;
            }

            pros::delay(20);
            continue;
        }

        hasSeenTag = true;
        lastSeenTime = now;

        // Positive error means the tag is to the right of camera center.
        const int error = centerX - CAMERA_CENTER_X;
        const bool centered =
            error >= -CENTER_TOLERANCE &&
            error <= CENTER_TOLERANCE;
        const bool closeEnough = largestTagSize >= TARGET_TAG_SIZE;

        // Finish only when the robot is both centered and close enough.
        if (centered && closeEnough) {
            chassis.tank(0, 0, false);
            return true;
        }

        // Proportional steering correction.
        int turn = static_cast<int>(error * TURN_KP);
        if (turn > MAX_TURN) turn = MAX_TURN;
        if (turn < -MAX_TURN) turn = -MAX_TURN;

        // Fast when far away, then smoothly slow as the tag gets larger.
        int forward = 0;

        if (largestTagSize <= SLOWDOWN_START_SIZE) {
            forward = FAST_SPEED;
        } else if (largestTagSize < TARGET_TAG_SIZE) {
            float progress =
                (largestTagSize - SLOWDOWN_START_SIZE) /
                (TARGET_TAG_SIZE - SLOWDOWN_START_SIZE);

            if (progress < 0.0f) progress = 0.0f;
            if (progress > 1.0f) progress = 1.0f;

            forward = FAST_SPEED - static_cast<int>(
                progress * (FAST_SPEED - SLOW_SPEED)
            );
        }
        // At or beyond TARGET_TAG_SIZE, forward remains zero so the
        // robot can make its final left/right correction in place.

        const int left = clampDrive(forward + turn);
        const int right = clampDrive(forward - turn);

        chassis.tank(left, right, true);
        pros::delay(20);
    }

    // Timeout: leave the drivetrain stopped.
    chassis.tank(0, 0, false);
    return false;
}
