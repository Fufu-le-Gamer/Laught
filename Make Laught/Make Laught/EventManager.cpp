#include "EventManager.h"
#include "Character.h"
#include <cstdlib>
#include <ctime>

EventManager::EventManager()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void EventManager::update()
{
	if (m_screamer && m_eventClock.getElapsedTime().asSeconds() > 2.0f)
	{
		m_screamer = false;
	}
}

void EventManager::triggerRandomEvent(Character& player)
{
	int choice = std::rand() % 3; // 3 action possibles (0, 1)

	switch (choice)
	{
		case 0: EventInvert(); break;
		case 1: EventFlip(); break;
		case 2: EventScreamer(); break;
	}
}

void EventManager::EventInvert()
{
	m_inverted = !m_inverted;
}

void EventManager::EventFlip()
{
	m_flipped = !m_flipped;
}

void EventManager::EventScreamer()
{
	m_screamer = true;
	m_eventClock.restart();
}
