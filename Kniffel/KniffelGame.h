#pragma once
#include "olcPixelGameEngine.h"
#include "Dice.h"



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

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::SPACE).bPressed)
		{
			for (auto& dice : m_arDice)
			{
				dice.roll();
			}
		}

		Clear({ 53,101,77 });
		for (auto& dice : m_arDice)
		{
			dice.draw(*this);
		}


		return true;
	}

private:
	std::array<Dice, 5> m_arDice{Dice{{ 30, 50 }}, Dice{ { 80,50 } }, Dice{ { 130,50 } }, Dice{ { 180,50 } }, Dice{ {230,50} } };

};