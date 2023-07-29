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
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear({ 53,101,77 });
		drawDice(DiceValue::one, { 70,70 });
		drawDice(DiceValue::two, { 120,70 });

		return true;
	}

private:
	enum class DiceValue
	{
		one,
		two,
		three,
		four,
		five,
		six
	};


	void drawDice(DiceValue number, Position pos);
};