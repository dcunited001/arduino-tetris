#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Psx.h>

#define PIN_SCE   7  // LCD CS  .... Pin 3
#define PIN_RESET 6  // LCD RST .... Pin 1
#define PIN_DC    5  // LCD Dat/Com. Pin 5
#define PIN_SDIN  11  // LCD SPIDat . Pin 6
#define PIN_SCLK  13  // LCD SPIClk . Pin 4

#define PIN_BACKLIGHT 9 // LCD Backlight Pin 8
#define BACKLIGHT_LEVEL 127

#define PCD8544_CMD      LOW
#define PCD8544_DATA     HIGH
//TODO: find out why Hardware SPI isn't working
// static Adafruit_PCD8544 lcd = Adafruit_PCD8544(PIN_DC, PIN_SCE, PIN_RESET);
static Adafruit_PCD8544 lcd = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

#define LCD_WIDTH      84
#define LCD_HEIGHT     48
#define LCD_LINE_HEIGHT 8
#define LCD_LINE_WIDTH 5
#define LCD_CMD   0
#define LCD_CONTRAST 60

static Psx psx;
static unsigned int psx_data = 0;
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

static unsigned int gameState = 0;
static bool titleDrawn = false;

void initBacklight(void) {
    pinMode(PIN_BACKLIGHT, OUTPUT);
    analogWrite(PIN_BACKLIGHT, BACKLIGHT_LEVEL);
}

void initLCD(void) {
    lcd.begin();
    lcd.setContrast(LCD_CONTRAST);
    lcd.clearDisplay();

    initBacklight();
}

void initPSX(void) {
    psx.setupPins(PIN_PSX_DATA, PIN_PSX_CMD, PIN_PSX_ATT, PIN_PSX_CLK, PSX_DELAY);
}

void initGame(void) {
    gameState = 0;
}

void drawTitleScreen(void) {
    lcd.clearDisplay();
    lcd.setCursor(0,0);
    lcd.println("Arduino Tetris");
    lcd.println("*Press Start*");
    lcd.display();
//TODO: make press start flash
//    delay(800);
//    lcd.println("*Press Start*");
//    lcd.display();
//    delay(800);
}

void onTitleScreen(void) {
    if (!titleDrawn) {
        drawTitleScreen();
        titleDrawn = true;
    }
    if (psx_data & psxStrt) {
        gameState = STATE_START;
    }
}

void onStartGame(void) {
    lcd.clearDisplay();
    //transition state
    // draw game board
    // initialize game
    gameState = STATE_PLAY;
}

void onPlayGame(void) {
    lcd.setCursor(0,0);
    lcd.println("Playing Tetris");
    lcd.display();
    gameState = STATE_END;
    delay(1000);
}

void onEndGame(void) {
    lcd.clearDisplay();
    gameState = STATE_TITLE;
    titleDrawn = false;
}

void setup(void) {
    initLCD();
    initPSX();
    initGame();
}

void loop(void) {
    psx_data = psx.read();
    switch(gameState) {
        case STATE_TITLE: onTitleScreen();
        case STATE_START: onStartGame();
        case STATE_PLAY: onPlayGame();
        case STATE_END: onEndGame();
    }
    delay(10);
}
