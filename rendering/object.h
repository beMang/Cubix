#include "../math/matrice.h"
#include "camera.h"
#include "face.h"
#include <stdbool.h>

#ifndef _OBJECT_H_
#define _OBJECT_H_

/**
 * @brief structure représentant un objet dans l'espace 3D
 * 
 */
typedef struct object
{
    Matrice_t* position;
    Matrice_t* rotation;

    Matrice_t** vertices;
    int n_vertices;

    face_t** faces;
    int n_faces;
} object_t;

/**
 * @brief intialise un objet avec ses points et ses faces
 * 
 * @param position 
 * @param rotation 
 * @param vertices 
 * @param n_vertices 
 * @param faces 
 * @param n_face 
 * @return object_t* 
 */
object_t* initialiseObject(int position[3], int rotation[3], double vertices[][3], int n_vertices, face_t** faces, int n_face);

/**
 * @brief free an object to liberate memory
 * 
 * @param obj 
 */
void freeObject(object_t* obj);

/**
 * @brief affiche un objet sur le terminal
 * 
 * @param object 
 */
void print_object(object_t* object);

bool is_visible(object_t* object, camera_t* camera);
Matrice_t** getProjection(camera_t* camera, object_t* object);

void rotateX(object_t* object, double angle);
void rotateY(object_t* object, double angle);
void rotateZ(object_t* object, double angle);

void translateX(object_t* object, double displacement);
void translateY(object_t* object, double displacement);
void translateZ(object_t* object, double displacement);

#endif