/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

//#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>

#include "headers/Game.h"


/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

Game* p_game = Game::getInstance();

const int SCREEN_WIDTH = 1280*2;
const int SCREEN_HEIGHT = 960*2;

Tile tiles[100];
int tileCount = 100;

typedef enum GAME_SCREENS 
{
    TITLE,
    GAMEPLAY,
    END,
}game_screen;

game_screen current_screen = TITLE;

class sGame {
public:
    sGame()
    {
        init();
    };
    ~sGame()
    {
        SDL_DestroySurface(g_surface);
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        SDL_Quit();
    }

    void init()
    {
        g_window = NULL;
        g_surface = NULL;
        g_renderer = NULL;
        test_texture = NULL;
        g_isRunning = true;

        Player* p_test_player = new Player();

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            if (!SDL_CreateWindowAndRenderer("ROGUEWORK AHEAD", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &g_window, &g_renderer))
            {
                printf("SDL could not initialize window and renderer! SDL_Error: %s\n", SDL_GetError());
            }
            else
            {
                g_surface = SDL_GetWindowSurface(g_window);
            }
        }

        delete p_test_player;

    };

    void g_loop()
    {
        SDL_Event g_event;

        //load images
        SDL_Surface* sp_title = loadMediaBMP("rogueworkaheadthumb_compA.bmp");
        SDL_Surface* sp_test = loadMediaBMP("TEST_SPRITE.bmp");
        SDL_Surface* sp_tile = loadMediaBMP("tile_walkable_a.bmp");
        SDL_Surface* sp_player = loadMediaBMP("player_a.bmp");
        SDL_Surface* sp_wall = loadMediaBMP("tile_wall_a.bmp");

        SDL_Rect stretchRect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_Rect tileRect = { 0,0,120,120 };

        // generate grid for drawing later
        int tileX = 0;
        int tileY = 0;
        int count = 0;
        for (int i = 0; i < 10; i++) 
        {
            tileX = 0;
            for (int j = 0; j < 10; j++) 
            {
                //tiles[count].setRectPos(tileX, tileY);
                tiles[count].setRectPos(tileX, tileY);
                if ((j % 2 == 0 && i % 3 == 0)) 
                {
                    tiles[count].setSprite(sp_wall);
                    tiles[count].setType(Type::WALL);
                }
                else 
                {
                    tiles[count].setSprite(sp_tile);
                    tiles[count].setType(Type::WALKABLE);
                }
                tileX += 120;
                count++;
            }
            tileY += 120;
        }
        tiles[0].setSprite(sp_tile);
        tiles[0].setType(Type::WALKABLE);


        while (g_isRunning)
        {

            SDL_PollEvent(&g_event);
            g_isRunning = handleGameScreen(current_screen, g_event);
            //SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
            //SDL_RenderClear(renderer);

            // render textures here
            SDL_FillSurfaceRect(g_surface, NULL, SDL_MapSurfaceRGB(g_surface, 0x00, 0x00, 0x00));
            if (current_screen == TITLE)  // TEMP, once other screens are implemented we'll probably want to handle this differently
            {
                SDL_BlitSurfaceScaled(sp_title, NULL, g_surface, &stretchRect, SDL_SCALEMODE_NEAREST);
            }
            else
            {
                generateLevel(tileRect, sp_tile, sp_wall);
                SDL_BlitSurfaceScaled(sp_player, NULL, g_surface, &playerRect, SDL_SCALEMODE_NEAREST);
            }
            SDL_UpdateWindowSurface(g_window);

            //SDL_RenderPresent(renderer);
        }

        SDL_DestroySurface(sp_title);
    };


