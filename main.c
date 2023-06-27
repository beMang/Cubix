#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "rendering/object.h"
#include "rendering/rendering.h"
#include "rendering/camera.h"
#include "loader/obj_file_loader.h"
#include "events/event.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
#define TARGET_FPS 60.0

int main()
{
    int status = EXIT_FAILURE;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)!=0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError()); //Envoie l'erreur dans le flux d'erreur standard stderr
        goto Quit;
    }

    SDL_Renderer* renderer;
    SDL_Window* window;

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)!=0){
        fprintf(stderr, "Erreur de SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetWindowTitle(window, "Cubix");

    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color red = {255,0,0,255};
    SDL_Color blue = {30,144,255, 255};

    int position[3] = {100,0,50};
    int rotation[3] = {0,0,0};

    double vertices[][3] = {
        {-50,-50,-50},{50,-50,-50},{-50,50,-50},{50,50,-50},
        {-50,-50,50},{50,-50,50},{-50,50,50},{50,50,50}
    };
    int edge[][2] = {
        {0,1},{1,3},{3,2},{2,0},
        {4,5},{5,7},{7,6},{6,4},
        {0,4},{2,6},{3,7},{1,5}
    };

    int camera_position[3] = {0,0,-100};
    camera_t* camera = init_camera(camera_position, rotation, WINDOW_HEIGHT, WINDOW_WIDTH);
    if(camera==NULL) fprintf(stderr, "Erreur lords de l'initialisation de la caméra");

    object_t* cube = initialiseObject(position, rotation, vertices, 8, edge, 12);
    if(cube==NULL) fprintf(stderr, "Erreur lords de l'initialisation d'un objet");

    object_t* custom_object = loadObject("model/unicorn.obj", 2.0);
    translateY(custom_object, 50);
    rotateY(custom_object, 3.14/2);
    
    SDL_Event event;
    SDL_bool quit = SDL_FALSE;
    Uint8* clavier;
    initMouse(window, renderer);
    while(!quit)
    {
        Uint64 t1 = SDL_GetTicks64();
        if(SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a)!=0) {
            fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
            goto Quit;
        }
        if(SDL_RenderClear(renderer)!=0) {
            fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
            goto Quit;
        }

        handleKeyboard(clavier, camera, &quit, event);
        handleMouse(camera);

        rotateY(cube, 0.03);
        //rotateY(custom_object, 0.03);

        draw_object(renderer, camera, &blue, cube);
        draw_object(renderer, camera, &red, custom_object);

        SDL_RenderPresent(renderer);

        SDL_Delay((int)(1/TARGET_FPS*1000));
        Uint64 t2 = SDL_GetTicks64();
        float time = ((float) (t2-t1))/1000;
        //printf("fps : %f.1 \n", 1/time); //SHOW FPS COUNTER IN TERMINAL
    }
    status=EXIT_SUCCESS;

Quit:
    free(clavier);
    freeObject(cube);
    freeObject(custom_object);
    freeCamera(camera);
    if (window!=NULL) SDL_DestroyWindow(window);
    if (renderer!=NULL) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return status;
}
