#pragma once
#include "olcPixelGameEngine.h"

using Position = olc::vi2d;

class KniffelGame : public olc::PixelGameEngine
{
public:
	KniffelGame()
	{
		// Name your application
		sAppName = "Kniffel";
	}

public:
	bool OnUserCreate() override
	{
		const auto now = std::time(nullptr);
		std::srand(now);

		Clear({ 53,101,77 });
		drawDice(DiceValue::one, { 30,50 });
		drawDice(DiceValue::two, { 80,50 });
		drawDice(DiceValue::three, { 130,50 });
		drawDice(DiceValue::four, { 180,50 });
		drawDice(DiceValue::five, { 230,50 });

		drawDice(DiceValue::six, { 80,100 });
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::SPACE).bPressed)
		{
			Clear({ 53,101,77 });
			drawDice(getRandomDiceValue(), { 30,50 });
			drawDice(getRandomDiceValue(), { 80,50 });
			drawDice(getRandomDiceValue(), { 130,50 });
			drawDice(getRandomDiceValue(), { 180,50 });
			drawDice(getRandomDiceValue(), { 230,50 });

		}
		return true;
	}

private:
	enum class DiceValue
	{
		one=1,
		two,
		three,
		four,
		five,
		six
	};


	void drawDice(DiceValue number, Position pos);
	DiceValue getRandomDiceValue();
};