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
		drawDice(DiceValue::one, { 30,50 });
		drawDice(DiceValue::two, { 80,50 });
		drawDice(DiceValue::three, { 130,50 });
		drawDice(DiceValue::four, { 180,50 });
		drawDice(DiceValue::five, { 230,50 });

		drawDice(DiceValue::six, { 80,100 });
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