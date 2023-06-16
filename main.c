#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
#define TARGET_FPS 60.0

void draw_points(SDL_Renderer* renderer, SDL_Color* color, int thic){
    if(SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < thic; j++)
        {
            SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2+j, WINDOW_HEIGHT/2+i);
        }
    }
}

void draw_square(SDL_Renderer* renderer, SDL_Color* color){
    if(SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }
    SDL_Point point[5];
    point[0].x = 100;
    point[0].y = 100;
    point[1].x = 200;
    point[1].y = 100;
    point[2].x = 200;
    point[2].y = 200;
    point[3].x = 100;
    point[3].y = 200;   
    point[4].x = 100;
    point[4].y = 100;
    SDL_RenderDrawLines(renderer, point, 5);
}

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

    if(SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
    if(SDL_RenderClear(renderer)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
    draw_points(renderer, &white,10);
    draw_square(renderer, &black);
    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    while(!quit)
    {
        Uint32 t1 = SDL_GetTicks64();
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT) quit = SDL_TRUE;
        SDL_Delay((int)(1/TARGET_FPS*1000));
        Uint32 t2 = SDL_GetTicks64();
        float time = ((float) (t2-t1))/1000;
        printf("fps : %f.1 \n", 1/time);
    }
    status=EXIT_SUCCESS;

Quit:
    if (window!=NULL) SDL_DestroyWindow(window);
    if (renderer!=NULL) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return status;
}
