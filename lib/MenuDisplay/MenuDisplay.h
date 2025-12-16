#pragma once
 
// MenuDisplay is a display system on an independent display.

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>
#include <BicycleComputer.h>
#include <string>
#include <vector>
#include <Menu.h>

struct UserInput 
{
    bool upButton = true;
    bool downButton = true;
    bool confirmButton = true;
    bool backButton = true;
};

class Adafruit_PCD8544;

class MenuDisplay
{
public:
    Adafruit_PCD8544* display = nullptr;

    bool flagDraw = true;

    size_t timePrevious = 0;

    Menu::Page::Base* pageCurrent = nullptr;
    Menu::Page::Base* pagePrevious = nullptr;
    int32_t cursor = 0;
    UserInput input;

    Menu::Page::MainMenu menuMain;
    Menu::Page::Settings menuSettings;
    Menu::Page::Sound menuSound;
    Menu::Page::Lights menuLights;
    Menu::Page::LightsBrightness menuBrightness;
    Menu::Page::EnterTireCirc menuEnterTireCirc;
    Menu::Page::SpeedDist pageSpdDst;

    void setup();
    void loop();
    void pageChange(Menu::Page::Base* pageNew);
};

extern MenuDisplay mainDisplay;

void displayDraw(int start, int end);