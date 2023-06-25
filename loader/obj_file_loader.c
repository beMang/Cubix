#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj_file_loader.h"
#include "../rendering/object.h"

#define MAX 100

int* countVerticesAndEdge(char *fileName)
{
    int* result = malloc(2*sizeof(int));

    char buf[MAX];
    FILE* input = fopen(fileName, "r");

    fgets(buf, MAX, input);
    int vertice_counter = 0;
    int edge_counter = 0;

    while (buf!=NULL)
    {
        char* occurence = strtok(buf, " ");
        if (*occurence==*"v") vertice_counter++;
        if (*occurence==*"f") {
            occurence = strtok(NULL, " ");
            while (occurence!=NULL)
            {
                edge_counter++;
                occurence = strtok(NULL, " ");
            }
        }
        if (fgets(buf, MAX, input)==NULL) break;
    }
    fclose(input);
    
    result[0] = vertice_counter;
    result[1] = edge_counter;

    return result;
}

object_t *loadObject(char *fileName, double scale)
{
    int* file_info = countVerticesAndEdge(fileName);
    int n_vertice = file_info[0];
    int n_edge = file_info[1];

    double vertices[n_vertice][3];
    int edges[n_edge][2];
    int default_position[3] = {0,0,0};
    int default_rotation[3] = {0,0,0};

    char buf[MAX];
    FILE* input = fopen(fileName, "r");

    fgets(buf, MAX, input);

    int current_vertice = 0;
    int current_edge = 0;

    while (buf!=NULL)
    {
        char* occurence = strtok(buf, " ");
        if (*occurence==*"v") {
            for (int i = 0; i < 3; i++)
            {
                occurence = strtok(NULL, " ");
                vertices[current_vertice][i] = strtod(occurence, NULL)*scale;
            }
            current_vertice++;
        } else if (*occurence==*"f") {
            //WORKS ONLY FOR 4 EDGE => ADAPT FOR TRIANGLES LATER !
            int temp_edge[4];
            for (int i = 0; i < 4; i++)
            {
                occurence = strtok(NULL, " ");
                temp_edge[i] = atoi(occurence)-1;
            }
            for (int i = 0; i < 3; i++)
            {
                edges[current_edge][0] = temp_edge[i];
                edges[current_edge][1] = temp_edge[i+1];
                current_edge++;
            }
            edges[current_edge][0] = temp_edge[0];
            edges[current_edge][1] = temp_edge[3];
            current_edge++;
        }
        if (fgets(buf, MAX, input)==NULL) break;
    }
    fclose(input);

    return initialiseObject(default_position, default_rotation, vertices, n_vertice, edges, n_edge);
}
