#pragma once
#include <cmath>
#include "lemlib/api.hpp"

inline bool MIRROR = false;

inline float m(float y) { return MIRROR ? -y : y; }

// Mirrored heading for a Y-flip, normalized to [0, 360)
inline float mh(float heading) {
    if (!MIRROR) return heading;
    float r = std::fmod(180.0f - heading, 360.0f);
    return r < 0 ? r + 360.0f : r;
}

inline lemlib::Pose mp(float x, float y, float theta) {
    return lemlib::Pose(x, m(y), mh(theta));
}