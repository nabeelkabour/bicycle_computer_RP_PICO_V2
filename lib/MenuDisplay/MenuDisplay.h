#pragma once
 
// MenuDisplay is a display system on an independent display.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <string>
#include <vector>
#include "Menu.h"

class MenuDisplay
{
public:
    Adafruit_PCD8544* display = nullptr;

    bool upButton = true;
    bool downButton = true;
    bool confirmButton = true;
    bool backButton = true;

    Menu::Page::Base* pageCurrent = nullptr;
    int32_t cursor = 0;

    // Menu::Page::Base* menuNavi = nullptr;
    Menu::Page::MainMenu menuMain;

    void setup();
    void loop();
    void pageChange(Menu::Page::Base* pageNew);
};

extern MenuDisplay mainDisplay;

void displayDraw(int start, int end);