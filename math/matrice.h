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
    int** array;
} Matrice_t;

//INITIALISATION
Matrice_t* initialiseMatrice(int row, int cols, int defaut_value);
Matrice_t* squareMatrice(int size, int default_value);

//AUX
void printMatrice(Matrice_t* matr);

//OPERATIONS
void setValue(Matrice_t* m, int x, int y, int value);
Matrice_t* addMatrice(Matrice_t* m1, Matrice_t* m2);
Matrice_t* subMatrice(Matrice_t* m1, Matrice_t* m2);
Matrice_t* multMatrice(Matrice_t* m1, Matrice_t* m2);

#endif