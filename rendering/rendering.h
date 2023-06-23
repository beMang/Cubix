#include <SDL2/SDL.h>
#include "object.h"
#include "camera.h"

#ifndef _RENDERING_H_
#define _RENDERING_H_

void draw_points(SDL_Renderer *renderer, SDL_Color *color, int thic);

void draw_object(SDL_Renderer *renderer, camera_t* camera, SDL_Color* color, object_t *obj);

void draw_square(SDL_Renderer *renderer, SDL_Color *color);

#endif
