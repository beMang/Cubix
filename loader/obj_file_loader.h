#include <stdlib.h>
#include <string.h>
#include "../rendering/object.h"

#ifndef _OBJ_FILE_LOADER_H_
#define _OBJ_FILE_LOADER_H_

/**
 * @brief compte le nombre de vertices d'un fichier obj
 * 
 * @param fileName le fichier à analyser
 * @return int le nombre de vertice
 */
int* countVerticesAndEdge(char* fileName);

/**
 * @brief charge un objet avec un fichier obj
 * 
 * @param fileName 
 * @return object_t* 
 */
object_t* loadObject(char* fileName, double scale);

#endif