#pragma once
#include "olcPixelGameEngine.h"

using Position = olc::vi2d;

struct BoundingBox
{
	Position leftUpperCorner{};
	Position rightLowerCorner{};
};


class Dice
{
public:
	Dice(const Position& pos);

	void draw(olc::PixelGameEngine& engine);
	void roll();
	bool isSelected() const;
	void select(bool isSelected = true);
	void clear()
	{
		m_clear = true;
	}

	int getPoints() const
	{
		if (m_clear)
			return 0;
		return static_cast<int>(m_value);
	}
	BoundingBox getBoundingBox();
	

	enum class DiceValue
	{
		one = 1,
		two,
		three,
		four,
		five,
		six
	};
private:

	void drawDice(DiceValue number, Position pos, olc::PixelGameEngine& engine);
	static DiceValue getRandomDiceValue();

	Position m_pos{};
	DiceValue m_value{ getRandomDiceValue()};
	bool m_selected{ false };
	bool m_clear{ true };
};

