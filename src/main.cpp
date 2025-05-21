#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include <vector>
#include <iostream>

#include "Chess.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
int windowWidth = 960, windowHeight = 540;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Chess", "1.0", "com.chess");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Vampire-Survivors", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Board test;
    test.print(); 
    std::cout << "\n";
    test.move(1, 0, 1, 2);
    test.print();
    std::cout << "\n";

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS; 
    if(event->key.key == 27)
        return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_WINDOW_RESIZED)
    {
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    }

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    /* clear the window to the draw color. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); 
    SDL_RenderClear(renderer);
    
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}