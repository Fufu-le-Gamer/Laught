#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class EventManager
{
public:
	EventManager();

	void update();

	void triggerRandomEvent(class Character& player);

	bool isInverted() const { return m_inverted; }
	bool isFlipped() const { return m_flipped; }
	bool isScreamer() const { return m_screamer; }

private:
	bool m_inverted = false;
	bool m_flipped = false;
	bool m_screamer = false;

	sf::Clock m_eventClock;

	void EventInvert();
	void EventFlip();
	void EventScreamer();

};

