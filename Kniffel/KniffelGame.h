#pragma once
#include "olcPixelGameEngine.h"

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
		drawDice(1);

		return true;
	}

private:
	void drawDice(short number);
};