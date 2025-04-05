#pragma once

#include <cstdio>
#include <string>
#include "../headers/Tile.h"
#include <random>


// handles the generation of the grid

class TileManager
{
public:
	TileManager();

	Tile getTile(int index) { return tiles[index]; };
	Tile tiles[400];
	int getCount() { return tileCount; };
	void initGrid(SDL_Surface* spr_wall, SDL_Surface* spr_tile);
	SDL_Surface* getSomething() { return msp_something; };

	void update(SDL_Event e, SDL_Surface* wall, SDL_Surface* tile) 
	{
		if (e.type == SDL_EVENT_KEY_DOWN)
		{
			if (m_canRegen) 
			{
				if (e.key.key == SDLK_R)
				{
					initGrid(wall, tile);
					m_canRegen = false;
				}
			}
		}
		else if (e.type == SDL_EVENT_KEY_UP) 
		{
			if (e.key.key == SDLK_R) 
			{
				m_canRegen = true;
			}
		}
	}

private:
	
	int tileCount = 400;
	bool m_canRegen = true;

	void BFS();

	SDL_Surface* msp_tile;
	SDL_Surface* msp_wall;

	SDL_Surface* msp_something;

	SDL_Surface* loadMediaBMP(std::string file_path)
	{
		SDL_Surface* p_surface = SDL_LoadBMP(file_path.c_str());
		if (p_surface == NULL)
		{
			printf("ERROR: Unable to load image %s! SDL ERROR: %s\n", file_path.c_str(), SDL_GetError());
		}
		else
		{
			printf("LOADED: %s\n", file_path.c_str());
		}
		return p_surface;
	}
};