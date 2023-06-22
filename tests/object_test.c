#include "../rendering/object.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    double vertices[][3] = {{1,2,3},{4,5,6}};
    int edge[][2] = {{0,1}, {2,3}};

    int position[3] = {0,0,0};
    object_t* cube = initialiseObject(position, vertices, 2, edge, 2);
    print_object(cube);

    freeObject(cube);

    return 0;
}