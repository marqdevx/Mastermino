#include "Mastermino.h"
Mastermino mastermino;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("INIT");

  mastermino.start();
  for (int i = 0; i < 8; i++) {
    while (mastermino.entryAvailable()) {
      mastermino.newEntry(COLOR_PINK);
    }
    mastermino.finishGuess();
    Serial.print("Win status: ");

    switch (mastermino.checkWin()) {
      case PLAYER_WON:
        Serial.println("Player won");
        break;
      case PLAYER_LOST:
        Serial.println("Try again");
        break;
      case PLAYER_PLAYING:
        Serial.println("Continue playing");
        break;
      default:
        break;
    }
    Serial.println();
    Serial.println("____END TURN____");
    Serial.println();
  }

}
void loop() {}
