#include "rendering.h"
#include "camera.h"
#include <stdlib.h>
#include "object.h"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 800
#endif

#define WINDOW_HEIGHT 480

static void fat_point(SDL_Renderer* renderer, int x, int y, int size);

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

static void fat_point(SDL_Renderer* renderer, int x, int y, int size){
    int up = y-size/2;
    int left = x-size/2;

    SDL_Rect rectangle = {left, up, size, size};
    if (SDL_RenderFillRect(renderer, &rectangle)==-1){
        fprintf(stderr, "Erreur de rendu fat_point : %s", SDL_GetError());
        return;
    }
}

void draw_object(SDL_Renderer* renderer, camera_t* camera, SDL_Color* color, object_t* obj){
    if(SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }
    Matrice_t** projected_vertices = getProjection(camera, obj, 120.0);
    for (int i = 0; i < obj->n_vertices; i++)
    {
        fat_point(renderer, projected_vertices[i]->array[0][0], projected_vertices[i]->array[1][0], 5);
    }
    for (int i = 0; i < obj->n_edges; i++)
    {
        int x1 = projected_vertices[obj->edges[i][0]]->array[0][0];
        int y1 = projected_vertices[obj->edges[i][0]]->array[1][0];
        int x2 = projected_vertices[obj->edges[i][1]]->array[0][0];
        int y2 = projected_vertices[obj->edges[i][1]]->array[1][0];
        if(SDL_RenderDrawLine(renderer, x1, y1, x2, y2)!=0) printf("Error line");
    }
    for (int i = 0; i < obj->n_vertices; i++)
    {
        freeMatrice(projected_vertices[i]);
    }
    free(projected_vertices);
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
