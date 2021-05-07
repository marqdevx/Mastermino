#include "Mastermino.h"

Mastermino::Mastermino()
{
	//Set all default values
	for (int i = 0; i < ROWS; i++)
	{
		for (int c = 0; c < COLUMNS; c++)
		{
			holder[i].dot[c].color = COLOR_NONE;
			holder[i].dot[c].index = c;
			holder[i].markers[c].color = COLOR_NONE;
		}
	}
}

Mastermino::~Mastermino()
{
}

void Mastermino::start()
{
	//Generate the secretCode
	for (int i = 0; i < COLUMNS; i++)
	{
		masterCode.dot[i].color = COLOR_PINK;
	}
	/*masterCode.dot[0].color = COLOR_PINK;
	masterCode.dot[0].index = 0;
	masterCode.dot[1].color = COLOR_RED;
	masterCode.dot[1].index = 1;
	masterCode.dot[2].color = COLOR_BLUE;
	masterCode.dot[2].index = 2;
	masterCode.dot[3].color = COLOR_ORANGE;
	masterCode.dot[3].index = 3;*/
	_generateMastercode();
}
void Mastermino::newEntry(uint32_t entryColor)
{
	//Allow entry, only if there is a dot free of color
	if (!(guessCount >= COLUMNS))
	{
		holder[turnCount].dot[guessCount].color = entryColor;
		holder[turnCount].dot[guessCount].index = guessCount;
		Serial.print("Color ");
		Serial.print(guessCount);
		Serial.print(" set to: ");
		Serial.println(entryColor);

		guessCount++;
	}
}

void Mastermino::_generateMastercode()
{
	//Generate secret code
	Serial.println("New secret code is: ");

	for (int i = 0; i < COLUMNS; i++)
	{
		int seed = analogRead(0);
		int randomNum = seed % (COLORS_SIZE - 1);
		if (randomNum <= 0)
		{
			i--;
		}
		else
		{
			Serial.println(randomNum);
			masterCode.dot[i].color = randomNum;
			masterCode.dot[i].index = i;
			//Serial.print(masterCode.dot[i].color);
			Serial.print(" , ");
		}
	}
	Serial.println();
}

bool Mastermino::entryAvailable()
{
	if (guessCount < COLUMNS && turnCount < ROWS)
		return true;
	return false;
}

uint8_t Mastermino::checkWin()
{
	int comparator = 0;
	//Save each color count
	for (int i = 0; i < COLUMNS; i++)
	{
		//Serial.println(turnCount);
		if (masterCode.dot[i].color == holder[turnCount].dot[i].color)
		{
			comparator++;
		}
	}
	/*Serial.print("Comparator");
	Serial.println(comparator);*/
	if (comparator >= COLUMNS)
	{
		return PLAYER_WON;
	}
	else if (turnCount == ROWS - 1)
	{
		return PLAYER_LOST;
	}
	return PLAYER_PLAYING;
}

void Mastermino::finishGuess()
{

	//Tesst
	/*holder[turnCount].dot[0].color = COLOR_BLUE;
	holder[turnCount].dot[0].index = 0;
	holder[turnCount].dot[1].color = COLOR_ORANGE;
	holder[turnCount].dot[1].index = 1;
	holder[turnCount].dot[2].color = COLOR_BLUE;
	holder[turnCount].dot[2].index = 2;
	holder[turnCount].dot[3].color = COLOR_PINK;
	holder[turnCount].dot[3].index = 3;	
	guessCount = COLUMNS;*/

	//Only reset values when it is not the last line
	if (turnCount < ROWS && guessCount >= COLUMNS)
	{
		//reset guess count
		guessCount = 0;

		//Set the last holder guessed, and increase turn
		if (turnCount < ROWS)
			turnCount++;
	}
}

void Mastermino::getChecks()
{
	//Set markers on each Holder
	//Check mastercode
	int prevTurn = turnCount - 1;
	int masterCode_colors_count[COLORS_SIZE]; //Save the color with the count of repeated colors
	int guessCode_colors_count[COLORS_SIZE];
	//Block the over check of the values
	bool masterCode_checked[COLUMNS];
	for (int i = 0; i < COLORS_SIZE; i++)
	{
		masterCode_colors_count[i] = 0;
		guessCode_colors_count[i] = 0;
	}

	//Save each color count
	for (int i = 0; i < COLUMNS; i++)
	{
		masterCode_colors_count[masterCode.dot[i].color]++;
		guessCode_colors_count[holder[prevTurn].dot[i].color]++;
	}

	//Print colors count info
	Serial.println("MasterCode info: ");
	for (int c = 0; c < COLORS_SIZE; c++)
	{
		if (masterCode_colors_count[c])
		{
			Serial.print("Color n");
			Serial.print(c);
			Serial.print(" is ");
			Serial.println(masterCode_colors_count[c]);
			Serial.println(" times");
		}
	}
	Serial.println();
	Serial.println("GUESS info");
	for (int c = 0; c < COLORS_SIZE; c++)
	{
		if (guessCode_colors_count[c])
		{
			Serial.print("Color n");
			Serial.print(c);
			Serial.print(" is ");
			Serial.println(guessCode_colors_count[c]);
			Serial.println(" times");
		}
	}
	Serial.println();

	//Now compare the guess with the masterCode to see how correct is the guess

	bool colorCheck[COLUMNS];
	for (int i = 0; i < COLUMNS; i++)
	{
		colorCheck[i] = false;
	}
	// comapre guess and mastercode to see comparisons
	int count = 0;
	for (int i = 0; i < COLUMNS; i++)
	{
		Dots masterColor = masterCode.dot[i];
		if (guessCode_colors_count[masterColor.color])
		{
			if (masterColor.color == holder[prevTurn].dot[i].color)
			{
				Serial.println("COLOR and POS ok");
				holder[prevTurn].markers[count].color = COLOR_RED;
			}
			else
			{
				Serial.println("COLOR ok");
				holder[prevTurn].markers[count].color = COLOR_WHITE;
			}

			count++;
		}
	}
}

Dots::Dots() {}
Dots::~Dots() {}
Holder::Holder()
{
}

Holder::~Holder()
{
}
