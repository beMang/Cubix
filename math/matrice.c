#include "matrice.h"
#include "operation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

Matrice_t *initialiseMatrice(int row, int cols, double default_v)
{
    Matrice_t* result = malloc(sizeof(Matrice_t));
    if (result==NULL) return NULL;

    result->cols = cols;
    result->rows = row;

    result->array = (double**) malloc(sizeof(double*)*row);
    if(result->array==NULL) return NULL;
    for (int i = 0; i < row; i++)
    {
        result->array[i] = (double*) calloc(cols, sizeof(double));
        for (int j= 0; j < cols; j++)
        {
            result->array[i][j] = default_v;
        }
        
    }
    return result;
}

void freeMatrice(Matrice_t* matr)
{
    for (int i = 0; i < matr->rows; i++)
    {
        free(matr->array[i]);
    }
    free(matr->array);
    free(matr);
}

int copyMatrice(Matrice_t *dest, Matrice_t *src)
{
    dest = initialiseMatrice(src->rows, src->cols, 0);
    if (dest==NULL) return -1;

    for (int i = 0; i < dest->cols; i++)
    {
        for (int j = 0; j < dest->rows; j++)
        {
            dest->array[i][j] = src->array[i][j];
        }
    }
    return 0;
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
            printf("%9.2f ", matr->array[i][j]);
        }
        printf("]\n");
    }
}

void setValue(Matrice_t *m, int x, int y, double value)
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

int operationOnMatrice(Matrice_t *m1, Matrice_t *m2, double (*f)(double a, double b), Matrice_t** result)
{
    if (!checkConditionForAddition(m1, m2)) return -1;
    *result = initialiseMatrice(m1->rows, m2->cols, 0);
    for (int i = 0; i < (*result)->rows; i++)
    {
        for (int j = 0; j < (*result)->cols; j++)
        {
            (*result)->array[i][j] = f(m1->array[i][j], m2->array[i][j]);
        }
    }
    return 0;
}

int addMatrice(Matrice_t *m1, Matrice_t *m2, Matrice_t** result)
{
    return operationOnMatrice(m1, m2, add, result);
}

int subMatrice(Matrice_t *m1, Matrice_t *m2, Matrice_t** result)
{
    return operationOnMatrice(m1, m2, sub, result);
}

bool checkConditionForMultiplication(Matrice_t* m1, Matrice_t* m2){
    return (m1->cols==m2->rows) ? true : false;
}

int multMatrice(Matrice_t *m1, Matrice_t *m2, Matrice_t** result)
{
    if (checkConditionForMultiplication(m1, m2)==false) return -1;

    *result = initialiseMatrice(m1->rows, m2->cols, 0);
    for (int i = 0; i < (*result)->rows; i++)
    {
        for (int j = 0; j < (*result)->cols; j++)
        {
            double entry = 0;
            for (int k = 0; k < m1->cols; k++)
            {
                entry+=m1->array[i][k]*m2->array[k][j];
            }
            (*result)->array[i][j] = entry;
        }
    }
    return 0;
}

Matrice_t *identity_matrix(int size)
{
    Matrice_t* idendity = initialiseMatrice(size, size, 0);
    if (idendity==NULL) return NULL;
    for (int i = 0; i < size; i++)
    {
        idendity->array[i][i] = 1;
    }
    return idendity;
}

Matrice_t *rotationX_matrix(double angle)
{
    Matrice_t* rotation = initialiseMatrice(3, 3, 0);
    if (rotation==NULL) return NULL;

    rotation->array[0][0] = 1.0;
    rotation->array[2][1] = sin(angle);
    rotation->array[1][1] = cos(angle);
    rotation->array[1][2] = -sin(angle);
    rotation->array[2][2] = cos(angle);

    return rotation;
}


Matrice_t *rotationY_matrix(double angle)
{
    Matrice_t* rotation = initialiseMatrice(3, 3, 0);
    if (rotation==NULL) return NULL;

    rotation->array[0][0] = cos(angle);
    rotation->array[0][2] = sin(angle);
    rotation->array[1][1] = 1.0;
    rotation->array[2][0] = -sin(angle);
    rotation->array[2][2] = cos(angle);

    return rotation;
}

Matrice_t *rotationZ_matrix(double angle)
{
    Matrice_t* rotation = initialiseMatrice(3, 3, 0);
    if (rotation==NULL) return NULL;

    rotation->array[0][0] = cos(angle);
    rotation->array[0][1] = -sin(angle);
    rotation->array[2][2] = 1.0;
    rotation->array[1][0] = sin(angle);
    rotation->array[1][1] = cos(angle);

    return rotation;
}

