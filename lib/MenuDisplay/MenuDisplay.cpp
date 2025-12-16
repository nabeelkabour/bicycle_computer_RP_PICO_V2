#include <MenuDisplay.h>
#include <Pins.h>
#include <Menu.h>
#include <Helper.h>
#include <Settings.h>


MenuDisplay mainDisplay;

void displayDraw(int start, int end) 
{
    for (int index = start; index < end; ++index) 
    {
        if (index == mainDisplay.cursor) 
        {
            // std::cout << ">";
            mainDisplay.display->print("->");
        } 
        // else 
        // {
        //     // std::cout << " ";
        //     mainDisplay.display->print(" "); // Posibly use double "  "
        // }
        // std::cout << vals[index] << "\n";
        // mainDisplay.display->println(mainDisplay.pageCurrent->contents[index]->name.c_str());
        mainDisplay.pageCurrent->contents[index]->draw();
    }
}

void displayTitle(std::string title)
{
    int16_t positionStart = (84 - title.length() * 6) / 2;

    mainDisplay.display->clearDisplay();
    mainDisplay.display->fillRect(0, 0, positionStart, 8, BLACK);
    mainDisplay.display->setCursor(positionStart, 0);
    mainDisplay.display->setTextColor(WHITE, BLACK);
    mainDisplay.display->print(title.c_str());
    mainDisplay.display->fillRect
    (
        mainDisplay.display->getCursorX(), 
        0,
        84 - mainDisplay.display->getCursorX(),
        8,
        BLACK
    );
    mainDisplay.display->setTextColor(BLACK, WHITE);
    mainDisplay.display->println("\n");
}

void MenuDisplay::setup()
{
    display = new Adafruit_PCD8544(DISP_DC, DISP_CS, DISP_RST, &SPI1);
    display->begin();
    display->setContrast(60);
    display->clearDisplay();
    display->setTextSize(1);
    // display.setTextColor(BLACK);
    display->setCursor(0, 0);
    display->display();
    
    pageChange(&menuMain);
}

void MenuDisplay::loop()
{    
    //Get input.
    input.upButton = digitalRead(UPBTNPIN);
    input.downButton = digitalRead(DOWNBTNPIN);
    input.confirmButton = digitalRead(GREENBTNPIN);
    input.backButton = digitalRead(REDBTNPIN);

    //Delta Time
    size_t timeCurrent = micros();

    size_t delta = timeCurrent - timePrevious;
    timePrevious = timeCurrent;
    float timeDeltaSeconds = float(delta) / 1000000.f; 

    cursor += !input.downButton - !input.upButton;

    // if(cursor < 0) cursor = 0;
    // else if(cursor > pageCurrent->contents.size() - 1) cursor = pageCurrent->contents.size() - 1;

    if(pageCurrent->flagLoop)
    {
        pageCurrent->loop(timeDeltaSeconds);

        if(!input.backButton)
        {
            pageChange(pagePrevious);
            delay(250);
        }
        else if(!input.confirmButton) 
        {
            pageCurrent->contents[cursor]->action();
            delay(250);    
        }
    }
    else if(!input.confirmButton or !input.backButton or !input.upButton or !input.downButton or flagDraw)
    {
        {
            flagDraw = false;
            pageCurrent->loop(timeDeltaSeconds);

            if(!input.backButton) pageChange(pagePrevious);
            else if(!input.confirmButton) pageCurrent->contents[cursor]->action();

            delay(250); 
        }
    }
}

void MenuDisplay::pageChange(Menu::Page::Base* pageNew)
{
    if(!pageNew) return;

    if(pageCurrent)
    {
        for(Menu::Element::Base* elem : pageCurrent->contents) 
            delete elem;
        pageCurrent->contents.clear();
        pageCurrent->destroy();
    }

    pagePrevious = pageCurrent;

    pageCurrent = pageNew;
    pageCurrent->create();

    cursor = pageCurrent->cursorDefaultVal;
    flagDraw = true;

    // if(!pageNew) return;

    // if(pageCurrent)
    // {
    //     delete pageCurrent;
    // }
    
    // pageCurrent = pageNew;
    // if (pageCurrent) pageCurrent->create();
}

void Menu::Element::PageSwitcher::action()
{
    //Switch to the target page.
    mainDisplay.pageChange(pageTarget);
}

void Menu::Element::PageSwitcher::draw()
{
    mainDisplay.display->println(name.c_str());
}

void Menu::Page::Navigation::draw()
{
    mainDisplay.display->setCursor(0, 0);
    mainDisplay.display->println(title.c_str());
}

void Menu::Page::Navigation::create()
{

}

void Menu::Page::Navigation::loop(float timeDeltaSeconds)
{
    displayTitle(title);

    if(mainDisplay.cursor < 0) mainDisplay.cursor = 0;
    else if(mainDisplay.cursor > contents.size() - 1) mainDisplay.cursor = contents.size() - 1;
    
    if(mainDisplay.cursor < 4)
    {
        displayDraw(0, contents.size());
    }
    else if (mainDisplay.cursor < contents.size() - 3) 
    {
        if (mainDisplay.cursor < 3) 
        {
            displayDraw(0, 5);
        } 
        else 
        {
            displayDraw(mainDisplay.cursor - 2, mainDisplay.cursor + 3);
        }
    } 
    else if (mainDisplay.cursor <= contents.size() - 1) 
    {
        displayDraw(contents.size() - 5, contents.size());
    }

    mainDisplay.display->display();     
    
    // for(Menu::Element::Base* elem : contents)
    // {
    //     elem.
    // }

    // if(buttonSelect)
    // {
    //     int cursor = 2;
    //     contents[cursor]->action();
    // }
}

