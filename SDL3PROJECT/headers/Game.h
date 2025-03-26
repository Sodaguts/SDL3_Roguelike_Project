#include <SDL3/SDL.h>
#include <iostream>

#include "../headers/Player.h"
//#include "../headers/TileManager.h"


class Game 
{
public:
	Game(const Game& obj) = delete; // delete copy constructor

	static Game* getInstance();
	void init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void update();
	void draw();
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

	bool m_isRunning;

	void g_loop();

	bool handleGameScreen(GameScreens _screen, SDL_Event _event);
	// maybe make these their own classes or something idk
	bool doTitle(SDL_Event _event);
	bool doGameplay(SDL_Event _event);

	//put this into a grid manager or something later
	void initGrid(SDL_Surface* sp_wall, SDL_Surface* sp_tile);
	void drawGrid();

	//Player shit
	Player m_player;

	Tile tiles[100];
	int tileCount = 100;

	TileManager m_tileManager;

	SDL_Surface* loadMediaBMP(std::string file_path) 
	{
		SDL_Surface* p_surface = SDL_LoadBMP(file_path.c_str());
		if (p_surface == NULL)
		{
			printf("ERROR: Unable to load image %s! SDL ERROR: %s\n", file_path, SDL_GetError());
		}
		else 
		{
			printf("LOADED: %s\n", file_path.c_str());
		}
		return p_surface;
	}
};

