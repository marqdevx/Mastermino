#include "Mastermino.h"
Mastermino mastermino;

//Include the tabs
//#include "matrix.h"
#include "input.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("INIT");

  mastermino.start();
  matrix.begin();
  /*
    for (int i = 0; i < 8; i++) {
      while (mastermino.entryAvailable()) {
        mastermino.newEntry(COLOR_PINK);

      }

      mastermino.finishGuess();
      mastermino.getChecks();
      updateMatrix();



      Serial.println();
      Serial.println("____END TURN____");
      Serial.println();



      Serial.print("Win status: ");

      switch (mastermino.checkWin()) {
        case PLAYER_WON:
          Serial.println("Player won");
          while (1);
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
    }*/
  //test();
}
void loop() {
  int status = mastermino.checkWin();
  if (status == PLAYER_PLAYING) {
    encoderUpdate();
  } else  {

    mastermino.finishGuess();
    mastermino.getChecks();

    updateMatrix();

    while (1);
  }
}
