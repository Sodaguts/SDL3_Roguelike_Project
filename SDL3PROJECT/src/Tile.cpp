#include "../headers/Tile.h"

Tile::Tile()
{
	setX(0);
	setY(0);
	mp_sprite = nullptr;
}

Tile::Tile(int _x, int _y) 
{
	setX(_x);
	setY(_y);
	mp_sprite = nullptr;
}

Tile::Tile(int _x, int _y, TileType _type) 
{
	setX(_x);
	setY(_y);
	mp_sprite = nullptr;
}

Tile::~Tile()
{
	SDL_DestroySurface(mp_sprite);
}
