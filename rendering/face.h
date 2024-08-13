#include <stdbool.h>
#include "../math/matrice.h"
#include "camera.h"

#ifndef _FACE_H_
#define _FACE_H_

typedef struct face
{
    int n_vertices;
    int* vertices;
    double normal[3];
} face_t;

face_t* makeFace(int vertices[], int n_vertices);
void freeFaces(face_t** faces, int n_faces);
void freeFace(face_t* face);
void print_face(face_t* face);

void computeNormal(face_t* face, Matrice_t** vertices);
bool isFaceVisible(face_t* face, camera_t* camera);

#endif