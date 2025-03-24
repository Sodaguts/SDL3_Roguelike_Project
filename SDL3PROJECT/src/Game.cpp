#include "../headers/Game.h"
Game* Game::g_instance = nullptr;

//static SDL_Renderer* renderer = NULL;


Game::Game() 
{
	init(SCREEN_WIDTH,SCREEN_HEIGHT);
}

void Game::g_loop()
{
	SDL_Event g_event;

	//load images
	SDL_Surface* sp_title = loadMediaBMP("rogueworkaheadthumb_compA.bmp");
	SDL_Surface* sp_test = loadMediaBMP("TEST_SPRITE.bmp");
	SDL_Surface* sp_tile = loadMediaBMP("tile_walkable_a.bmp");
	SDL_Surface* sp_player = loadMediaBMP("player_a.bmp");
	SDL_Surface* sp_wall = loadMediaBMP("tile_wall_a.bmp");

	SDL_Rect stretchRect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect tileRect = {0, 0, 120, 120};
	//SDL_Rect playerRect = {0,0, 120,120};

	initGrid(sp_wall, sp_tile);

	// main game loop
	while (m_isRunning) 
	{
		SDL_PollEvent(&g_event);
		m_isRunning = handleGameScreen(current_screen, g_event);
		m_player.handlePlayerInput(g_event);
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderClear(m_renderer);

		// render textures here
		SDL_FillSurfaceRect(m_surface, NULL, SDL_MapSurfaceRGB(m_surface, 0x00, 0x00, 0x00));
		if (current_screen == TITLE)  // TEMP, once other screens are implemented we'll probably want to handle this differently
		{
		    SDL_BlitSurfaceScaled(sp_title, NULL, m_surface, &stretchRect, SDL_SCALEMODE_NEAREST);
		}
		else
		{
			drawGrid();
		    //generateLevel(tileRect, sp_tile, sp_wall);
		    SDL_BlitSurfaceScaled(sp_player, NULL, m_surface, &m_player.getRect(), SDL_SCALEMODE_NEAREST);
			//SDL_FillSurfaceRect(m_surface, NULL, SDL_MapSurfaceRGB(m_surface, 0x00, 0x00, 0x00)); //TEMP
		}
		SDL_UpdateWindowSurface(m_window);

		//SDL_RenderPresent(renderer);
	}

	SDL_DestroySurface(sp_title);
}

bool Game::handleGameScreen(GameScreens _screen, SDL_Event _event)
{
	bool isRunning = true;
	switch (_screen) 
	{
		case TITLE:
			isRunning = doTitle(_event);
			break;
		case GAMEPLAY:
			isRunning = doGameplay(_event);
			break;
		case END:
			break;
	}
	return isRunning;
}

bool Game::doTitle(SDL_Event _event)
{
	switch (_event.type)
	{
	case SDL_EVENT_KEY_DOWN:
		if (_event.key.key == SDLK_ESCAPE)
		{
			return false;
		}
		else if (_event.key.key == SDLK_SPACE)
		{
			current_screen = GAMEPLAY;
			return true;
		}
		break;
	case SDL_EVENT_QUIT:
		return false;
		break;
	}
	return true;
}

bool Game::doGameplay(SDL_Event _event)
{
	switch (_event.type) 
	{
		case SDL_EVENT_QUIT:
			return false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (_event.key.key == SDLK_ESCAPE) 
			{
				current_screen = TITLE;
				return true;
			}
			break;
	}
	return true;
}


Game* Game::getInstance() 
{
	if (g_instance == nullptr) 
	{
		g_instance = new Game();
	}
	return g_instance;
}

void Game::init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	m_window = NULL;
	m_surface = NULL;
	m_renderer = NULL;
	m_isRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else 
	{
		if (!SDL_CreateWindowAndRenderer("ROGUEWORK AHEAD", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &m_window, &m_renderer))
		{
			printf("SDL could not initialize window and renderer! SDL_Error: %s\n", SDL_GetError());
		}
		else 
		{
			m_surface = SDL_GetWindowSurface(m_window);
		}
	}
}

void Game::update()
{
	g_loop();
}

void Game::draw()
{
}

void Game::initGrid(SDL_Surface* sp_wall, SDL_Surface* sp_tile) 
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
				tiles[count].setSprite(sp_wall);
				tiles[count].setType(TileType::WALL);
			}
			else
			{
				tiles[count].setSprite(sp_tile);
				tiles[count].setType(TileType::WALKABLE);
			}
			tileX += 120;
			count++;
		}
		tileY += 120;
	}
	tiles[0].setSprite(sp_tile);
	tiles[0].setType(TileType::WALKABLE);
}

void Game::drawGrid() 
{
	int tileX = 0;
	int tileY = 0;
	for (int i = 0; i < 100; i++)
	{
		SDL_BlitSurfaceScaled(tiles[i].getSprite(), NULL, m_surface, &tiles[i].getRect(), SDL_SCALEMODE_NEAREST);
	}
}
