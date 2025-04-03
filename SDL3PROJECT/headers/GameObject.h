#include <cstdio>
#include <SDL3/SDL.h>
#include "Collider.h"

//#include "../headers/Collider.h"

class GameObject 
{
public:
	GameObject()
	{
		m_playerCanMove = true;
		m_playerStep = 120;
		m_posX = 0;
		m_posY = 0;
		m_prevX = 0;
		m_prevY = 0;
		m_rect = { m_posX,m_posY,120,120 };
		mp_sprite = nullptr;
	};
	~GameObject();
	void update();
	//void draw();
	void handlePlayerInput(SDL_Event _event);



	int getX() { return m_posX; };
	int getY() { return m_posY; };
	SDL_Rect& getRect() { return m_rect; };
	void setRectPrev();

	bool checkCollision(SDL_Rect other) 
	{
		int leftA = m_rect.x;
		int rightA = m_rect.x + m_rect.w;
		int topA = m_rect.y;
		int botA = m_rect.y + m_rect.h;

		int leftB = other.x;
		int rightB = other.x + other.w;
		int topB = other.y;
		int botB = other.y + other.h;

		if (botA <= topB) 
		{
			return false;
		}

		if (topA >= botB) 
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

	void setSprite(SDL_Surface* p_sprite) { mp_sprite = p_sprite; };

private:
	//void handlePlayerInput(SDL_Event _event);
	SDL_Rect m_rect;
	int m_playerStep;
	int m_posX;
	int m_posY;
	bool m_playerCanMove;

	int m_prevX = 0;
	int m_prevY = 0;

	SDL_Surface* mp_sprite;


};