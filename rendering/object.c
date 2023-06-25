#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "object.h"
#include "../math/matrice.h"
#include "camera.h"

//HELPER FUNCTIONS
static Matrice_t** makeVertices(double coordinates[][3], int n_vertices);
static int** makeEdges(int edges[][2], int n_edge);

object_t* initialiseObject(int position[3], int rotation[3], double vertices[][3], int n_vertices, int edges[][2], int n_edge)
{
    object_t* result = malloc(sizeof(object_t));
    if(result==NULL) return NULL;

    result->n_edges = n_edge;
    result->n_vertices = n_vertices;
    result->edges = makeEdges(edges, n_edge);
    result->vertices = makeVertices(vertices, n_vertices);
    
    result->position = malloc(sizeof(Matrice_t*));
    result->position = initialiseMatrice(3,1,0);
    result->position->array[0][0] = position[0];
    result->position->array[1][0] = position[1];
    result->position->array[2][0] = position[2];

    result->rotation = malloc(sizeof(Matrice_t*));
    result->rotation = initialiseMatrice(3,1,0);
    result->rotation->array[0][0] = rotation[0];
    result->rotation->array[1][0] = rotation[1];
    result->rotation->array[2][0] = rotation[2];
    
    return result;
}

void freeObject(object_t *obj)
{
    if (obj==NULL) return;
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
    freeMatrice(obj->position);
    freeMatrice(obj->rotation);
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
        printf("(%d, %d) - ", object->edges[i][0], object->edges[i][1]);
    }
    printf("\n");
}

Matrice_t **getProjection(camera_t* camera, object_t *object)
{
    //Rotation de l'objet :
    Matrice_t* rotationX = rotationX_matrix(object->rotation->array[0][0]);
    Matrice_t* rotationY = rotationY_matrix(object->rotation->array[1][0]);
    Matrice_t* rotationZ = rotationZ_matrix(object->rotation->array[2][0]);

    //Rotation de la caméra :
    Matrice_t* cameraRotationX = rotationX_matrix(camera->rotation->array[0][0]);
    Matrice_t* cameraRotationY = rotationY_matrix(camera->rotation->array[1][0]);
    Matrice_t* cameraRotationZ = rotationZ_matrix(camera->rotation->array[2][0]);

    Matrice_t** projected_vertices = malloc(sizeof(Matrice_t*)*object->n_vertices);
    if (projected_vertices==NULL) return NULL;

    for (int i = 0; i < object->n_vertices; i++)
    {
        //Utilisé pour calculer les résultats intermédiaires, un peu moche il faudrait faire mieux pour ne pas devoir free et malloc à chaque résultat intermédiaire.
        Matrice_t* interComputation1;
        Matrice_t* interComputation2;

        //Rotation of the object
        multMatrice(rotationZ, object->vertices[i], &interComputation1);
        multMatrice(rotationY, interComputation1, &interComputation2);
        multMatrice(rotationX, interComputation2, projected_vertices);

        //Global position of the object
        (*projected_vertices)->array[0][0] += object->position->array[0][0];
        (*projected_vertices)->array[1][0] += object->position->array[1][0];
        (*projected_vertices)->array[2][0] += object->position->array[2][0];

        freeMatrice(interComputation1);
        freeMatrice(interComputation2);

        //CAMERA TRANSFORM
        subMatrice(*projected_vertices, camera->position, &interComputation1); //Position of matrix
        free(*projected_vertices);

        //3 rotations of the camera :
        multMatrice(cameraRotationZ, interComputation1, &interComputation2);
        freeMatrice(interComputation1);
        multMatrice(cameraRotationY, interComputation2, &interComputation1);
        freeMatrice(interComputation2);
        multMatrice(cameraRotationX, interComputation1, &interComputation2);
        freeMatrice(interComputation1);

        //HOMOGENEOUS COORDINATES
        double display_surface[3] = {0,0,camera->width};
        Matrice_t* homogeneous_matrix = identity_matrix(3);
        homogeneous_matrix->array[0][2] = display_surface[0]/display_surface[2];
        homogeneous_matrix->array[1][2] = display_surface[1]/display_surface[2];
        homogeneous_matrix->array[2][2] = 1.0/display_surface[2];

        multMatrice(homogeneous_matrix, interComputation2, projected_vertices);
        freeMatrice(interComputation2);

        //SCALE BY THE HOMOGENEOUS COORDINATE
        (*projected_vertices)->array[0][0] = (*projected_vertices)->array[0][0]/(*projected_vertices)->array[2][0]+camera->width/2; //x coordinate
        (*projected_vertices)->array[1][0] = (*projected_vertices)->array[1][0]/(*projected_vertices)->array[2][0]+camera->height/2; //y coordinate

        projected_vertices++;
    }
    projected_vertices-=object->n_vertices;

    freeMatrice(rotationX);
    freeMatrice(rotationY);
    freeMatrice(rotationZ);

    freeMatrice(cameraRotationX);
    freeMatrice(cameraRotationY);
    freeMatrice(cameraRotationZ);

    return projected_vertices;
}

void rotateX(object_t *object, double angle)
{
    object->rotation->array[0][0]+=angle;
}

void rotateY(object_t *object, double angle)
{
    object->rotation->array[1][0]+=angle;
}

void rotateZ(object_t *object, double angle)
{
    object->rotation->array[2][0]+=angle;
}

void translateX(object_t *object, double displacement)
{
    object->position->array[0][0]+=displacement;
}

void translateY(object_t *object, double displacement)
{
    object->position->array[1][0]+=displacement;
}

void translateZ(object_t *object, double displacement)
{
    object->position->array[2][0]+=displacement;
}

static Matrice_t** makeVertices(double coordinates[][3], int n_vertices)
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

static int** makeEdges(int edges[][2], int n_edge)
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
