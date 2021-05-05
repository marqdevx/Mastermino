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
	COLOR_NONE,
	COLOR_RED,
	COLOR_YELLOW,
	COLOR_ORANGE,
	COLOR_BROWN,
	COLOR_BLUE,
	COLOR_CYAN,
	COLOR_PINK,
	COLORS_SIZE //Know cout of colors
};
enum checkers
{
	CHECK_NOTHING,
	CHECK_CORREC_TPOS,
	CHECK_COLOR_EXISTING

};
enum status
{
	PLAYER_PLAYING,
	PLAYER_WON,
	PLAYER_LOST
};

class Dots
{
private:
	/* data */
public:
	Dots();
	~Dots();

	uint32_t color = COLOR_NONE;
	uint32_t index;
	bool checked = true;
};

class Holder
{
private:
	/* data */
public:
	Holder();
	~Holder();

	Dots dot[COLUMNS];
	bool guessed = false;

	Dots markers[COLUMNS];
	
};

class Mastermino
{

public:
	Mastermino();
	~Mastermino();

	Holder holder[ROWS];
	Holder masterCode;

	void start();

	int turnCount = 0;
	int guessCount = 0;
	void newEntry(uint32_t entryColor);
	void finishGuess();

private:
};

#endif