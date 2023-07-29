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
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};