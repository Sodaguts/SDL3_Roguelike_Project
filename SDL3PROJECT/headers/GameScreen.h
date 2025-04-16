#pragma once
#include <SDL3/SDL.h>

class GameScreen 
{
public:
	//bool getScreen(SDL_Event _event) { return this->doScreen(_event); };
	virtual bool doScreen(SDL_Event _event) { return true; };

protected:
	//virtual bool doScreen(SDL_Event _event) = 0;
};