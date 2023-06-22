#include "rendering.h"
#include <stdlib.h>
#include "object.h"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 800
#endif

#define WINDOW_HEIGHT 480

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

void draw_object(SDL_Renderer* renderer, SDL_Color* color, object_t* obj){
    int scale = 20;
    if(SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }
    for (int i = 0; i < obj->n_vertices; i++)
    {
        SDL_RenderDrawPoint(renderer, obj->vertices[i]->array[0][0]*scale, obj->vertices[i]->array[1][0]*scale);
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
