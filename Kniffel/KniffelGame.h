#pragma once
#include "olcPixelGameEngine.h"
#include "Dice.h"
#include <ranges>


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
			auto notSelected = [](const Dice& dice) { return !dice.isSelected(); };
			for (auto& dice : m_arDice | std::views::filter(notSelected))
			{
				dice.roll();
			}
		}

		Clear({ 53,101,77 });
		for (auto& dice : m_arDice)
		{
			dice.draw(*this);
			if (dice.isSelected())
			{
				const auto bb = dice.getBoundingBox();
				DrawRect(bb.leftUpperCorner - olc::vi2d{1, 1}, bb.rightLowerCorner - bb.leftUpperCorner + olc::vi2d{ 1, 1 }, olc::RED);
			}
		}

		const auto mousePos = GetMousePos();
		for (auto& dice : m_arDice)
		{
			const auto bb = dice.getBoundingBox();
			if (bb.leftUpperCorner.x < mousePos.x && bb.rightLowerCorner.x > mousePos.x &&
				bb.leftUpperCorner.y < mousePos.y && bb.rightLowerCorner.y > mousePos.y)
			{
				if (GetMouse(0).bPressed)
				{
					dice.select(!dice.isSelected());
				}
				else if(!dice.isSelected())
				{
					DrawRect(bb.leftUpperCorner - olc::vi2d{1, 1}, bb.rightLowerCorner - bb.leftUpperCorner + olc::vi2d{ 1, 1 }, olc::GREY);
				}
			}
		}


		return true;
	}

private:
	std::array<Dice, 5> m_arDice{Dice{{ 30, 50 }}, Dice{ { 80,50 } }, Dice{ { 130,50 } }, Dice{ { 180,50 } }, Dice{ {230,50} } };

};