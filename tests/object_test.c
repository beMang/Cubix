#include "../rendering/object.h"
#include "../rendering/camera.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    double vertices[][3] = {{1,2,3},{4,5,6}, {1,6,7}};
    int edge[][2] = {{0,1}, {2,3}};

    int position[3] = {0,0,0};
    object_t* cube = initialiseObject(position, position, vertices, 3, edge, 2);

    camera_t* camera = init_camera(position, position, 200,200);
    
    Matrice_t** result = getProjection(camera, cube);

    for (int i = 0; i < cube->n_vertices; i++)
    {
        freeMatrice(result[i]);
    }
    free(result);

    freeCamera(camera);
    freeObject(cube);

    return 0;
}