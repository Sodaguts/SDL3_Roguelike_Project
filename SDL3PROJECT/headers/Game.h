#pragma once
#include <SDL3/SDL.h>
#include <iostream>

#include "../headers/GameObject.h"
#include "../headers/TileManager.h"

#include "../headers/GameScreen.h"
#include "TitleScreen.h"
#include "ControllerComponent.h"
//#include "../headers/TileManager.h"


class Game 
{
public:
	Game(const Game& obj) = delete; // delete copy constructor

	static Game* getInstance();
	void init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void g_loop();
	void shutdown() {}; // delete g_instance and cleanup other pointers

	Tile getTile(int index) { return tiles[index]; };

	typedef enum GAMESCREENS
	{
		TITLE,
		GAMEPLAY,
		END,
	}GameScreens;

private:
	Game();
	static Game* g_instance;
	int m_int = 0;

	GameScreens current_screen = TITLE;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 960;

	//move over from main
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;

	GameScreen screen;

	bool m_isRunning;
	void update(SDL_Event g_event);
	void draw();

	bool handleGameScreen(GameScreens _screen, SDL_Event _event);
	// maybe make these their own classes or something idk
	bool doTitle(SDL_Event _event);
	bool doGameplay(SDL_Event _event);

	//put this into a grid manager or something later
	void initGrid(SDL_Surface* sp_wall, SDL_Surface* sp_tile);
	void drawGrid();

	//load images
	SDL_Surface* sp_title = loadMediaBMP("rogueworkaheadthumb_compA.bmp");
	SDL_Surface* sp_test = loadMediaBMP("TEST_SPRITE.bmp");
	SDL_Surface* sp_tile = loadMediaBMP("tile_walkable_a.bmp");
	SDL_Surface* sp_player = loadMediaBMP("player_a.bmp");
	SDL_Surface* sp_wall = loadMediaBMP("tile_wall_a.bmp");

	SDL_Rect stretchRect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect tileRect = { 0, 0, 120, 120 };

	ControllerComponent* mp_controller;
	//Player shit
	GameObject m_player;

	Tile tiles[100];
	int tileCount = 100;

	TileManager m_tileManager;

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

