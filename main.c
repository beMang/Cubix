#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "rendering/object.h"
#include "rendering/rendering.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
#define TARGET_FPS 60.0

int main(int argc, char *argv[])
{
    int status = EXIT_FAILURE;

    if (SDL_Init(SDL_INIT_VIDEO)!=0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError()); //Envoie l'erreur dans le flux d'erreur standard stderr
        goto Quit;
    }

    SDL_Renderer* renderer;
    SDL_Window* window;

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, &window, &renderer)!=0){
        fprintf(stderr, "Erreur de SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetWindowTitle(window, "Ceci est un test :)");

    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color white = {255,255,255,255};
    SDL_Color black = {0,0,0,255};
    SDL_Color red = {255,0,0,255};

    float vertices[][3] = {
        {10,10,10},{20,10,10},{10,20,10},{20,20,10},
        {10,10,20},{20,10,20},{10,20,20},{20,20,20}
    };
    int edge[][2] = {
        {0,1},{1,3},{3,2},{2,0},
        {4,5},{5,7},{7,6},{6,4},
        {0,4},{2,6},{3,7},{1,5}
    };

    object_t* cube = initialiseObject(vertices, 8, edge, 12);
    
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    while(!quit)
    {
        if(SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
        }
        if(SDL_RenderClear(renderer)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
        }

        Uint32 t1 = SDL_GetTicks64();
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT) quit = SDL_TRUE;
        SDL_Delay((int)(1/TARGET_FPS*1000));
        Uint32 t2 = SDL_GetTicks64();
        float time = ((float) (t2-t1))/1000;
        printf("fps : %f.1 \n", 1/time);
        draw_object(renderer, &red, cube);
        draw_points(renderer, &white,10);
        draw_square(renderer, &black);
        
        SDL_RenderPresent(renderer);
    }
    
    status=EXIT_SUCCESS;
    freeObject(cube);

Quit:
    if (window!=NULL) SDL_DestroyWindow(window);
    if (renderer!=NULL) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return status;
}
