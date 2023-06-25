#include "camera.h"
#include "../math/matrice.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

camera_t* init_camera(int position[3], int rotation[3], int height, int width)
{
    camera_t* camera = malloc(sizeof(camera_t));
    if (camera==NULL) return NULL;

    camera->position = initialiseMatrice(3,1,0);
    setPosition(camera, position[0], position[1], position[2]);

    camera->rotation = initialiseMatrice(3,1,0);
    setRotation(camera, rotation[0], rotation[1], rotation[2]);

    camera->height = height;
    camera->width = width;

    return camera;
}

void freeCamera(camera_t *camera)
{
    if(camera==NULL) return;
    freeMatrice(camera->position);
    freeMatrice(camera->rotation);
    free(camera);
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

void rotate_X_camera(camera_t *camera, double angle)
{
    camera->rotation->array[0][0]+=angle;
}

void rotate_Y_camera(camera_t *camera, double angle)
{
    camera->rotation->array[1][0]+=angle;
}

void rotate_Z_camera(camera_t *camera, double angle)
{
    camera->rotation->array[2][0]+=angle;
}

void translate_X_camera(camera_t *camera, double displacement)
{
    camera->position->array[0][0]+=displacement*cos(camera->rotation->array[1][0]);
    camera->position->array[2][0]+=displacement*sin(camera->rotation->array[1][0]);
}

void translate_Y_camera(camera_t *camera, double displacement)
{
    camera->position->array[1][0]+=displacement;
}

void translate_Z_camera(camera_t *camera, double displacement)
{
    camera->position->array[2][0]+=displacement*cos(camera->rotation->array[1][0]);
    camera->position->array[0][0]-=displacement*sin(camera->rotation->array[1][0]);
}
