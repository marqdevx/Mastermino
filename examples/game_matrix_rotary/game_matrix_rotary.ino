#include "Mastermino.h"
Mastermino mastermino;

//Include the tabs
//#include "matrix.h"
#include "input.h"

#include "bitmaps.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  Serial.println("INIT");
  matrix.begin();
  matrix.clear();
  matrix.show();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0, 0, logo, 128, 64 , 1);
  display.display();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);
  delay(3500);
  display.clearDisplay();
  display.setCursor(0, 15);
  display.print("Press the knob to     start");
  display.display();
  //while(1);
  while (digitalRead(7))delay(100);
  display.clearDisplay();
  display.setCursor(0, 15);
  display.println("Rotate the knob to");
  display.println("select a color");
  display.display();

  blinkMatrix(COLOR_CYAN);
  mastermino.start();

  //Custom code
  mastermino.masterCode.dot[0].color = COLOR_RED;
  mastermino.masterCode.dot[1].color = COLOR_YELLOW;
  mastermino.masterCode.dot[2].color = COLOR_PINK;
  mastermino.masterCode.dot[3].color = COLOR_CYAN;
  display.clearDisplay();
  display.setCursor(0, 18);
  display.print("Playing");
  display.display();
}

void loop() {
  int status = mastermino.checkWin();
  if (status == PLAYER_PLAYING) {
    encoderUpdate();
  } else  {
    mastermino.finishGuess();
    mastermino.getChecks();

    updateMatrix();

    if (status == PLAYER_LOST) {
      blinkMatrix(COLOR_RED);
      display.clearDisplay();
      display.setCursor(0, 18);
      display.println("YOU LOST!");
      display.display();
    } else {
      blinkMatrix(COLOR_GREEN);
      display.clearDisplay();
      display.setCursor(0, 18);
      display.print("The code is:");
      display.println("0 8 5 6 8");
      display.display();
    }

    delay(1500);
    display.println();
    display.print("Press to RESTART");
    display.display();
    while (digitalRead(7));
    //Restart the game
    mastermino = Mastermino();
    setup();
  }
}
