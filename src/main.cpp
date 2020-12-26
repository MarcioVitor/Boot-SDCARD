/*
  Arduino MCUFRIEND_kbv bootloader sd_card
  created on Dec 2020
  by Marcio Vitor
  GPL-3.0 License
*/
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <SPI.h>

#pragma region Hardware
MCUFRIEND_kbv tft; //ILI9325 ADAFRUIT BASED TFT

uint_fast16_t tft_id = 0x9325; //TFT BEGIN VENDOR ID

const uint_fast8_t SD_CS = 10; //PIN PORT FOR SD_CARD

#pragma endregion
#pragma region Software
File root; //Root for file system
char namebuf[32] = "/"; //Root path
int pathlen; //Path Length for file system
bool sd_ini; //Init variable for SD_CARD
#define BMPIMAGEOFFSET 54 //Image offset
#define BUFFPIXEL 20 //GPU Buffer
#define PALETTEDEPTH 0 
#pragma endregion
#pragma region ReadInteger
uint16_t read16(File& f) {
    uint16_t result;         // read little-endian
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}
uint32_t read32(File& f) {
    uint32_t result;
    f.read((uint8_t*)&result, sizeof(result));
    return result;
}
#pragma endregion

static int configure_screen(){
  //BEGIN GPU FROM TFT SCREEN
  tft.reset();
  tft.begin(tft_id);
  tft.setRotation(1);
}

static int start_loader(){
  //START OPERATING SYSTEM
  tft.fillScreen(TFT_WHITE);
  sd_ini = SD.begin(SD_CS);
  #pragma region SD_CARD_ERROR
  if(!sd_ini){
    tft.setCursor(94, 111);
    tft.setTextSize(3);
    tft.setTextColor(TFT_BLACK);
    tft.print("SD ERROR!");
    while(1);
  }
  #pragma endregion
  //BEGIN SD CARD FS WHEN SD_INI RETURNS A VALID SD_CARD
  if(sd_ini){
    root = SD.open(namebuf);
    pathlen = strlen(namebuf);
  }
}

void setup() {
  configure_screen();
  start_loader();
}

void loop() {
  
}