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
    double** array;
} Matrice_t;

//INITIALISATION
Matrice_t *initialiseMatrice(int row, int cols, double default_v);
void freeMatrice(Matrice_t* matr);

int copyMatrice(Matrice_t* dest, Matrice_t* src);

//AUX
void printMatrice(Matrice_t* matr);

//OPERATIONS
void setValue(Matrice_t* m, int x, int y, double value);
int addMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);
int subMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);
int multMatrice(Matrice_t* m1, Matrice_t* m2, Matrice_t** result);

//BASIC MATRICES
Matrice_t* identity_matrix(int size);
Matrice_t* rotationX_matrix(double angle);
Matrice_t* rotationY_matrix(double angle);
Matrice_t* rotationZ_matrix(double angle);

#endif