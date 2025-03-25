#include <cstdio>
#include <SDL3/SDL.h>

#include "../headers/TileManager.h"

class Player 
{
public:
	Player()
	{
		m_playerCanMove = true;
		m_playerStep = 120;
		m_posX = 0;
		m_posY = 0;
		m_rect = { m_posX,m_posY,120,120 };
		mp_sprite = nullptr;
	};
	~Player();
	void update();
	//void draw();
	void handlePlayerInput(SDL_Event _event);

	int getX() { return m_posX; };
	int getY() { return m_posY; };
	SDL_Rect getRect() { return m_rect; };

	void setSprite(SDL_Surface* p_sprite) { mp_sprite = p_sprite; };

private:
	//void handlePlayerInput(SDL_Event _event);
	SDL_Rect m_rect;
	int m_playerStep;
	int m_posX;
	int m_posY;
	bool m_playerCanMove;

	SDL_Surface* mp_sprite;

	TileManager* mp_tileManager;

};