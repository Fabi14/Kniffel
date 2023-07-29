#include "KniffelGame.h"

void KniffelGame::rollDice()
{
	if (m_rollCount > 0)
	{
		auto notSelected = [](const Dice& dice) { return !dice.isSelected(); };
		for (auto& dice : m_arDice | std::views::filter(notSelected))
		{
			dice.roll();
		}

		m_currentPoints = std::reduce(m_arDice.begin(), m_arDice.end(), 0, [](int sum, const Dice& dice) {return sum + dice.getPoints(); });
	}
	--m_rollCount;

	if (m_rollCount < 0)
	{
		m_rollCount = 3;
		if (m_currentPoints > m_highScore)
		{
			m_highScore = m_currentPoints;
		}
		for (auto& dice : m_arDice)
		{
			dice.select(false);
			dice.clear();
		}
	}
}

void KniffelGame::initRandomNumberGenerator()
{
	const auto now = std::time(nullptr);
	std::srand(now);
}

void KniffelGame::handleMouseInput()
{
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
			else if (!dice.isSelected())
			{
				DrawRect(bb.leftUpperCorner - olc::vi2d{1, 1}, bb.rightLowerCorner - bb.leftUpperCorner + olc::vi2d{ 1, 1 }, olc::GREY);
			}
		}
	}
}

void KniffelGame::drawGame()
{
	Clear({ 53,101,77 });
	{
		drawRollCount();
	}
	for (auto& dice : m_arDice)
	{
		dice.draw(*this);
		if (dice.isSelected())
		{
			const auto bb = dice.getBoundingBox();
			DrawRect(bb.leftUpperCorner - olc::vi2d{1, 1}, bb.rightLowerCorner - bb.leftUpperCorner + olc::vi2d{ 1, 1 }, olc::RED);
		}
	}
	{
		drawScores();
	}
}

void KniffelGame::drawScores()
{
	std::stringstream str;
	str << "Punkte: " << m_currentPoints << "   Highscore: " << m_highScore;
	DrawString({ 20,130 }, str.str());
}

void KniffelGame::drawRollCount()
{
	std::stringstream str;
	str << "Verbleibende Wuerfe: " << m_rollCount;
	DrawString({ 20,10 }, str.str());
}
