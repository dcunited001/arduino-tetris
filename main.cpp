#include <Arduino.h>
#include <PCD8544.h>
#include <Psx.h>

static PCD8544 lcd;
#define PIN_SCE   7  // LCD CS  .... Pin 3
#define PIN_RESET 6  // LCD RST .... Pin 1
#define PIN_DC    5  // LCD Dat/Com. Pin 5
#define PIN_SDIN  11  // LCD SPIDat . Pin 6
#define PIN_SCLK  13  // LCD SPIClk . Pin 4

#define PIN_BACKLIGHT 9 // LCD Backlight Pin 8
#define BACKLIGHT_LEVEL 127

#define PCD8544_CMD      LOW
#define PCD8544_DATA     HIGH

#define LCD_WIDTH      84
#define LCD_HEIGHT     48
#define LCD_LINE_HEIGHT 8
#define LCD_LINE_WIDTH 5
#define LCD_CMD   0

static Psx psx;
static unsigned int psx_data;
#define PIN_PSX_DATA 8
#define PIN_PSX_CMD 9
#define PIN_PSX_ATT 11
#define PIN_PSX_CLK 10
#define PSX_DELAY 10 // statechange delay in ms

//game states
#define STATE_TITLE 0
#define STATE_START 1
#define STATE_PLAY 2
#define STATE_END 3

void initBacklight(void) {
    pinMode(PIN_BACKLIGHT, OUTPUT);
    analogWrite(PIN_BACKLIGHT, BACKLIGHT_LEVEL);
}

void initLCD(void) {
    lcd = PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_RESET, PIN_SCE);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    initBacklight();
}

void initPSX(void) {
    psx.setupPins(PIN_PSX_DATA, PIN_PSX_CMD, PIN_PSX_ATT, PIN_PSX_CLK, PSX_DELAY);
}

void onTitleScreen(void) {


}

void onStartGame(void) {

}

void onPlayGame(void) {

}

void onEndGame(void) {

}

void setup(void) {
    initLCD();
    initPSX();
}

void loop(void) {
    psx_data = psx.read();
}
