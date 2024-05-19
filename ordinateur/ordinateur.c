#include <stdio.h>

#define ROWS 6
#define COLS 7

int matrix[ROWS][COLS];

void initializeMatrix() {
    // Définir les poids pour chaque position dans la matrice
    int weights[ROWS][COLS] = {
        {3, 4, 5, 7, 5, 4, 3},
        {4, 6, 8, 10, 8, 6, 4},
        {5, 8, 11, 13, 11, 8, 5},
        {5, 8, 11, 13, 11, 8, 5},
        {4, 6, 8, 10, 8, 6, 4},
        {3, 4, 5, 7, 5, 4, 3}
    };

    // Copier les poids dans la matrice
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = weights[i][j];
        }
    }
}

void printMatrix() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initializeMatrix();
    printMatrix();
    return 0;
}