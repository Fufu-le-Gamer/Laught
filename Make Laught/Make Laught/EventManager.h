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
	bool isPandaria() const { return m_pandaria; }
	bool isFart() const { return m_fart; }
	bool isMacron() const { return m_macron; }
	bool isEventRunning() const { return m_screamer || m_pandaria || m_fart || m_macron; }

private:
	bool m_inverted = false;
	bool m_flipped = false;
	bool m_screamer = false;
	bool m_pandaria = false;
	bool m_fart = false;
	bool m_macron = false;

	sf::Clock m_eventClock;

	void EventInvert();
	void EventFlip();
	void EventScreamer();
	void EventPandaria();
	void EventFart();
	void EventMacron();

};

