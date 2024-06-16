#include <stdlib.h>
#include "face.h"

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
