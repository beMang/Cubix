#include "../math/matrice.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    Matrice_t* result;

    Matrice_t* m1 = initialiseMatrice(4,4, 0);
    for (int i = 0; i < m1->rows; i++)
    {
        m1->array[i][i] = i+1;
    }
    
    printMatrice(m1);
    Matrice_t* double_m1;
    addMatrice(m1, m1, &double_m1);
    printMatrice(double_m1);

    multMatrice(m1, double_m1, &result);
    printMatrice(result);

    freeMatrice(result);
    freeMatrice(double_m1);
    freeMatrice(m1);

    Matrice_t* M1 = initialiseMatrice(2, 3, 0);
    Matrice_t* M2 = initialiseMatrice(3,2,0);

    M1->array[0][0] = 1;
    M1->array[0][1] = 2;
    M1->array[0][2] = 3;
    M1->array[1][0] = 4;
    M1->array[1][1] = 5;
    M1->array[1][2] = 6;
    printMatrice(M1);

    M2->array[0][0] = 7;
    M2->array[0][1] = 8;
    M2->array[1][0] = 9;
    M2->array[1][1] = -1;
    M2->array[2][0] = -2;
    M2->array[2][1] = -3;
    printMatrice(M2);

    multMatrice(M1, M2, &result);
    printMatrice(result);

    freeMatrice(result);

    Matrice_t* M3 = initialiseMatrice(50,3,0);
    if(multMatrice(M1, M3, &result)==-1) printf("Wrong dimension is okay\n");

    freeMatrice(M1);
    freeMatrice(M2);
    freeMatrice(M3);

    //ROTATIONS_TESTS
    double angle = 0.7853;

    Matrice_t* rotationX = rotationX_matrix(angle);
    Matrice_t* rotationY = rotationY_matrix(angle);
    Matrice_t* rotationZ = rotationZ_matrix(angle);

    printMatrice(rotationX);
    printMatrice(rotationY);
    printMatrice(rotationZ);

    freeMatrice(rotationX);
    freeMatrice(rotationY);
    freeMatrice(rotationZ);

    return 0;
}
