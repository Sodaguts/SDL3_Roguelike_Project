#include <cstdio>
#include <SDL3/SDL.h>

class Tile 
{
public:
	Tile();
	Tile(int _x, int _y);
	~Tile();

	int getX() { return x; };
	int getY() { return y; };
	void setX(int value) { x = value; };
	void setY(int value) { y = value; };
	void setSprite(SDL_Surface* p_surface) { mp_sprite = p_surface; };
	void setRectPos(int x, int y) { m_rect = {x,y,120,120}; };
	SDL_Rect getRect() { return m_rect; };
	SDL_Surface* getSprite() { return mp_sprite; };


private:
	int x;
	int y;
	SDL_Surface* mp_sprite; // sprite
	SDL_Rect m_rect;
};