#include <cstdio>
#include <string>
#include "../headers/Tile.h"

class TileManager
{
public:
	TileManager();

	Tile getTile(int index) { return tiles[index]; };
	void initGrid(SDL_Surface* spr_wall, SDL_Surface* spr_tile);
	SDL_Surface* getSomething() { return msp_something; };
private:
	Tile tiles[100];
	int tileCount = 100;

	SDL_Surface* mps_tile;
	SDL_Surface* mps_wall;

	SDL_Surface* msp_something;
	
};