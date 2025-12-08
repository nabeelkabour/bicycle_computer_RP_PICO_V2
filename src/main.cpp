#include <Arduino.h>
#include <Pins.h>
#include <MenuDisplay.h>

void setup() 
{
    Pins::setup();
    mainDisplay.setup();
}

void loop() 
{
    mainDisplay.loop();
}