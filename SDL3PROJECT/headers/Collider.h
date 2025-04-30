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

	bool checkCollision(SDL_Rect other);

private:
	SDL_Rect m_rect;

	struct CollisionBounds 
	{
		int left;
		int right;
		int top;
		int bottom;
		void setBounds(SDL_Rect rect) 
		{
			left = rect.x;
			right = rect.x + rect.w;
			top = rect.y;
			bottom = rect.y + rect.h;
		}
	};

	CollisionBounds setCollisionBoundsOther(SDL_Rect other);
	CollisionBounds setCollisionBoundsSelf();
	
	bool compareBounds(CollisionBounds selfBounds, CollisionBounds otherBounds);

};