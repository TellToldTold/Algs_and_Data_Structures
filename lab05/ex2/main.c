#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void recursive_bits(int **mat, int n, int c);

void print_mat(int **mat, int n);

int main() {
    int n;
    int **mat;
    printf("Give me a number: ");
    scanf("%d", &n);

    mat = (int **)calloc(n * pow(2, n), sizeof(int));

    for (int i = 0; i < n; i++) {
        mat[i] = (int *)calloc(pow(2, n), sizeof(int));
    }
    mat[0][1] = 1;
    recursive_bits(mat, n, 1);

    print_mat(mat, n);

    return 0;
}

void recursive_bits(int **mat, int n, int c) {
    if (c == n) {
        return;
    }

    int p = pow(2, c + 1);

    // flip stuff
    for (int j = 0; j < p / 2; j++) {
        for (int i = 0; i < c; i++) {
            mat[i][j + (p / 2)] = mat[i][(p / 2) -1 - j];
        }
        mat[c][j] = 0;
        mat[c][j+ (p / 2)] = 1;
    }

    return recursive_bits(mat, n, c+1);
}

void print_mat(int **mat, int n) {
    for(int j = 0; j < pow(2,n); j++) {
        for (int i = n-1; i >= 0; i--) {
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}