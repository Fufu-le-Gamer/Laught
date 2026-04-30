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
	bool isInverted()  const { return m_inverted; }
	bool isFlipped()   const { return m_flipped; }
	bool isScreamer()  const { return m_screamer; }
	bool isPandaria()  const { return m_pandaria; }
	bool isFart()      const { return m_fart; }
	bool isMacron()    const { return m_macron; }
	bool isDuck()      const { return m_duck; }
	bool isCharles()   const { return m_charles; }
	bool isCat()	   const { return m_cat; }
	bool isInternal()  const { return m_internal; }
	bool isEventRunning() const { return m_screamer || m_pandaria || m_fart || m_macron || m_duck || m_charles || m_cat || m_internal; }

private:
	bool m_inverted = false;
	bool m_flipped = false;
	bool m_screamer = false;
	bool m_pandaria = false;
	bool m_fart = false;
	bool m_macron = false;
	bool m_duck = false;
	bool m_charles = false;
	bool m_cat = false;
	bool m_internal = false;
	sf::Clock m_eventClock;
	void EventInternal();
	void EventInvert();
	void EventFlip();
	void EventScreamer();
	void EventPandaria();
	void EventFart();
	void EventMacron();
	void EventDuck();
	void EventCharles();
	void EventCat();
};