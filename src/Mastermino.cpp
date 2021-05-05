#include "Mastermino.h"

Mastermino::Mastermino()
{
}

Mastermino::~Mastermino()
{
}

void Mastermino::start()
{
	//Generate the secretCode
	for (int i = 0; i < COLUMNS; i++)
	{
		masterCode.dot[i].color = COLOR_YELLOW;
	}
}
void Mastermino::newEntry(uint32_t entryColor)
{
	//Allow entry, only if there is a dot free of color
	if (!(guessCount > COLUMNS))
	{
		holder[turnCount].dot[guessCount].color = entryColor;
		holder[turnCount].dot[guessCount].index = guessCount;

		guessCount++;
	}
}

void Mastermino::finishGuess()
{
	masterCode.dot[0].color = COLOR_PINK;
	masterCode.dot[0].index = 0;
	masterCode.dot[1].color = COLOR_RED;
	masterCode.dot[1].index = 1;
	masterCode.dot[2].color = COLOR_BLUE;
	masterCode.dot[2].index = 2;
	masterCode.dot[3].color = COLOR_ORANGE;
	masterCode.dot[3].index = 3;

	//Tesst
	holder[turnCount].dot[0].color = COLOR_BLUE;
	holder[turnCount].dot[0].index = 0;
	holder[turnCount].dot[1].color = COLOR_ORANGE;
	holder[turnCount].dot[1].index = 1;
	holder[turnCount].dot[2].color = COLOR_PINK;
	holder[turnCount].dot[2].index = 2;
	holder[turnCount].dot[3].color = COLOR_PINK;
	holder[turnCount].dot[3].index = 3;

	guessCount = COLUMNS;

	//Only reset values when it is not the last line
	if (turnCount < ROWS && guessCount >= COLUMNS)
	{
		//reset guess count
		guessCount = 0;

		//Set markers on each Holder
		//Check mastercode

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
			guessCode_colors_count[holder[turnCount].dot[i].color]++;
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
		for (int i = 0; i < COLUMNS; i++)
		{
			Dots masterColor = masterCode.dot[i];
			if (guessCode_colors_count[masterColor.color] && !colorCheck[i])
			{
				if (masterColor.color == holder[turnCount].dot[i].color)
				{
					Serial.println("COLOR and POS ok");
				}
				else
				{
					
				}
				colorCheck[i] = true;
			}
		}

		//Set the last holder guessed, and increase turn
		holder[turnCount].guessed = true;
		turnCount++;
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
