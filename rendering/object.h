#include "../math/matrice.h"

#ifndef _OBJECT_H_
#define _OBJECT_H_

/**
 * @brief structure représentant un objet dans l'espace 3D
 * 
 */
typedef struct object
{
    Matrice_t** vertices;
    int n_vertices;

    int** edges;
    int n_edges;
} object_t;

/**
 * @brief intialise un objet avec ses points et ses arêtes à afficher
 * 
 * @param vertices 
 * @param n_vertices 
 * @param edges 
 * @param n_edge 
 * @return object_t* 
 */
object_t* initialiseObject(float vertices[][3], int n_vertices, int edges[][2], int n_edge);

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

Matrice_t** makeVertices(float coordinates[][3], int n_vertices);
int** makeEdges(int edges[][2], int n_edge);

#endif