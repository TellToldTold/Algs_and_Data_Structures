#include <stdio.h>
#include <stdlib.h>

typedef struct n_used_t {
    int n;
    struct n_used_t *next;
} n_used;

int val = 0;

int add_n(int **mat, int n, int r, int c, n_used *used_head);

int check_not_used(int number, n_used *used_head);

int mat_is_fine(int **mat, int n, int r, int c);

int row_sum(int *row, int n);

int col_sum(int **mat, int c, int n);

void print_mat(int **mat, int n);

int main() {
    int n;
    printf("Inset the side length: ");
    scanf("%d", &n);

    int **mat = (int **)calloc(n * n, sizeof(int));
    for (int i = 0; i < n; i++) {
        mat[i] = (int *)calloc(n, sizeof(int));
    }

    val = (n * ((n*n) + 1)) / 2;

    n_used *head = (n_used *)malloc(sizeof(n_used));
    head->n = 0;
    int a = add_n(mat, n, 0 , 0, head);
    print_mat(mat, n);
    return 0;
}

int add_n(int **mat, int n, int r, int c, n_used *used_head) {
    // means that the matrix is filled
    if (r == n) {
        return 1;
    }

    int new_r = r;
    int new_c = c;
    if (c == n-1) {
        new_c = 0;
        new_r = r + 1;
    } else {
        new_c = c + 1;
    }

    // scroll all possible numbers to insert
    for (int num = 1; num <= n*n ; num++) {
        // only do stuff with numbers that are not already in the matrix
        if (check_not_used(num, used_head) == 0) {
            mat[r][c] = num;
            n_used *new = (n_used *)malloc(sizeof(n_used));
            new->n = num;
            new->next = used_head;
            if (mat_is_fine(mat, n, r, c) == 1) {
                if (add_n(mat, n, new_r, new_c, new) == 1) {
                    return 1;
                }
            }
            free(new);
        }
    }

    mat[r][c] = 0;
    return 0;
}

// check if a number is already present in the matrix
int check_not_used(int number, n_used *used_head) {
    n_used *current = used_head;
    while (current->n != 0) {
        if (current->n == number) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// returns 1 if the matrix is still fine
int mat_is_fine(int **mat, int n, int r, int c) {

    if (c == n-1) {                                 // the row is complete so sum has to be the exact value
        if (row_sum(mat[r], n) != val) {
            return 0;
        }
    } else if (row_sum(mat[r], n) >= val) {     // the row is incomplete just has to be smaller than the exact value
        return 0;
    }

    if (r == n-1) {                                 // the row is complete so sum has to be the exact value
        if (col_sum(mat, c, n) != val) {
            return 0;
        }
    } else if (col_sum(mat, c, n) >= val) {         // the row is incomplete just has to be smaller than the exact value
        return 0;
    }

    if (r == n-1 && c == 0) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
           sum += mat[n-1-i][i];
        }
        if (sum != val) {
            return 0;
        }
    }

    if (r == n-1 && c == n-1) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += mat[i][i];
        }
        if (sum != val) {
            return 0;
        }
    }

    return 1;
}

int row_sum(int *row, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += row[i];
    }
    return sum;
}

int col_sum(int **mat, int c, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += mat[i][c];
    }
    return sum;
}

void print_mat(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d  ", (mat)[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}