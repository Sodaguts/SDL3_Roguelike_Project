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


int main(int argc, char* args[])
{
    p_game->g_loop();
    return 1;
}