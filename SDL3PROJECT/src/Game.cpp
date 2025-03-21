#include "../headers/Game.h"
Game* Game::g_instance = nullptr;

Game::Game() 
{

}

Game* Game::getInstance() 
{
	if (g_instance == nullptr) 
	{
		g_instance = new Game();
	}
	return g_instance;
}
