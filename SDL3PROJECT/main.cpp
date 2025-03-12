/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

//#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string>


/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 1280*2;
const int SCREEN_HEIGHT = 960*2;

typedef enum GAME_SCREENS 
{
    TITLE,
    GAMEPLAY,
    END,
}game_screen;

game_screen current_screen = TITLE;

class Game {
public:
    Game()
    {
        init();     
    };
    ~Game() 
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

    };

    void g_loop() 
    {
        SDL_Event g_event;

        //load images
        SDL_Surface* sp_title = loadMediaBMP("title_screen_b.bmp");
        SDL_Surface* sp_test = loadMediaBMP("TEST_SPRITE.bmp");

        SDL_Rect stretchRect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
        


        while (g_isRunning) 
        {
            

            SDL_PollEvent(&g_event);
            g_isRunning = handleGameScreen(current_screen,g_event);
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
                SDL_BlitSurfaceScaled(sp_test, NULL, g_surface, &playerRect, SDL_SCALEMODE_NEAREST);
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

    int test_num = 0;

    SDL_Rect playerRect = { 0,0,120,120 };

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
        test_num = 0;
        playerRect = {0,0,120,120};
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
                if (_event.key.key == SDLK_0) 
                {
                    test_num += 10;
                    playerRect = {test_num,0,120,120 };
                    return true;
                }
                break;
            case SDL_EVENT_QUIT:
                return false;
                break;
        }
        return true;
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
    Game g_main;
    g_main.g_loop();
    return 1;
}