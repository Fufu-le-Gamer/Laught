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
	float elapsed = m_eventClock.getElapsedTime().asSeconds();
	if (m_screamer && elapsed > 2.0f) m_screamer = false;
	if (m_pandaria && elapsed > 2.0f) m_pandaria = false;
	if (m_fart && elapsed > 1.0f) m_fart = false;
	if (m_macron && elapsed > 1.0f) m_macron = false;
	if (m_duck && elapsed > 2.0f)    m_duck = false;
	if (m_charles && elapsed > 8.0f) m_charles = false;
	if (m_cat && elapsed > 6.0f)     m_cat = false;
	if (m_internal && elapsed > 2.0f) m_internal = false;
}

void EventManager::triggerRandomEvent(Character& player)
{
	int choice = std::rand() % 10; // nombre d'actions possibles

	switch (choice)
	{
	case 0: EventInvert(); break;
	case 1: EventFlip(); break;
	case 2: EventScreamer(); break;
	case 3: EventPandaria(); break;
	case 4: EventFart(); break;
	case 5: EventMacron(); break;
	case 6: EventDuck(); break;
	case 7: EventCharles(); break;
	case 8: EventCat(); break;
	case 9: EventInternal(); break;
	}
}

void EventManager::EventDuck()
{
	m_duck = true;
	m_eventClock.restart();
}
void EventManager::EventCharles()
{
	m_charles = true;
	m_eventClock.restart();
}

void EventManager::EventCat()
{
	m_cat = true;
	m_eventClock.restart();
}

void EventManager::EventInternal()
{
	m_internal = true;
	m_eventClock.restart();
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

void EventManager::EventPandaria()
{
	m_pandaria = true;
	m_eventClock.restart();
}

void EventManager::EventFart()
{
	m_fart = true;
	m_eventClock.restart();
}

void EventManager::EventMacron()
{
	m_macron = true;
	m_eventClock.restart();
}
