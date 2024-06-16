#include "rendering.h"
#include "camera.h"
#include <stdlib.h>
#include <stdbool.h>
#include "object.h"
#include <stdbool.h>

static void fat_point(SDL_Renderer* renderer, int x, int y, int size);
static bool out_of_bound(camera_t* camera, int x, int y);

static void fat_point(SDL_Renderer* renderer, int x, int y, int size){
    int up = y-size/2;
    int left = x-size/2;

    SDL_Rect rectangle = {left, up, size, size};
    if (SDL_RenderFillRect(renderer, &rectangle)!=0){
        fprintf(stderr, "Erreur de rendu fat_point : %s", SDL_GetError());
        return;
    }
}

void draw_object(SDL_Renderer* renderer, camera_t* camera, SDL_Color* color, object_t* obj){
    if(!is_visible(obj, camera)) return;
    Matrice_t** projected_vertices = getProjection(camera, obj);

    bool render_vertice = true;
    SDL_Color black = {0,0,0,255};
    if(SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }

    if(render_vertice){
        for (int i = 0; i < obj->n_vertices; i++)
        {
            if(!out_of_bound(camera, (int) projected_vertices[i]->array[0][0], (int) projected_vertices[i]->array[1][0])) {
                fat_point(renderer, projected_vertices[i]->array[0][0], projected_vertices[i]->array[1][0], 3);
            }
        }
    }

    if(SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a)!=0) {
        fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
        return;
    }

    for (int i = 0; i < obj->n_edges; i++)
    {
        int x1 = projected_vertices[obj->edges[i][0]]->array[0][0];
        int y1 = projected_vertices[obj->edges[i][0]]->array[1][0];
        if(out_of_bound(camera, x1,y1)) continue;

        int x2 = projected_vertices[obj->edges[i][1]]->array[0][0];
        int y2 = projected_vertices[obj->edges[i][1]]->array[1][0];
        if(out_of_bound(camera, x2, y2)) continue;

        if(SDL_RenderDrawLine(renderer, x1, y1, x2, y2)!=0) printf("Error line");
    }
    for (int i = 0; i < obj->n_vertices; i++)
    {
        freeMatrice(projected_vertices[i]);
    }
    free(projected_vertices);
}

static bool out_of_bound(camera_t* camera, int x, int y){
    return (x>camera->width || y>camera->height || x<0 || y<0);
}
