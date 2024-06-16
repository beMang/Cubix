#include "camera.h"
#include "../math/matrice.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double MAX_ROTATION = 25.0*3.1415/180.0; // in radians

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
    if (camera->rotation->array[0][0]>MAX_ROTATION)
    {
        camera->rotation->array[0][0] = MAX_ROTATION;
    }
    else if (camera->rotation->array[0][0]<-MAX_ROTATION)
    {
        camera->rotation->array[0][0] = -MAX_ROTATION;
    }
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

Matrice_t* getCameraVector(camera_t* camera)
{
    Matrice_t* result = initialiseMatrice(3,1,0);
    result->array[2][0] = 1.0;

    Matrice_t* rotationX = rotationX_matrix(camera->rotation->array[0][0]);
    Matrice_t* rotationY = rotationY_matrix(camera->rotation->array[1][0]);
    Matrice_t* rotationZ = rotationZ_matrix(camera->rotation->array[2][0]);

    Matrice_t* interComputation1 = NULL;
    Matrice_t* interComputation2 = NULL;

    //Rotation of the object
    multMatrice(rotationZ, result, &interComputation1);
    multMatrice(rotationY, interComputation1, &interComputation2);
    multMatrice(rotationX, interComputation2, &result);

    freeMatrice(interComputation1);
    freeMatrice(interComputation2);

    result->array[0][0] = -result->array[0][0]; //TODO : INVESTIGATE WHY THIS IS NECESSARY
    return result;
}
