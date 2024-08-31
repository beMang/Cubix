#include "event.h"
#include <SDL2/SDL.h>
#include "../rendering/camera.h"

void handleKeyboard(camera_t* camera, SDL_bool* quit, SDL_Event event)
{
    SDL_PumpEvents();
    const Uint8* clavier = SDL_GetKeyboardState(NULL);

    double speed = 1.0;

    if (clavier[SDL_SCANCODE_W]) translate_Z_camera(camera, speed);
    if (clavier[SDL_SCANCODE_S]) translate_Z_camera(camera, -speed);
    if (clavier[SDL_SCANCODE_A]) translate_X_camera(camera, -speed);
    if (clavier[SDL_SCANCODE_D]) translate_X_camera(camera, speed);
    if(clavier[SDL_SCANCODE_LCTRL]) translate_Y_camera(camera, speed);
    if(clavier[SDL_SCANCODE_LSHIFT]) translate_Y_camera(camera, -speed);

    if(clavier[SDL_SCANCODE_ESCAPE]) *quit = SDL_TRUE;

    while(SDL_PollEvent(&event))
        if(event.type == SDL_QUIT) *quit = SDL_TRUE;
}

void handleMouse(camera_t* camera)
{
    int x = 0;
    int y = 0;
    SDL_GetRelativeMouseState(&x, &y);

    double x_sensivity = 0.005;
    double y_sensivity = 0.005;

    rotate_Y_camera(camera, -x_sensivity*x);
    rotate_X_camera(camera, y*y_sensivity);
}

void initMouse(SDL_Window* window, SDL_Renderer* renderer)
{
    int w_width = 0;
    int w_height = 0;

    if(SDL_GetRendererOutputSize(renderer, &w_width, &w_height)!=0) fprintf(stderr, "Erreur de SDL_SetRenderDrawColor : %s", SDL_GetError());
    printf("%d\n", w_width);
    SDL_WarpMouseInWindow(window, w_width/2, w_height/2);
    int x = 0;
    int y = 0;
    SDL_GetRelativeMouseState(&x, &y);
}
