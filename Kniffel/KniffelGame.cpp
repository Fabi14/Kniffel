#include "KniffelGame.h"



namespace
{
	Position operator-(Position pos, int d)
	{
		return { pos.x - d,pos.y - d };
	}
	Position operator+(Position pos, int d)
	{
		return { pos.x + d,pos.y + d };
	}
}


void KniffelGame::drawDice(DiceValue number, Position pos)
{
	constexpr int diceSize = 40;
	constexpr int c_dotSizeRadius = 2;

	FillRect(pos - diceSize / 2, { diceSize, diceSize });

	auto drawOne = [this,&pos] {
		FillCircle(pos, c_dotSizeRadius, olc::BLACK);
	};
	auto drawTwo = [this, &pos] {
		FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
	};

	auto drawFour = [this, &pos] {
		FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{0.2, -0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{-0.2, 0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
	};

	auto drawSix = [this, &pos] {
		FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{0.2, -0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{0.2, 0.} *diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{-0.2, 0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		FillCircle(pos - olc::vd2d{-0.2, 0.} *diceSize, c_dotSizeRadius, olc::BLACK);
	};

	switch (number)
	{
		using enum DiceValue;
		case one : 
		{
			drawOne();
			break;
		}
		case two:
		{
			drawTwo();
			break;
		}
		case three:
		{
			drawOne();
			drawTwo();
			break;
		}
		case four:
		{
			drawFour();
			break;
		}
		case five:
		{
			drawFour();
			drawOne();
			break;
		}
		case six:
		{
			drawSix();
			break;
		}
	}
}

auto KniffelGame::getRandomDiceValue() -> DiceValue
{
	int x = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
	return DiceValue(x);
}
