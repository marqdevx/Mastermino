#include "Mastermino.h"

Mastermino::Mastermino(int numColumns, int numEntrys)
{
	_numColums = numColumns;
	_numEntrys = numEntrys;
}

void Mastermino::start()
{
	//Generate new secret code
	for (int i = 0; i < _numEntrys; i++)
	{
		int seed = analogRead(0);
		int randomNum = seed % _numEntrys;
		//Serial.println(randomNum);
		_masterCode[i * 4] = colors(randomNum);
		Serial.print(_masterCode[i]);
		Serial.print(" , ");
	}

	
}

void Mastermino::entryNewGuess(uint32_t newGuess)
{
	if (_guessCount < _numEntrys)
	{
		_guess[_guessCount] = newGuess;

		Serial.print("RECORDED NEW ENTRY : ");
		Serial.println(_guess[_guessCount]);

		_guessCount++;
	}
}

void Mastermino::entryGoBack()
{
	_guess[_guessCount] = 0;
	_guessCount--;
}

bool Mastermino::entryAvailable()
{
	if (_guessCount == _numEntrys)
	{
		return false;
	}
	return true;
}
void Mastermino::finishTurn()
{
	for (int x = 0; x < COLUMNS; x++)
	{
		_historyGuesses[_turnCount][x] = _guess[x];
		_guess[x] = 0;
		
		Serial.print("History :");
		Serial.println(_historyGuesses[_turnCount][x]);
	}

	Serial.println("History: ");
	for (int y = 0; y <= _turnCount; y++)
	{
		Serial.print("R ");
		Serial.print(y);
		Serial.print(" : ");
		for (int x = 0; x < COLUMNS; x++)
		{
			Serial.print(_historyGuesses[y][x]);
			Serial.print(" ");
			
		}
		Serial.println();
	}
	_guessCount = 0;
	_turnCount++;
}

uint32_t Mastermino::getGuess(int entryIndex)
{
	return _guess[entryIndex];
}

uint32_t Mastermino::getHistory(int rowIndex, int rowColumn)
{
	//return _historyGuesses[rowIndex * rowColumn * 4];
}

uint8_t Mastermino::status(){
	if(_turnCount == ROWS){
		return PLAYER_LOST;
	}
	return PLAYER_PLAYING;
}