void Menu::Page::VariableEnter::destroy()
{
    delete variable;
}

void Menu::Page::MainMenu::create()
{
    Navigation::create();

    //Initialize.
    title = "Main Menu";
    cursorDefaultVal = 0;
    contents.push_back(new Menu::Element::PageSwitcher("Settings", &mainDisplay.menuSettings));
    // contents.push_back(new Menu::Element::PageSwitcher("Tire Circ", &mainDisplay.menuEnterTireCirc));
    contents.push_back(new Menu::Element::PageSwitcher("page #3.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #4.", &mainDisplay.menuMain));
    contents.push_back(new Menu::Element::PageSwitcher("page #5.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #6.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #7.", &mainDisplay.menuMain));
    contents.push_back(new Menu::Element::PageSwitcher("page #8.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #9.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #10.", &mainDisplay.menuMain));
    contents.push_back(new Menu::Element::PageSwitcher("page #11.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #12.", nullptr));
}

void Menu::Page::MainMenu::destroy()
{

}

void Menu::Page::Lights::create()
{
    title = "Lights";
    cursorDefaultVal = 0;
    contents.push_back(new Menu::Element::PageSwitcher("Lights", &mainDisplay.menuLights));
    contents.push_back(new Menu::Element::PageSwitcher("Main Menu", &mainDisplay.menuMain));
}

void Menu::Page::Lights::destroy()
{
    
}

void Menu::Page::LightsBrightness::create()
{
    title = "Brightness:";
    cursorDefaultVal = settings.ledBrightness;
    valueMin = 0;
    valueMax = 255;

    variable = new Menu::Element::VariableInt("Brightness", &settings.ledBrightness);
} 

void Menu::Page::LightsBrightness::destroy()
{
    delete variable;
}

void Menu::Page::LightsBrightness::loop(float timeDeltaSeconds)
{
    VariableEnter::loop(timeDeltaSeconds);
}

void Menu::Page::LightsBrightness::draw()
{

}

void Menu::Page::Settings::create()
{
    title = "Settings";
    cursorDefaultVal = 0;
    contents.push_back(new Menu::Element::PageSwitcher("Sound", &mainDisplay.menuSound));
    contents.push_back(new Menu::Element::PageSwitcher("Lights", &mainDisplay.menuLights));
    contents.push_back(new Menu::Element::PageSwitcher("Tire Circ", &mainDisplay.menuEnterTireCirc)); 
    contents.push_back(new Menu::Element::PageSwitcher("Main Menu", &mainDisplay.menuMain));
}

void Menu::Page::Settings::destroy()
{

}

void Menu::Page::EnterTireCirc::create()
{
    title = "Tire Circ:";
    cursorDefaultVal = settings.tireCirc / 1000;
    flagLoop = true;
}

void Menu::Page::EnterTireCirc::destroy()
{
    // delete 
}

void Menu::Page::EnterTireCirc::draw()
{
    
}

void Menu::Page::EnterTireCirc::loop(float timeDeltaSeconds)
{
    displayTitle(title);

    mainDisplay.display->setTextSize(3);

    if(mainDisplay.cursor > 9) mainDisplay.cursor = 0;
    else if(mainDisplay.cursor < 0) mainDisplay.cursor = 9;

    tireDigits[stage] = mainDisplay.cursor;

    if(!mainDisplay.input.confirmButton) 
    {
        --stage;
        delay(250);
    }
    if(stage < 0)
    {
        settings.tireCirc =
              tireDigits[3] * 1000 
            + tireDigits[2] * 100
            + tireDigits[1] * 10
            + tireDigits[0];

        stage = 3; 

        mainDisplay.display->print(settings.tireCirc);
    } 

    mainDisplay.display->setTextSize(1);
    mainDisplay.display->display();
}

void Menu::Element::VariableInt::draw()
{
    mainDisplay.display->setTextSize(3);
    mainDisplay.display->println(*value);
    mainDisplay.display->setTextSize(1);
}

void Menu::Element::VariableInt::action()
{

}

void Menu::Page::Sound::create()
{
    title = "Volume:";
    cursorDefaultVal = settings.soundVolume;

    soundLevel = new Element::VariableInt("Volume:", &settings.soundVolume);
    //contents.push_back(new Element::VariableInt("Volume:", &settings.soundVolume));
}

void Menu::Page::Sound::destroy()
{
    delete soundLevel;
}

void Menu::Page::Sound::loop(float timeDeltaSeconds)
{
    VariableEnter::loop(timeDeltaSeconds);

    timeDeltaSecondsCursor += timeDeltaSeconds;

    if(mainDisplay.cursor < valueMin) mainDisplay.cursor = valueMin;
    else if(mainDisplay.cursor > valueMax) mainDisplay.cursor = valueMax;

    int8_t valsign = sgn(cursorPrev - mainDisplay.cursor);

    int32_t valIncrement = 1;
    if(timeDeltaSeconds >= 2.5f)
    {
        valIncrement = 3;
    }

    *soundLevel->value +=  valsign * valIncrement;// mainDisplay.cursor;// + valueAcceleration; //+ volumeSign * int32_t(floor(timeDeltaSecondsCursor) * 2.f);    
    soundLevel->draw();
    mainDisplay.display->display();
}

void Menu::Page::Sound::draw()
{
}

void Menu::Page::VariableEnter::loop(float timeDeltaSeconds)
{
    displayTitle(title);
}