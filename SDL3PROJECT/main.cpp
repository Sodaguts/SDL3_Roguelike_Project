/*
 * This example code $WHAT_IT_DOES.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

//#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>


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
}game_screens;


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
        SDL_Event event;

        //load image
        SDL_Surface* sp_title = SDL_LoadBMP("title_screen_b.bmp");
        if (sp_title == NULL) 
        {
            printf("ERROR: Unable to load image %s! SDL ERROR: %s\n", "images/TEST_SPRITE.bmp", SDL_GetError());
        }

        SDL_Rect stretchRect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};

        bool isRunning = true;

        while (isRunning) 
        {
            SDL_PollEvent(&event);
            switch (event.type) 
            {
                case SDL_EVENT_KEY_DOWN:
                    printf("key pressed!\n");
                    if (event.key.key == SDLK_ESCAPE) 
                    {
                        isRunning = false;
                    }
                    break;
                case SDL_EVENT_KEY_UP:
                    printf("key released!\n");
                    break;
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;

            }
            //SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
            //SDL_RenderClear(renderer);

            // render textures here
            SDL_BlitSurfaceScaled(sp_title, NULL, g_surface, &stretchRect, SDL_SCALEMODE_NEAREST);

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
};



int main(int argc, char* args[])
{
    Game g_main;
    g_main.g_loop();
    return 1;
}