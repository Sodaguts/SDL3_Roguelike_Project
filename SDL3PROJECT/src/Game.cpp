#include "../headers/Game.h"
Game* Game::g_instance = nullptr;


void Game::init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	m_window = NULL;
	m_surface = NULL;
	m_renderer = NULL;
	m_isRunning = true;

	if (!SDL_Init(SDL_INIT_VIDEO))
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

	//screen = TitleScreen();

}

Game::Game() 
{
	init(SCREEN_WIDTH,SCREEN_HEIGHT);
}

void Game::g_loop()
{
	SDL_Event g_event;

	//initGrid(sp_wall, sp_tile);
	m_tileManager.initGrid(sp_wall, sp_tile);

	mp_controller = new ControllerComponent();
	m_player.attachController(mp_controller);

	while (m_isRunning) 
	{
		SDL_PollEvent(&g_event);
		update(g_event);
		draw();
	}

	delete mp_controller;
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


void Game::update(SDL_Event g_event)
{
	//g_loop();
	m_isRunning = handleGameScreen(current_screen, g_event);
	m_tileManager.update(g_event, sp_wall, sp_tile);
	//m_player.handlePlayerInput(g_event);
	m_player.update(g_event);
	for (int i = 0; i < m_tileManager.getCount(); i++)
	{
		if (m_tileManager.tiles[i].getType() == TileType::WALL)
		{
			if (m_tileManager.tiles[i].getX() == m_player.getX() &&
				m_tileManager.tiles[i].getY() == m_player.getY())
			{
				m_player.setRectPrev();
			}
		}
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
	//SDL_RenderClear(m_renderer);
	SDL_Rect enemyRect;
	enemyRect.x = 0;
	enemyRect.y = 0;
	enemyRect.w = 120;
	enemyRect.h = 120;
	// render textures here
	SDL_FillSurfaceRect(m_surface, NULL, SDL_MapSurfaceRGB(m_surface, 0x00, 0x00, 0x00));
	if (current_screen == TITLE)  // TEMP, once other screens are implemented we'll probably want to handle this differently
	{
		SDL_BlitSurfaceScaled(sp_title, NULL, m_surface, &stretchRect, SDL_SCALEMODE_NEAREST);
	}
	else
	{
		drawGrid();
		SDL_BlitSurfaceScaled(sp_enemy, NULL, m_surface, &enemyRect, SDL_SCALEMODE_NEAREST);
		SDL_BlitSurfaceScaled(sp_player, NULL, m_surface, &m_player.getRect(), SDL_SCALEMODE_NEAREST);
	}
	SDL_UpdateWindowSurface(m_window);
}

void Game::drawGrid() 
{
	int tileX = 0;
	int tileY = 0;
	for (int i = 0; i < m_tileManager.getCount(); i++)
	{
		if (!m_tileManager.tiles[i].isSpriteSet())
		{
			std::cout << "no sprite found at index: " << i << std::endl;
		}
		SDL_BlitSurfaceScaled(m_tileManager.tiles[i].getSprite(), NULL, m_surface, &m_tileManager.tiles[i].getRect(), SDL_SCALEMODE_NEAREST);
	}
}

