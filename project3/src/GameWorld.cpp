#include "GameWorld.h"
#include "GameController.h"
#include <cstdlib>
#include <string>
using namespace std;

bool GameWorld::getKey(int &value)
{
	bool gotKey = m_controller->getLastKey(value);

	if (gotKey)
	{
		if (value == 'q' || value == '\x03') // CTRL-C
			m_controller->quitGame();
	}
	return gotKey;
}

void GameWorld::playSound(int soundID)
{
	std::cout << "PLAYING SOUND: " << SOUNDS[soundID] << std::endl; // TODO DELETE`
	m_controller->playSound(soundID);
}

void GameWorld::setGameStatText(string text)
{
	m_controller->setGameStatText(text);
}

void GameWorld::setMsPerTick(int ms_per_tick)
{
	m_controller->setMsPerTick(ms_per_tick);
}