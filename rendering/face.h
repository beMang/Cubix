#include <stdbool.h>

#ifndef _FACE_H_
#define _FACE_H_

typedef struct face
{
    int n_vertices;
    int* vertices;
} face_t;

face_t* makeFace(int vertices[], int n_vertices);
void freeFaces(face_t** faces, int n_faces);
void freeFace(face_t* face);
void print_face(face_t* face);

#endif