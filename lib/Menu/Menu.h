#pragma once

#include <Settings.h>
#include <string>
#include <vector>

namespace Menu
{
    namespace Element
    {
        class Base
        {
        public:
            std::string name = "";

            Base (std::string _name) : name(_name) {}
            virtual void action() = 0;
            // virtual void loop() = 0;
            virtual void draw() = 0;
        };

        class VariableInt : public Base
        {
        public:
            int32_t* value = nullptr;
            // int32_t valueMin = 0, valueMax = 0;

            // VariableInt(std::string _name, int32_t* _value, int32_t _min, int32_t _max) :
            //     Base(_name), value(_value), min(_min), max(_max) {}

            VariableInt(std::string _name, int32_t* _value) :
                Base(_name), value(_value) {}

            void action() override;
            // void loop() override;
            void draw() override;
        };
    }

    namespace Page
    {
        class Base
        {
        public: 
            std::vector<Element::Base*> contents;
            std::string title = "";

            int32_t cursorDefaultVal = 0;
            bool flagLoop = false;

            // Base();
            //~Base();
            virtual void draw() = 0;
            virtual void create() = 0;
            virtual void loop(float timeDeltaSeconds) = 0;
            virtual void destroy() = 0;
        };

        class Navigation : public Base
        {
        public:
            //constexpr static int8_t MAX_ELEMENTS = 5;

            // Navigation();
            virtual void draw() override;
            virtual void create() override;
            virtual void loop(float timeDeltaSeconds) override;
        };

        class VariableEnter : public Base
        {
        public:
            Element::VariableInt* variable = nullptr;
            int32_t valueMin, valueMax;

            virtual void create() override;
            virtual void loop(float timeDeltaSeconds) override;
            virtual void destroy() override;
        };

        class MainMenu final : public Navigation
        {
        public:
            void create() override; 
            void destroy() override;
        };

        class Settings final : public Navigation
        {
        public:
            void create() override;
            void destroy() override;
        };

        class Sound final : public VariableEnter
        {
        public:
            float timeDeltaSecondsCursor = 0.f;
            int32_t cursorPrev = settings.soundVolume;

            Element::VariableInt* soundLevel = nullptr;

            void create() override;
            void loop(float timeDeltaSeconds) override;
            void draw() override;
            void destroy() override;
        };

        class Lights final : public Navigation
        {
        public:
            void create() override;
            void destroy() override;
        };

        class LightsBrightness final : public VariableEnter
        {
        public:
            void create() override;
            void loop(float timeDeltaSeconds) override;
            void destroy() override;
            void draw() override;
        };

        class EnterTireCirc final : public Base
        {
        public:
            int8_t stage = 3;
            int8_t tireDigits[4] = {0, 1, 1, 2};
            float timeAcc = 0.f;
            bool blinkOn = false;

            void draw();
            void create();
            void loop(float timeDeltaSeconds);
            void destroy() override;
        };
    }

    namespace Element
    {
        class PageSwitcher : public Base
        {
        public:
            Page::Base* pageTarget = nullptr;

            PageSwitcher(std::string _name, Page::Base* _pageTarget) : 
                Base(_name), pageTarget(_pageTarget)  {}
            virtual void action() override;
            virtual void draw() override;
        };
    }
}