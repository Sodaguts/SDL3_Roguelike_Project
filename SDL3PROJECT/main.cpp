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

const int SCREEN_WIDTH = 1280/2;
const int SCREEN_HEIGHT = 960/2;


class Game {
public:
    Game()
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
    ~Game() 
    {
        SDL_DestroySurface(g_surface);
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        SDL_Quit();
    }

    void init() {}; // TODO: ADD IMPLEMENTATION

    void g_loop() 
    {
        SDL_Event event;

        //load image
        SDL_Surface* p_mouseButton = SDL_LoadBMP("TEST_SPRITE.bmp");
        if (p_mouseButton == NULL) 
        {
            printf("ERROR: Unable to load image %s! SDL ERROR: %s\n", "images/aoi.bmp", SDL_GetError());
        }

        while (1) 
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_EVENT_QUIT) 
            {
                break;
            }
            //SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
            //SDL_RenderClear(renderer);

            // render textures here
            SDL_BlitSurface(p_mouseButton, NULL, g_surface, NULL);

            SDL_UpdateWindowSurface(g_window);

            //SDL_RenderPresent(renderer);
        }

        SDL_DestroySurface(p_mouseButton);
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