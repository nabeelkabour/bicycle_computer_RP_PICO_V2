#include <Arduino.h>
#include "Pins.h"


void Pins::setup()
{
    SPI.setRX(SPI0_RX);
    SPI.setCS(SPI0_CSN);
    SPI.setSCK(SPI0_SCK);
    SPI.setTX(SPI0_TX);
    SPI.begin(true);

    SPI1.setRX(SPI1_RX);
    SPI1.setCS(SPI1_CSN);
    SPI1.setSCK(SPI1_SCK);
    SPI1.setTX(SPI1_TX);
    SPI1.begin(true);

    pinMode(REED_SWITCH_PIN, INPUT);

    pinMode(GREENBTNPIN, INPUT);
    pinMode(REDBTNPIN, INPUT);
    pinMode(UPBTNPIN, INPUT);
    pinMode(DOWNBTNPIN, INPUT);

    //pinMode(SD_LED, OUTPUT);
    //pinMode(SDCS, OUTPUT);
   // pinMode(BLE_PIN, OUTPUT);
}