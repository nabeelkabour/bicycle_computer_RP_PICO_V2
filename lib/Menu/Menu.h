#pragma once

#include <string>

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
            virtual void draw() = 0;
        };
    }

    namespace Page
    {
        class Base
        {
        public: 
            std::vector<Element::Base*> contents;
            std::string title = "";

            // Base();
            //~Base();
            virtual void draw() = 0;
            virtual void create() = 0;
            virtual void loop() = 0;
        };

        class Navigation : public Base
        {
        public:
            //constexpr static int8_t MAX_ELEMENTS = 5;

            // Navigation();
            virtual void draw() override;
            virtual void create() override;
            virtual void loop() override;
        };

        class MainMenu final : public Navigation
        {
        public:
            void create() override; 
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