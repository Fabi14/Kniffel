#include "KniffelGame.h"

void KniffelGame::drawDice(short number)
{
	constexpr int c_dotSizeRadius = 2;
	FillRect({ 50,50 }, { 40,40 });
	FillCircle({ 70,70 }, c_dotSizeRadius, olc::BLACK);

}
