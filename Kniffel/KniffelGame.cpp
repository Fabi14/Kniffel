#include "KniffelGame.h"



namespace
{
	Position operator-(Position pos, int d)
	{
		return { pos.x - d,pos.y - d };
	}
}


void KniffelGame::drawDice(DiceValue number, Position pos)
{
	constexpr int diceSize = 40;
	constexpr int c_dotSizeRadius = 2;

	FillRect(pos - diceSize/2, { diceSize, diceSize });
	FillCircle(pos, c_dotSizeRadius, olc::BLACK);
}
