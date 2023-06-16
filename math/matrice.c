#include "matrice.h"
#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

Matrice_t *initialiseMatrice(int row, int cols, int defaut_value)
{
    Matrice_t* result = malloc(sizeof(Matrice_t));
    if (result==NULL) return NULL;

    result->cols = cols;
    result->rows = row;

    result->array = (int**) malloc(sizeof(int*)*row);
    if(result->array==NULL) return NULL;
    for (int i = 0; i < row; i++)
    {
        result->array[i] = (int*) malloc(sizeof(int)*cols);
        for (int j = 0; j < cols; j++)
        {
            result->array[i][j] = defaut_value;
        }
        
    }
    return result;
}

Matrice_t *squareMatrice(int size, int default_value)
{
    return initialiseMatrice(size, size, default_value);
}

void printMatrice(Matrice_t *matr)
{
    if(matr==NULL || matr->rows==0 || matr->cols==0) {
        printf("Empty matrice\n");
        return;
    }
    printf("Nbr de ligne : %d - Nbr de colonne : %d \n", matr->rows, matr->cols);
    for (int i = 0; i < matr->rows; i++)
    {
        printf("[ ");
        for (int j = 0; j < matr->cols; j++)
        {
            printf("%d ", matr->array[i][j]);
        }
        printf("]\n");
    }
}

void setValue(Matrice_t *m, int x, int y, int value)
{
    if (x<0 || y<0 || x>=m->rows || y>=m->cols)
    {
        printf("Error, wrong coordinates\n");
        return;
    } else {
        m->array[x][y] = value;
    }
}

bool checkConditionForAddition(Matrice_t* m1, Matrice_t* m2)
{
    return (m1->rows==m2->rows && m1->cols==m2->cols) ? true : false;
}

Matrice_t *operationOnMatrice(Matrice_t *m1, Matrice_t *m2, int (*f)(int a, int b))
{
    if (!checkConditionForAddition(m1, m2)) return NULL;
    Matrice_t* result = initialiseMatrice(m1->rows, m2->cols, 0);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->array[i][j] = f(m1->array[i][j], m2->array[i][j]);
        }
    }
    return result;
}

Matrice_t *addMatrice(Matrice_t *m1, Matrice_t *m2)
{
    return operationOnMatrice(m1, m2, add);
}

Matrice_t *subMatrice(Matrice_t *m1, Matrice_t *m2)
{
    return operationOnMatrice(m1, m2, sub);
}

bool checkConditionForMultiplication(Matrice_t* m1, Matrice_t* m2){
    return (m1->cols==m2->rows) ? true : false;
}

Matrice_t* multMatrice(Matrice_t *m1, Matrice_t *m2)
{
    if (checkConditionForMultiplication(m1, m2)==false) return NULL;

    Matrice_t* result = initialiseMatrice(m1->rows, m2->cols, 0);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            int entry = 0;
            for (int k = 0; k < m1->cols; k++)
            {
                entry+=m1->array[i][k]*m2->array[k][j];
            }
            result->array[i][j] = entry;
        }
    }
    return result;
}
