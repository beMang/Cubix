#include "../rendering/camera.h"
#include <SDL2/SDL.h>

#ifndef _EVENT_H_
#define _EVENT_H_

void handleKeyboard(Uint8* clavier, camera_t* camera, SDL_bool* quit, SDL_Event event);

void handleMouse(camera_t* camera);
void initMouse(SDL_Window* window, SDL_Renderer* renderer);
#endif