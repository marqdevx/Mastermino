#include "Adafruit_NeoMatrix.h"
Adafruit_NeoMatrix matrix(8, 8, 6, NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_COLUMNS, (NEO_GRB + NEO_KHZ800));

void setpixel(int x, int y, uint32_t color) {
  switch (color) {
    case COLOR_RED:
      matrix.drawPixel(x, y, LED_RED);
      break;
    case COLOR_YELLOW:
      matrix.drawPixel(x, y, LED_YELLOW);
      break;
    case COLOR_ORANGE:
      matrix.drawPixel(x, y, LED_ORANGE);
      break;
    case COLOR_GREEN:
      matrix.drawPixel(x, y, LED_GREEN);
      break;
    case COLOR_PURPLE:
      matrix.drawPixel(x, y, LED_PURPLE);
      break;
    case COLOR_CYAN:
      matrix.drawPixel(x, y, LED_CYAN);
      break;
    case COLOR_PINK:
      matrix.drawPixel(x, y, LED_PINK);
      break;
    case COLOR_WHITE:
      matrix.drawPixel(x, y, LED_WHITE);
      break;
    default:
      matrix.drawPixel(x, y, LED_NONE);
      break;
  }
  matrix.show();
}

void test() {
  matrix.begin();
  matrix.setBrightness(50);
  matrix.drawPixel(1, 7,  LED(1));
  matrix.drawPixel(2, 7,  LED_PINK);
  matrix.drawPixel(3, 7,  LED_YELLOW);
  matrix.drawPixel(4, 7,  LED_ORANGE);
  matrix.drawPixel(5, 7,  LED_PURPLE);
  matrix.drawPixel(0, 1,  LED_CYAN);
  matrix.drawPixel(5, 5,  LED_GREEN);

  matrix.show();
}

void updateMatrix() {
  matrix.clear();
  matrix.setBrightness(50);
  for (int i = 0; i < ROWS; i++) {
    for (int c = 0; c < COLUMNS; c++) {
      uint32_t color = mastermino.holder[i].dot[c].color;
      uint32_t newColor = 0;
      setpixel(i, c, color);

    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int c = 0; c < COLUMNS; c++) {
      uint32_t color = mastermino.holder[i].markers[c].color;
      uint32_t newColor = 0;
      setpixel(i, c + 4, color);
    }
  }
}
