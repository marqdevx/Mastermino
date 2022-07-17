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
	COLOR_GREEN,
	COLOR_PURPLE,
	COLOR_CYAN,
	COLOR_PINK,
	COLOR_WHITE,
	COLORS_SIZE //Know count of colors
};

enum LED:uint32_t{
	LED_NONE = 0x0,
	LED_RED = 0xF920,
	LED_YELLOW = 0xFFE0,
	LED_ORANGE = 0xFBA0,
	LED_GREEN = 0x37E0,
	LED_PURPLE = 0x029F,
	LED_CYAN = 0x07FF,
	LED_PINK = 0xF817,
	LED_WHITE = 0xFFFF
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
	bool entryAvailable();
	void finishGuess();

	uint8_t checkWin();

	void getChecks();

private:
	void _generateMastercode();
	
};

#endif