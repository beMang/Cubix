/**
 * @file matrice.h
 * @author beMang
 * @brief permet de manipuler des matrices
*/

#ifndef _MATRICE_H_
#define _MATRICE_H_

/**
 * @brief Représente une matrice
 * 
 */
typedef struct Matrice
{
    int rows;
    int cols;
    float** array;
} Matrice_t;

//INITIALISATION
Matrice_t *initialiseMatrice(int row, int cols, float default_v);
void freeMatrice(Matrice_t* matr);

//AUX
void printMatrice(Matrice_t* matr);

//OPERATIONS
void setValue(Matrice_t* m, int x, int y, float value);
int addMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);
int subMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);
int multMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);

#endif