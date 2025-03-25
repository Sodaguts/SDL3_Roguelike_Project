#include "../headers/TileManager.h"

TileManager::TileManager() 
{
	std::string tileFilePath = "tile_walkable_a.bmp";
	mps_tile = SDL_LoadBMP(tileFilePath.c_str());
	if (mps_tile == NULL) 
	{
		printf("ERROR: UNABLE TO LOAD FILE! %s\n",tileFilePath);
	}
	else 
	{
		printf("Loaded image in TileManager.cpp successfully\n");
	}
	std::string wallFilePath = "tile_wall_a.bmp";
	mps_wall = SDL_LoadBMP(wallFilePath.c_str());
	if (mps_wall == NULL)
	{
		printf("ERROR: UNABLE TO LOAD FILE! %s\n", wallFilePath);
	}
	else 
	{
		printf("Loaded image in TileManager.cpp successfully\n");
	}

	msp_something = SDL_LoadBMP(tileFilePath.c_str());

	//initGrid();
}

void TileManager::initGrid(SDL_Surface* spr_wall, SDL_Surface* spr_tile) 
{
	int tileX = 0;
	int tileY = 0;
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		tileX = 0;
		for (int j = 0; j < 10; j++)
		{
			tiles[count].setRectPos(tileX, tileY);
			if ((j % 2 == 0 && i % 3 == 0))
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