#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
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
    if(SDL_TRUE){
        SDL_version *version = malloc(sizeof(SDL_version));
        SDL_GetVersion(version);
        printf("SDL version : %d.%d.%d\n", version->major, version->minor, version->patch);
    }

    int status = EXIT_FAILURE;
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;

    camera_t* camera = NULL;
    object_t* cube = NULL;
    object_t* custom_object = NULL;


    if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError()); //Envoie l'erreur dans le flux d'erreur standard stderr
        goto Quit;
    }

    window = SDL_CreateWindow("Cubix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN);
    if(window==NULL){
        fprintf(stderr, "Erreur de SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer==NULL){
        fprintf(stderr, "Erreur de SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color red = {255,0,0,255};
    SDL_Color blue = {30,144,255, 255};

    int position[3] = {0,0,250};
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

    int camera_position[3] = {0,0,0};
    camera = init_camera(camera_position, rotation, WINDOW_HEIGHT, WINDOW_WIDTH);
    if(camera==NULL) fprintf(stderr, "Erreur lords de l'initialisation de la caméra");

    cube = initialiseObject(position, rotation, vertices, 8, edge, 12);
    if(cube==NULL) fprintf(stderr, "Erreur lords de l'initialisation d'un objet");

    custom_object = loadObject("model/unicorn.obj", 2.0);
    translateY(custom_object, 50);
    rotateY(custom_object, 3.14/2);
    
    SDL_Event event;
    SDL_bool show_fps = SDL_FALSE;
    SDL_bool quit = SDL_FALSE;
    initMouse(window, renderer);
    while(!quit)
    {
        Uint64 t1;
        if(show_fps){
            t1 = SDL_GetTicks64();
        }

        if(SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a)!=0) {
            fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
            goto Quit;
        }
        if(SDL_RenderClear(renderer)!=0) {
            fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
            goto Quit;
        }

        handleKeyboard(camera, &quit, event);
        handleMouse(camera);

        rotateY(cube, 0.03);

        draw_object(renderer, camera, &blue, cube);
        draw_object(renderer, camera, &red, custom_object);

        SDL_RenderPresent(renderer);

        SDL_Delay((int)(1/TARGET_FPS*1000));

        if(show_fps){
            Uint64 t2 = SDL_GetTicks64();
            float time = ((float) (t2-t1))/1000;
            printf("fps : %f.1 \n", 1/time); //SHOW FPS COUNTER IN TERMINAL
        }
    }

    status=EXIT_SUCCESS;

Quit:
    if (cube!=NULL) freeObject(cube);
    if (custom_object!=NULL) freeObject(custom_object);
    if (camera!=NULL) freeCamera(camera);
    if (window!=NULL) SDL_DestroyWindow(window);
    if (renderer!=NULL) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return status;
}
