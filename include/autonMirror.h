#pragma once
#include "lemlib/api.hpp"

inline bool MIRROR = false;

// Flips Y values
inline float m(float value) {
    return MIRROR ? -value : value;
}

// Flips Y and heading in a full pose
inline lemlib::Pose mp(float x, float y, float theta) {
    if (MIRROR) return lemlib::Pose(x, -y, -theta);
    return lemlib::Pose(x, y, theta);
}