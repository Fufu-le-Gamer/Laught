#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class EventManager
{
public:
	EventManager();

	void triggerRandomEvent(class Character& player);

	bool isInverted() const { return m_inverted; }
	bool isFlipped() const { return m_flipped; }

private:
	bool m_inverted = false;
	bool m_flipped = false;

	void EventInvert();
	void EventFlip();

};

