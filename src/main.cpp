#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <SPI.h>

#pragma region Hardware
MCUFRIEND_kbv tft; //ILI9325 ADAFRUIT BASED TFT

uint_fast16_t tft_id = 0x9325; //TFT BEGIN VENDOR ID

uint_fast8_t SD_CS = 10; //PIN PORT FOR SD_CARD

#pragma endregion
#pragma region Software
File root; //Root for file system
char namebuf[32] = "/"; //Root path
bool sd_ini; //Init variable for SD_CARD
#pragma endregion

static int configure_screen(){
  tft.reset();
  tft.begin(tft_id);
  tft.setRotation(1);
}

static int start_loader(){
  tft.fillScreen(TFT_WHITE);
  sd_ini = SD.begin(SD_CS);
  #pragma region SD_CARD_ERROR
  if(!sd_ini){
    tft.setCursor(94, 111);
    tft.setTextSize(3);
    tft.print("SD ERROR!");
    while(1);
  }
  #pragma endregion
}

void setup() {
  configure_screen();
  start_loader();
}

void loop() {
  
}