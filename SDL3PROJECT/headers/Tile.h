#include <cstdio>
#include <SDL3/SDL.h>
#include "Collider.h"


typedef enum TileType 
{
	WALKABLE=0,
	WALL,
}tileType;

class Tile 
{
public:
	Tile();
	Tile(int _x, int _y);
	Tile(int _x, int _y, TileType _type);
	~Tile();

	int getX() { return x; };
	int getY() { return y; };
	void setX(int value) { x = value; };
	void setY(int value) { y = value; };
	void setSprite(SDL_Surface* p_surface) { mp_sprite = p_surface; };
	void setRectPos(int x, int y) { m_rect = { x,y,120,120 }; setX(x); setY(y); };
	SDL_Rect& getRect() { return m_rect; };
	SDL_Surface* getSprite() { return mp_sprite; };
	TileType getType() { return m_type; };
	void setType(TileType type) { m_type = type; };

	bool isSpriteSet()
	{
		if (mp_sprite == nullptr)
		{
			return false;
		}
		return true;
	};


private:
	int x;
	int y;
	SDL_Surface* mp_sprite; // sprite
	SDL_Rect m_rect;
	TileType m_type;
};