private:
    SDL_Window* g_window;
    SDL_Renderer* g_renderer;
    SDL_Surface* g_surface;
    SDL_Texture* test_texture;
    bool g_isRunning;

    bool player_can_run = true;

    int player_x = 45;
    int player_y = 45;
    int player_step = 120;

    SDL_Rect playerRect = { player_x,player_y,120,120 };

    bool handleGameScreen(game_screen _screen, SDL_Event _event)
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
            // this is like gameover stuff 
            break;
        }
        return isRunning;
    }

    bool doTitle(SDL_Event _event)
    {
        player_x = 0;
        player_y = 0;
        playerRect = { player_x,player_y,120,120 };
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
            // continue to next game screen
            break;
        case SDL_EVENT_QUIT:
            return false;
            break;
        }
        return true;
    }

    bool doGameplay(SDL_Event _event)
    {
        switch (_event.type)
        {
        case SDL_EVENT_KEY_DOWN:
            if (_event.key.key == SDLK_ESCAPE)
            {
                current_screen = TITLE;
                return true;
            }
            if (player_can_run)
            {
                if (_event.key.key == SDLK_RIGHT)
                {
                    player_x += player_step;
                    if (canMoveToPosition(player_x, player_y)) 
                    {
                        playerRect = { player_x,player_y,120,120 };
                    }
                    else 
                    {
                        player_x -= player_step;
                    }
                    player_can_run = false;
                    return true;
                }
                if (_event.key.key == SDLK_LEFT)
                {
                    player_x -= player_step;
                    if (canMoveToPosition(player_x,player_y)) 
                    {
                        playerRect = { player_x, player_y,120,120 };
                    }
                    else 
                    {
                        player_x += player_step;
                    }
                    player_can_run = false;
                    return true;
                }
                if (_event.key.key == SDLK_UP)
                {
                    player_y -= player_step;
                    if (canMoveToPosition(player_x, player_y)) 
                    {
                        playerRect = { player_x, player_y, 120,120 };
                    }
                    else 
                    {
                        player_y += player_step;
                    }
                    player_can_run = false;
                    return true;
                }
                if (_event.key.key == SDLK_DOWN)
                {
                    player_y += player_step;
                    if (canMoveToPosition(player_x, player_y))
                    {
                        playerRect = { player_x, player_y, 120,120 };
                    }
                    else
                    {
                        player_y -= player_step;
                    }
                    player_can_run = false;
                    return true;
                }
            }
            break;
        case SDL_EVENT_KEY_UP:
            if (_event.key.key == SDLK_RIGHT)
            {
                player_can_run = true;
                return true;
            }
            if (_event.key.key == SDLK_LEFT)
            {
                player_can_run = true;
                return true;
            }
            if (_event.key.key == SDLK_UP)
            {
                player_can_run = true;
                return true;
            }
            if (_event.key.key == SDLK_DOWN)
            {
                player_can_run = true;
                return true;
            }
            break;
        case SDL_EVENT_QUIT:
            return false;
            break;
        }
        return true;
    }

    void generateLevel(SDL_Rect tile_rect, SDL_Surface* sp_tile, SDL_Surface* sp_wall)
    {
        int tileX = 0;
        int tileY = 0;
        for (int i = 0; i < 100; i++)
        {
            SDL_BlitSurfaceScaled(tiles[i].getSprite(), NULL, g_surface, &tiles[i].getRect(), SDL_SCALEMODE_NEAREST);
        }
    }

    bool canMoveToPosition(int x, int y) 
    {
        std::cout << x << "," << y << std::endl;
        for (int i = 0; i < tileCount; i++) 
        {
            if (tiles[i].getType() == Type::WALL)
            {
                if ((tiles[i].getX() == x) && (tiles[i].getY() == y)) // account for player offset
                {
                    std::cout << tiles[i].getX() << "," << tiles[i].getY() << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

    int flipCoin() 
    {
        srand(1);
        int coin_side = 0;
        return (rand()%5)+1;
    }

    SDL_Surface* loadMediaBMP(std::string file_path) 
    {
        SDL_Surface* p_surface = SDL_LoadBMP(file_path.c_str());
        if (p_surface == NULL) 
        {
            printf("ERROR: Unable to load image %s! SDL ERROR: %s\n", file_path, SDL_GetError());
        }
        return p_surface;
    }

};



int main(int argc, char* args[])
{
    sGame g_main;
    g_main.g_loop();
    return 1;
}