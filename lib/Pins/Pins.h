#pragma once

#include <SPI.h>


#define SPI0_RX 0
#define SPI0_CSN 1
#define SPI0_SCK 2
#define SPI0_TX 3

#define SPI1_RX 12
#define SPI1_CSN 13
#define SPI1_SCK 14
#define SPI1_TX 15

#define DISP_DC 20
#define DISP_CS SPI1_CSN 
#define DISP_RST 21

#define GREENBTNPIN 8
#define REDBTNPIN 9
#define UPBTNPIN 10
#define DOWNBTNPIN 11

#define REED_SWITCH_PIN 22

// //#define BLE_PIN 4

// #define SDCS 22
// #define SD_LED 6

// #define DISP_DC 20
// #define DISP_CS 17 
// #define DISP_RST 21

namespace Pins
{
    void setup();
}