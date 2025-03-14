#include "Tile.h"

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
}

Tile::~Tile()
{
	SDL_DestroySurface(mp_sprite);
}
