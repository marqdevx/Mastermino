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
		guessCount++;
	}
}

void Mastermino::finishGuess()
{
	masterCode.dot[0].color = COLOR_YELLOW;
	masterCode.dot[1].color = COLOR_BLUE;
	masterCode.dot[2].color = COLOR_PINK;
	masterCode.dot[3].color = COLOR_YELLOW;
	guessCount = COLUMNS;

	//Only reset values when it is not the last line
	if (turnCount < ROWS && guessCount >= COLUMNS)
	{
		//reset guess count
		guessCount = 0;

		//Set markers on each Holder
		//Check mastercode
		int masterCode_differentColors = 1; // 1 cause allways there is atleast 1 color in the code
		int masterCode_repeatedColors = 0;
		//Block the over check of the values
		bool masterCode_checked[COLUMNS];
		for (int i = 0; i < COLUMNS; i++)
		{
			masterCode_checked[i] = false;
		}

		//Compare each Dot with each other to check the repeated colors
		for (int i = 0; i < COLUMNS; i++)
		{
			if (!masterCode_checked[i])
			{

				for (int c = 0; c < COLUMNS; c++)
				{
					if (!masterCode_checked[c])
					{

						if (masterCode.dot[i].color != masterCode.dot[c].color)
						{

							masterCode_differentColors++;
							
						}
						else if(masterCode.dot[i].color == masterCode.dot[c].color) 
						{
							Serial.print("Index: ");
							Serial.print(i);
							Serial.println(" ");
							Serial.println("color reepated: ");
							Serial.println(masterCode.dot[i].color);
							masterCode_repeatedColors++;
						}
						
					}
					masterCode_checked[i] = true;
				}
			}
		}

		Serial.print("Different colors in the code: ");
		Serial.println(masterCode_differentColors);
		Serial.print("Repeated colors in the code: ");
		Serial.println(masterCode_repeatedColors);

		// Clear again the checked colors
		for (int i = 0; i < COLUMNS; i++)
		{
			masterCode_checked[i] = false;
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
