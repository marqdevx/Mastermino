#ifndef Mastermino_h_
#define Mastermino_h_

#include "Arduino.h"

#ifndef ROWS
#define ROWS 8
#endif

#ifndef COLUMNS
#define COLUMNS 4
#endif

enum colors
{
	COLOR_RED,
	COLOR_YELLOW,
	COLOR_ORANGE,
	COLOR_BROWN,
	COLOR_BLUE,
	COLOR_CYAN,
	COLOR_PINK,
	COLORS_SIZE	//Know cout of colors
};
enum checkers
{
	CHECK_CORRECTPOS,
	CHECK_COLOR_EXISTING,
	CHECK_NOTHING
};
enum status{
	PLAYER_PLAYING,
	PLAYER_WON,
	PLAYER_LOST

};
class Mastermino
{

public:
	Mastermino(int numColumns, int numEntrys);

	void start();
	void finishTurn();

	bool entryAvailable(); //Return true if the user can entry more colors
	void entryNewGuess(uint32_t newGuess);
	void entryNewGuess(int guessIndex, uint32_t newGuess);
	void entryGoBack();

	bool checkGuess();

	uint32_t *getResult();
	uint8_t getResult(int indexColumn);
	uint8_t getResult(int rowIndex, int columnIndex);

	uint32_t *getGuess();
	uint32_t getGuess(int rowInentryIndex);

	uint32_t getHistory(int rowIndex, int rowColumn);

	uint8_t getWinner();

	uint8_t status();

private:
	int _numColums;
	int _numEntrys;
	uint32_t _masterCode[COLUMNS];	 // Resized on init
	uint32_t _historyGuesses[ROWS][COLUMNS]; // Resized on init
	uint32_t _guess[COLUMNS];
	int _guessCount = 0;
	int _turnCount = 0;

	int _maxTurns;
	int _turn = 0;

	void _generateSecretCode();
};
#endif