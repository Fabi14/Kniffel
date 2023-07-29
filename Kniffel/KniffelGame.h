#pragma once
#include "olcPixelGameEngine.h"
#include "Dice.h"
#include <ranges>
#include <numeric>


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
		initRandomNumberGenerator();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::SPACE).bPressed && m_rollCount >= 0)
		{
			rollDice();
		}
		drawGame();

		handleMouseInput();

		return true;
	}


private:
	void handleMouseInput();
	void rollDice();

	void drawGame();
	void drawScores();
	void drawRollCount();

	void initRandomNumberGenerator();

	std::array<Dice, 5> m_arDice{Dice{{ 30, 50 }}, Dice{ { 80,50 } }, Dice{ { 130,50 } }, Dice{ { 180,50 } }, Dice{ {230,50} } };
	int m_rollCount{ 3 };

	int m_currentPoints{ 0 };
	int m_highScore{ 0 };
};