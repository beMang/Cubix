#include "camera.h"
#include "../math/matrice.h"
#include <stdlib.h>
#include <stdio.h>

camera_t* init_camera(int position[3], int rotation[3])
{
    camera_t* camera = malloc(sizeof(camera_t));
    if (camera==NULL) return NULL;

    camera->position = initialiseMatrice(3,1,0);
    setPosition(camera, position[0], position[1], position[2]);

    camera->rotation = initialiseMatrice(3,1,0);
    setRotation(camera, rotation[0], rotation[1], rotation[2]);

    return camera;
}

void setPosition(camera_t *camera, int x, int y, int z)
{
    if(camera==NULL || camera->position==NULL) fprintf(stderr, "Camera pas initialisée correctement");

    camera->position->array[0][0] = x;
    camera->position->array[1][0] = y;
    camera->position->array[2][0] = z;
}

void setRotation(camera_t *camera, int x, int y, int z)
{
    if(camera==NULL || camera->rotation==NULL) fprintf(stderr, "Camera pas initialisée correctement");

    camera->rotation->array[0][0] = x;
    camera->rotation->array[1][0] = y;
    camera->rotation->array[2][0] = z;
}
