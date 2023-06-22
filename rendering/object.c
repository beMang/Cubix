#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "../math/matrice.h"

object_t* initialiseObject(float vertices[][3], int n_vertices, int edges[][2], int n_edge)
{
    object_t* result = malloc(sizeof(object_t));

    result->n_edges = n_edge;
    result->n_vertices = n_vertices;
    result->edges = makeEdges(edges, n_edge);
    result->vertices = makeVertices(vertices, n_vertices);
    
    return result;
}

void freeObject(object_t *obj)
{
    for (int i = 0; i < obj->n_edges; i++)
    {
        free(obj->edges[i]);
    }
    free(obj->edges);

    for (int i = 0; i < obj->n_vertices; i++)
    {
        freeMatrice(obj->vertices[i]);
    }
    free(obj->vertices);
    free(obj);
}

void print_object(object_t *object)
{
    printf("Nombre de points : %d       Nombre d'arête : %d\n", object->n_vertices, object->n_edges);

    printf("Points : \n");
    for (int i = 0; i < object->n_vertices; i++)
    {
        printf("x : %f - y : %f - z : %f\n", (object->vertices[i])->array[0][0], (object->vertices[i])->array[1][0], (object->vertices[i])->array[2][0]);
    }
    printf("\nArêtes :");
    for (int i = 0; i < object->n_edges; i++)
    {
        printf("(%d, %d)\n", object->edges[i][0], object->edges[i][1]);
    }
}

Matrice_t **makeVertices(float coordinates[][3], int n_vertices)
{

    Matrice_t** result = malloc(sizeof(Matrice_t*)*n_vertices);
    if (result==NULL) return NULL;

    for (int i = 0; i < n_vertices; i++)
    {
        result[i] = initialiseMatrice(3, 1, 0);
        if (result[i]==NULL) return NULL;

        setValue(result[i], 0, 0, coordinates[i][0]);
        setValue(result[i], 1, 0, coordinates[i][1]);
        setValue(result[i], 2, 0, coordinates[i][2]);
    }
    return result;
}

int **makeEdges(int edges[][2], int n_edge)
{
    int** result = malloc(sizeof(int*)*n_edge);
    if(result==NULL) return NULL;

    for (int i = 0; i < n_edge; i++)
    {
        result[i] = malloc(sizeof(int)*2);
        if (result[i]==NULL) return NULL;

        result[i][0] = edges[i][0];
        result[i][1] = edges[i][1];
    }
    return result;
}
