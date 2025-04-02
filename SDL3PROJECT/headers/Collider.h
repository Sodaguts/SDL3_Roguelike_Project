#pragma once
#include <SDL3/SDL.h>

class Collider 
{
public:
	Collider(int x, int y, int w, int h) 
	{
		m_rect.x = x;
		m_rect.y = y;
		m_rect.w = w;
		m_rect.h = h;
	};

	SDL_Rect getRect() { return m_rect; };

private:
	SDL_Rect m_rect;
};