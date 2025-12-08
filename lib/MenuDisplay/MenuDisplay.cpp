#include <MenuDisplay.h>
#include <Pins.h>
#include <Menu.h>

MenuDisplay mainDisplay;

void displayDraw(int start, int end) 
{
    for (int index = start; index < end; ++index) 
    {
        if (index == mainDisplay.cursor) 
        {
            // std::cout << ">";
            mainDisplay.display->print(">");
        } 
        else 
        {
            // std::cout << " ";
            mainDisplay.display->print(" "); // Posibly use double "  "
        }
        // std::cout << vals[index] << "\n";
        // mainDisplay.display->println(mainDisplay.pageCurrent->contents[index]->name.c_str());
        mainDisplay.pageCurrent->contents[index]->draw();
    }
}

void MenuDisplay::setup()
{
    //menuNavi = new Menu::Page::Navigation;

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
    upButton = digitalRead(UPBTNPIN);
    downButton = digitalRead(DOWNBTNPIN);
    confirmButton = digitalRead(GREENBTNPIN);
    backButton = digitalRead(REDBTNPIN);

    cursor += !downButton - !upButton;

    if(cursor < 0) cursor = 0;
    else if(cursor > pageCurrent->contents.size()) cursor = pageCurrent->contents.size() - 1;

    if(!confirmButton or !backButton or !upButton or !downButton)
    {
        // display->clearDisplay();
        // display->setCursor(0, 0);
        // // display->print("    ");
        // // display->setCursor(0, 0);
        // // display->print("Cursor:  ");
        // display->print(cursor);
        // display->display();

        pageCurrent->loop(); 
        delay(250);
    }
}

void MenuDisplay::pageChange(Menu::Page::Base* pageNew)
{
    if(!pageNew) return;

    pageCurrent = pageNew;
    pageCurrent->create();

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
    //mainDisplay.pageChange(pageTarget);
}

void Menu::Element::PageSwitcher::draw()
{
    mainDisplay.display->println(name.c_str());
}

// void Menu::Page::Navigation::draw()
// {
//     mainDisplay.display->setCursor(0, 0);
//     mainDisplay.display->println(title.c_str());
// }

void Menu::Page::Navigation::create()
{
}

void Menu::Page::Navigation::loop()
{
    mainDisplay.display->clearDisplay();
    mainDisplay.display->setCursor(0, 0);
    mainDisplay.display->println(title.c_str());

    // if (mainDisplay.cursor < contents.size() - 3) 
    // {
    //     if (mainDisplay.cursor < 3) 
    //     {
    //         displayDraw(0, 5);
    //     } 
    //     else 
    //     {
    //         displayDraw(mainDisplay.cursor - 2, mainDisplay.cursor + 3);
    //     }
    // } 
    // else if (mainDisplay.cursor <= contents.size() - 1) 
    // {
    //     displayDraw(contents.size() - 5, contents.size());
    // }

    // for(Menu::Element::Base* elem : contents)
    // {
    //     elem.
    // }

    mainDisplay.display->display();

    // if(buttonSelect)
    // {
    //     int cursor = 2;
    //     contents[cursor]->action();
    // }
}

void Menu::Page::MainMenu::create()
{
    Navigation::create();
    
    //Initialize.
    contents.push_back(new Menu::Element::PageSwitcher("page #1.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #2.", nullptr));
    contents.push_back(new Menu::Element::PageSwitcher("page #3.", nullptr));
}

// Menu::Page::Base::Base()
// {
//     contents.clear();
// }

// Menu::Page::Base::~Base()
// {
//     for(Menu::Element::Base* elem : contents)
//     {
//         delete elem;
//     }

//     contents.clear();
// }