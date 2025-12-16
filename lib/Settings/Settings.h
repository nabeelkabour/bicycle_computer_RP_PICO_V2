#pragma once

#include <stdint.h>

struct Settings
{
    int32_t soundVolume = 40;
    int32_t tireCirc = 2110;
    int32_t ledBrightness = 255;
    int32_t magnetsNum = 1;
};

extern Settings settings;