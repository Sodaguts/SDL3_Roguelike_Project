#include "../headers/TileManager.h"

TileManager::TileManager() 
{
	msp_tile = loadMediaBMP("tile_walkable_a.bmp");
	msp_wall = loadMediaBMP("tile_wall_a.bmp");
	msp_something = loadMediaBMP("tile_wall_a.bmp");
	msp_exit = loadMediaBMP("tile_exit_a.bmp");
	//initGrid();
}

void BFS() 
{
	//get a start tile and end tile
	//find a path from one to the other
	//any tiles in that path should become path tiles
}

void TileManager::initGrid(SDL_Surface* spr_wall, SDL_Surface* spr_tile) 
{
	int tileX = 0;
	int tileY = 0;
	int count = 0;

	int randMax = 10;
	int randMin = 2;
	for (int i = 0; i < 20; i++)
	{
		tileX = 0;
		for (int j = 0; j < 20; j++)
		{
			int randNum = (rand() % (randMax - randMin + 1)) + randMin;
			tiles[count].setRectPos(tileX, tileY);
			if (randNum >= 8)
			{
				tiles[count].setSprite(spr_wall);
				tiles[count].setType(TileType::WALL);
			}
			else
			{
				tiles[count].setSprite(spr_tile);
				tiles[count].setType(TileType::WALKABLE);
			}
			tileX += 120;
			count++;
		}
		tileY += 120;
	}
	tiles[0].setSprite(spr_tile);
	tiles[0].setType(TileType::WALKABLE);
}