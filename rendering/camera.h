#include "../math/matrice.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_

/**
 * @brief représente la caméra utilisée pour le rendu
 * 
 */
typedef struct camera
{
    Matrice_t* position;
    Matrice_t* rotation;

    int height;
    int width;
} camera_t;

/**
 * @brief initialise une caméra
 * 
 * @param camera 
 * @param position 
 * @param rotation 
 * @return int 0 si succès 0 sinon
 */
camera_t* init_camera(int position[3], int rotation[3], int height, int width);

/**
 * @brief libère un pointeur pointant vers une caméra
 * 
 * @param camera 
 */
void freeCamera(camera_t* camera);

/**
 * @brief Set the position of the camera
 * 
 * @param camera 
 * @param x x coordinate
 * @param y y coordinate
 * @param z z coordinate
 */
void setPosition(camera_t* camera, int x, int y, int z);

/**
 * @brief Set the rotatio of the camera (unit of angle is in radian)
 * 
 * @param camera 
 * @param x x rotation
 * @param y y rotation
 * @param z z rotation
 */
void setRotation(camera_t* camera, int x, int y, int z);

void rotate_X_camera(camera_t* camera, double angle);
void rotate_Y_camera(camera_t* camera, double angle);
void rotate_Z_camera(camera_t* camera, double angle);

void translate_X_camera(camera_t* camera, double displacement);
void translate_Y_camera(camera_t* camera, double displacement);
void translate_Z_camera(camera_t* camera, double displacement);

Matrice_t* getCameraVector(camera_t* camera);

#endif