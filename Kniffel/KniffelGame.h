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
		if (GetKey(olc::SPACE).bPressed)
		{
			rollDice();
		}
		drawGame();
		DrawString({ 20,230 }, "-- Leertaste zum Wuerfeln --");

		handleMouseInput();

		return true;
	}

	using AllDice = std::array<Dice, 5>;
private:
	void handleMouseInput();

	void selectOrHighlight(Dice& dice, const olc::vi2d& mousePos);

	void rollDice();
	void rollAllNotSelectedDice();

	void startNewRound();

	void resetAllDice();

	void resetDice(Dice& dice);

	void updatePoints();
	void updateHighscore();

	void drawGame();
	void draw(Dice& dice);
	void drawHighlight(Dice& dice);
	void drawSelection(Dice& dice);
	void drawFrame(Dice& dice, olc::Pixel color);
	void drawScores();
	void drawRollCount();

	void initRandomNumberGenerator();

	
	AllDice m_arDice{Dice{{ 30, 50 }}, Dice{ { 80,50 } }, Dice{ { 130,50 } }, Dice{ { 180,50 } }, Dice{ {230,50} } };
	int m_rollCount{ 3 };

	struct Points
	{
		int currentPoints{ 0 };
		int highScore{ 0 };
	};
	Points m_points;
};