#include "Collider.h"

Collider::Collider(int posX, int posY, int width, int height)
{
	m_rect.x = posX;
	m_rect.y = posY;
	m_rect.w = width;
	m_rect.h = height;
}

bool Collider::checkCollision(SDL_Rect other)
{
	// based on lazyFoo implementation
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// get self calculation
	leftA = m_rect.x;
	rightA = m_rect.x + m_rect.w;
	topA = m_rect.y;
	bottomA = m_rect.y + m_rect.h;

	//get other calculation
	leftB = other.x;
	rightB = other.x + other.w;
	topB = other.y;
	bottomB = other.y + other.h;

	//collision detection
	if (bottomA <= topB) 
	{
		return false;
	}
	if (topA >= bottomB) 
	{
		return false;
	}
	if (rightA <= leftB) 
	{
		return false;
	}
	if (leftA >= rightB) 
	{
		return false;
	}


	return true;
}
