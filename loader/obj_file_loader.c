#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj_file_loader.h"
#include "../rendering/object.h"

#define MAX 100

int* countVerticesAndFaces(char *fileName)
{
    int* result = malloc(2*sizeof(int));

    char buf[MAX];
    FILE* input = fopen(fileName, "r");

    fgets(buf, MAX, input);
    int vertice_counter = 0;
    int face_counter = 0;

    while (buf!=NULL)
    {
        char* occurence = strtok(buf, " ");
        if (*occurence==*"v") vertice_counter++;
        if (*occurence==*"f") {
            face_counter++;
        }
        if (fgets(buf, MAX, input)==NULL) break;
    }
    fclose(input);
    
    result[0] = vertice_counter;
    result[1] = face_counter;

    return result;
}

object_t *loadObject(char *fileName, double scale)
{
    int* file_info = countVerticesAndFaces(fileName);
    int n_vertice = file_info[0];
    int n_faces = file_info[1];
    free(file_info);

    printf("Number of faces : %d\n", n_faces);

    double vertices[n_vertice][3];
    face_t** faces = malloc(sizeof(face_t*)*n_faces);
    for (int i = 0; i < n_faces; i++)
    {
        faces[i] = NULL;
    }

    int default_position[3] = {0,0,0};
    int default_rotation[3] = {0,0,0};

    char buf[MAX];
    FILE* input = fopen(fileName, "r");

    fgets(buf, MAX, input);

    int current_vertice = 0;
    int current_face = 0;

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
            int buffer_size = 6;
            int temp_edge[buffer_size]; //faces with max 5 vertices
            int n_vertices = 0;
            for (int i = 0; i < buffer_size; i++)
            {
                occurence = strtok(NULL, " ");
                if(occurence==NULL) break;
                temp_edge[i] = atoi(occurence)-1;
                n_vertices++;
            }
            faces[current_face] = makeFace(temp_edge, n_vertices);
            current_face++;
        }
        if (fgets(buf, MAX, input)==NULL) break;
    }
    fclose(input);
    return initialiseObject(default_position, default_rotation, vertices, n_vertice, faces, n_faces);
}
