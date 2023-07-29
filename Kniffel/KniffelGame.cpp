#include "KniffelGame.h"
#include <algorithm>
#include <ranges>

namespace {
	int calcPoints(KniffelGame::AllDice& dice)
	{
		return std::reduce(dice.begin(), dice.end(), 0, [](int sum, const Dice& dice) {return sum + dice.getPoints(); });
	}
}


void KniffelGame::rollAllNotSelectedDice()
{
	auto notSelected = [](const Dice& dice) { return !dice.isSelected(); };
	for (auto& dice : m_arDice | std::views::filter(notSelected))
	{
		dice.roll();
	}
}

void KniffelGame::updatePoints()
{
	m_points.currentPoints = calcPoints(m_arDice);
}


void KniffelGame::rollDice()
{
	if (m_rollCount > 0)
	{
		rollAllNotSelectedDice();
		updatePoints();
	}
	--m_rollCount;
	if (m_rollCount < 0)
	{
		startNewRound();
	}
}

void KniffelGame::startNewRound()
{
	m_rollCount = 3;
	updateHighscore();
	resetAllDice();
}

void KniffelGame::resetAllDice()
{
	std::ranges::for_each(m_arDice, [this](auto& dice) { resetDice(dice); });
}

void KniffelGame::resetDice(Dice& dice)
{
	dice.select(false);
	dice.clear();
}

void KniffelGame::updateHighscore()
{
	if (m_points.currentPoints > m_points.highScore)
	{
		m_points.highScore = m_points.currentPoints;
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
		selectOrHighlight(dice, mousePos);
	}
}

void KniffelGame::selectOrHighlight(Dice& dice, const olc::vi2d& mousePos)
{
	const auto bb = dice.getBoundingBox();
	bool isMouseOverDice = bb.isInside(mousePos);
	if (isMouseOverDice)
	{
		if (GetMouse(0).bPressed)
		{
			dice.select(!dice.isSelected());
		}
		else if (!dice.isSelected())
		{
			drawHighlight(dice);
		}
	}
}

void KniffelGame::drawGame()
{
	Clear({ 53,101,77 });
	drawRollCount();
	std::ranges::for_each(m_arDice, [this](auto& dice) { draw(dice); });
	drawScores();
}

void KniffelGame::draw(Dice& dice)
{
	dice.draw(*this);
	if (dice.isSelected())
	{
		drawSelection(dice);
	}
}

void KniffelGame::drawHighlight(Dice& dice)
{
	drawFrame(dice,olc::GREY);
}

void KniffelGame::drawSelection(Dice& dice)
{
	drawFrame(dice, olc::RED);
}

void KniffelGame::drawFrame(Dice& dice, olc::Pixel color)
{
	const auto bb = dice.getBoundingBox();
	DrawRect(bb.leftUpperCorner - olc::vi2d{1, 1}, bb.rightLowerCorner - bb.leftUpperCorner + olc::vi2d{ 1, 1 }, color);
}

void KniffelGame::drawScores()
{
	std::stringstream str;
	str << "Punkte: " << m_points.currentPoints << "   Highscore: " << m_points.highScore;
	DrawString({ 20,130 }, str.str());
}

void KniffelGame::drawRollCount()
{
	std::stringstream str;
	str << "Verbleibende Wuerfe: " << m_rollCount;
	DrawString({ 20,10 }, str.str());
}
