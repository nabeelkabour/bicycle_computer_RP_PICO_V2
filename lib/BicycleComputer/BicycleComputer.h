#pragma once

#include <Menu.h>
#include <stdint.h>
#include <Arduino.h>

namespace Menu
{
    namespace Element
    {
        class SpeedMeter final : public Base
        {
        public:
            uint32_t intervalTime = 1500;
            int32_t timeUpdatePrev = 0;
            uint16_t count = 0;
            bool reedSwitchValPrev = HIGH;
            float speed = 0.f;
            int32_t x, y;

            void create();
            void loop(float timeDeltaSeconds);
            void action() override;
            void draw() override;

            SpeedMeter(std::string _name, int32_t _x, int32_t _y) :
                Base(_name), x(_x), y(_y) {}
            void pollHallSensor();
            void measureSpeed();
            void displaySpeed();
        };
    }
}

namespace Menu
{
    namespace Page
    {
        class SpeedDist final : public Base
        {
        public:
            Element::SpeedMeter* speedMeter = nullptr;

            //SpeedDist();
            void draw();
            void create();
            void loop(float timeDeltaSeconds);
            void destroy() override;
        };
    }
}