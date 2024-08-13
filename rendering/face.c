#include <stdlib.h>
#include <stdio.h>
#include "face.h"
#include "../math/matrice.h"

face_t* makeFace(int vertices[], int n_vertices)
{
    face_t* result = malloc(sizeof(face_t));
    if(result==NULL) return NULL;

    result->n_vertices = n_vertices;
    result->vertices = malloc(n_vertices*sizeof(int));
    if(result->vertices==NULL) return NULL;

    for (int i = 0; i < n_vertices; i++)
    {
        result->vertices[i] = vertices[i];
    }
    
    return result;
}

void freeFaces(face_t **faces, int n_faces)
{
    for (int i = 0; i < n_faces; i++)
    {
        freeFace(faces[i]);
    }
    free(faces);
}

void freeFace(face_t *face)
{
    free(face->vertices);
    free(face);
}

void print_face(face_t *face)
{
    printf("Nombre de points : %d\n", face->n_vertices);
    printf("Points : ");
    for (int i = 0; i < face->n_vertices; i++)
    {
        printf("%d ", face->vertices[i]);
    }
    printf("\n");
}

void computeNormal(face_t *face, Matrice_t **vertices)
{
    Matrice_t* v1 = vertices[face->vertices[0]];
    Matrice_t* v2 = vertices[face->vertices[1]];
    Matrice_t* v3 = vertices[face->vertices[2]];

    Matrice_t* u = NULL;
    Matrice_t* v = NULL;
    subMatrice(v2, v1, &u);
    subMatrice(v3, v1, &v);

    //cross product
    face->normal[0] = u->array[1][0]*v->array[2][0] - u->array[2][0]*v->array[1][0];
    face->normal[1] = u->array[2][0]*v->array[0][0] - u->array[0][0]*v->array[2][0];
    face->normal[2] = u->array[0][0]*v->array[1][0] - u->array[1][0]*v->array[0][0];

    freeMatrice(u);
    freeMatrice(v);
}

bool isFaceVisible(face_t *face, camera_t *camera)
{
    Matrice_t* cameraVector = getCameraVector(camera);

    double dot = face->normal[0]*cameraVector->array[0][0] + face->normal[1]*cameraVector->array[1][0] + face->normal[2]*cameraVector->array[2][0];
    return dot<0;
}
