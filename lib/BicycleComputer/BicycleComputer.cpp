#include <BicycleComputer.h>
#include <Pins.h>
#include <BikeTime.h>
#include <Settings.h>
#include <MenuDisplay.h>

void Menu::Element::SpeedMeter::create()
{
    mainDisplay.display->fillRect(int16_t(x), int16_t(y), 72, 24, 0);
    mainDisplay.display->setTextSize(1);
    mainDisplay.display->setCursor(int16_t(x) + 72, int16_t(y));
    mainDisplay.display->print("KM");
    mainDisplay.display->setCursor(int16_t(x) + 72, int16_t(y) + 8);
    mainDisplay.display->print("/H");  
}

void Menu::Element::SpeedMeter::loop(float timeDeltaSeconds)
{
    pollHallSensor();
    measureSpeed();
}

void Menu::Element::SpeedMeter::pollHallSensor()
{
    bool reedSwitchVal = digitalRead(REED_SWITCH_PIN);

        if (reedSwitchVal != reedSwitchValPrev)
    {
        if (reedSwitchVal == HIGH)
        {
            ++count;
        }

        reedSwitchValPrev = reedSwitchVal;
    }
}

void Menu::Element::SpeedMeter::measureSpeed()
{
    time_ms now = millis();
    time_ms deltaTime = now - timeUpdatePrev;

    if (deltaTime >= intervalTime)
    {
        if(count)
        {
            float revolutions = float(count) / float(settings.magnetsNum);
            speed = revolutions * float(settings.tireCirc) / float(deltaTime) * 3.6f;

            if(speed > 9999.0F)
            {
                speed = 9999.0F;
            }

            count = 0;
        }
        else
        {
            speed = 0.f;
        }

        displaySpeed();
        timeUpdatePrev = now;
    }   
}

void Menu::Element::SpeedMeter::action() {}
void Menu::Element::SpeedMeter::draw() {}


void Menu::Element::SpeedMeter::displaySpeed()
{
    mainDisplay.display->fillRect(int16_t(x), int16_t(y), 70, 24, 0);
    mainDisplay.display->setTextSize(3);

    uint8_t decimal_places = 1;

    mainDisplay.display->setCursor(int16_t(x), int16_t(y));
    if (speed < 10.0F)
    {
        mainDisplay.display->print(" ");
    }
    else if (speed < 100.0F)
    {
        decimal_places = 1;
    }
    else if (speed < 1000.0F)
    {
        decimal_places = 0;
        mainDisplay.display->print(" ");
    }

    mainDisplay.display->print(speed, decimal_places);   
}

void Menu::Page::SpeedDist::create()
{
    title = "Speed and Distance";
    speedMeter = new Element::SpeedMeter("Speedometer", 0, 0);
}

void Menu::Page::SpeedDist::destroy()
{
    delete speedMeter;
}

void Menu::Page::SpeedDist::draw()
{

}

void Menu::Page::SpeedDist::loop(float timeDeltaSeconds)
{
    speedMeter->loop(timeDeltaSeconds);
}

