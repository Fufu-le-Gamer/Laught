#include "EventManager.h"
#include "Character.h"
#include <cstdlib>
#include <ctime>

EventManager::EventManager()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void EventManager::triggerRandomEvent(Character& player)
{
	int choice = std::rand() % 2; // 2 action possibles (0, 1)

	switch (choice)
	{
		case 0: EventInvert(); break;
		case 1: EventFlip(); break;
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
