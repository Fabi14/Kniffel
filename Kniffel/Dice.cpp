#include "Dice.h"


namespace
{
	constexpr int diceSize = 40;

	Position operator-(Position pos, int d)
	{
		return { pos.x - d,pos.y - d };
	}
	Position operator+(Position pos, int d)
	{
		return { pos.x + d,pos.y + d };
	}
}

Dice::Dice(const Position& pos) : m_pos{pos}
{

}

void Dice::draw(olc::PixelGameEngine& engine)
{
	drawDice(m_value, m_pos, engine);
}

void Dice::roll()
{
	m_value = getRandomDiceValue();
}

bool Dice::isSelected() const
{
	return m_selected;
}

void Dice::select(bool isSelected)
{
	m_selected = isSelected;
}

BoundingBox Dice::getBoundingBox()
{
	return BoundingBox({m_pos - 0.5 * diceSize }, { m_pos + 0.5 * diceSize });
}

void Dice::drawDice(DiceValue number, Position pos, olc::PixelGameEngine& engine)
{

	constexpr int c_dotSizeRadius = 2;

	engine.FillRect(pos - diceSize / 2, { diceSize, diceSize });

	auto drawOne = [&engine, &pos] {
		engine.FillCircle(pos, c_dotSizeRadius, olc::BLACK);
	};
	auto drawTwo = [&engine, &pos] {
		engine.FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
	};

	auto drawFour = [&engine, &pos] {
		engine.FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{0.2, -0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{-0.2, 0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
	};

	auto drawSix = [&engine, &pos] {
		engine.FillCircle(pos - 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{0.2, -0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{0.2, 0.} *diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos + 0.2 * diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{-0.2, 0.2} *diceSize, c_dotSizeRadius, olc::BLACK);
		engine.FillCircle(pos - olc::vd2d{-0.2, 0.} *diceSize, c_dotSizeRadius, olc::BLACK);
	};

	switch (number)
	{
		using enum DiceValue;
	case one:
	{
		drawOne();
		break;
	}
	case two:
	{
		drawTwo();
		break;
	}
	case three:
	{
		drawOne();
		drawTwo();
		break;
	}
	case four:
	{
		drawFour();
		break;
	}
	case five:
	{
		drawFour();
		drawOne();
		break;
	}
	case six:
	{
		drawSix();
		break;
	}
	}
}

auto Dice::getRandomDiceValue() -> DiceValue
{
	int x = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
	return DiceValue(x);
}
