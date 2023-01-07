#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 up   2 left   3 down   4 right

typedef struct path_t {
    int path_l;
    int course[100];
} path;

void readFile(char *fileName, char ***matrix, int *r, int *c, int *start_r, int *start_c) {
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%d", r);
    fscanf(fp, "%d", c);
    fscanf(fp, "%*c");

    *matrix = (char **) malloc(*r * sizeof(char *));

    for (int i = 0; i < *r; i++) {
        (*matrix)[i] = (char *) malloc(*c * sizeof(char));
        for (int j = 0; j < *c; j++) {
            fscanf(fp, "%c", &(*matrix)[i][j]);
            if ((*matrix)[i][j] == '@') {
                *start_r = i;
                *start_c = j;
            }
        }
        fscanf(fp, "%*c");
    }
}

int findOnePath(char **matrix, int r_c, int c_c) {
    if (matrix[r_c][c_c] == '#') {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%c", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }
    matrix[r_c][c_c] = '-';
    if (matrix[r_c - 1][c_c] != '*' && matrix[r_c - 1][c_c] != '-') {
        if (findOnePath(matrix, r_c - 1, c_c) == 1) {
            matrix[r_c][c_c] = ' ';
            return 1;
        }
    }
    if (matrix[r_c][c_c - 1] != '*' && matrix[r_c][c_c - 1] != '-') {
        if (findOnePath(matrix, r_c, c_c - 1) == 1) {
            matrix[r_c][c_c] = ' ';
            return 1;
        }
    }
    if (matrix[r_c + 1][c_c] != '*' && matrix[r_c + 1][c_c] != '-') {
        if (findOnePath(matrix, r_c + 1, c_c) == 1) {
            matrix[r_c][c_c] = ' ';
            return 1;
        }
    }
    if (matrix[r_c][c_c + 1] != '*' && matrix[r_c][c_c + 1] != '-') {
        if (findOnePath(matrix, r_c, c_c + 1) == 1) {
            matrix[r_c][c_c] = ' ';
            return 1;
        }
    }
    matrix[r_c][c_c] = ' ';
    return 0;
}

void findAllPaths(char **matrix, int r_c, int c_c, int *n_paths, path **paths) {
    if (matrix[r_c][c_c] == '#') {
        printf("\n");
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%c", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        *n_paths = 1;
        *paths = malloc(*n_paths * sizeof(path));
        (*paths)[0].path_l = 0;
        return;
    }

    int n_upP = 0;
    int n_leftP = 0;
    int n_downP = 0;
    int n_rightP = 0;
    path *upP;
    path *leftP;
    path *downP;
    path *rightP;

    matrix[r_c][c_c] = '-';
    if (matrix[r_c - 1][c_c] != '*' && matrix[r_c - 1][c_c] != '-') {
        findAllPaths(matrix, r_c - 1, c_c, &n_upP, &upP);
        *n_paths += n_upP;
    }
    if (matrix[r_c][c_c - 1] != '*' && matrix[r_c][c_c - 1] != '-') {
        findAllPaths(matrix, r_c, c_c - 1, &n_leftP, &leftP);
        *n_paths += n_leftP;
    }
    if (matrix[r_c + 1][c_c] != '*' && matrix[r_c + 1][c_c] != '-') {
        findAllPaths(matrix, r_c + 1, c_c, &n_downP, &downP);
        *n_paths += n_downP;
    }
    if (matrix[r_c][c_c + 1] != '*' && matrix[r_c][c_c + 1] != '-') {
        findAllPaths(matrix, r_c, c_c + 1, &n_rightP, &rightP);
        *n_paths += n_rightP;
    }

    matrix[r_c][c_c] = ' ';
    if (*n_paths > 0) {
        *paths = malloc(*n_paths * sizeof(path));
        int c = 0;
        for (int i = 0; i < n_upP; i++) {
            upP[i].course[upP[i].path_l] = 1;
            upP[i].path_l++;
            (*paths)[c] = upP[i];
            c++;
        }
        for (int i = 0; i < n_leftP; i++) {
            leftP[i].course[leftP[i].path_l] = 2;
            leftP[i].path_l++;
            (*paths)[c] = leftP[i];
            c++;
        }
        for (int i = 0; i < n_downP; i++) {
            downP[i].course[downP[i].path_l] = 3;
            downP[i].path_l++;
            (*paths)[c] = downP[i];
            c++;
        }
        for (int i = 0; i < n_rightP; i++) {
            rightP[i].course[rightP[i].path_l] = 4;
            rightP[i].path_l++;
            (*paths)[c] = rightP[i];
            c++;
        }
        return;
    }

    *n_paths = 0;
    return;
}

void findBestPath(char **matrix, int r, int c, int n_paths, path **paths) {
    path min_p = (*paths)[0];
    for (int i = 1; i < n_paths; i++) {
        path current_p = (*paths)[i];
        if (current_p.path_l < min_p.path_l) {
            min_p = current_p;
        }
    }

    for (int i = 0; i < min_p.path_l; i++) {
        if (min_p.course[min_p.path_l - i] == 1) {
            r--;
            matrix[r][c] = '-';
        } else if (min_p.course[min_p.path_l - i] == 2) {
            c--;
            matrix[r][c] = '-';
        } else if (min_p.course[min_p.path_l - i] == 3) {
            r++;
            matrix[r][c] = '-';
        } else if (min_p.course[min_p.path_l - i] == 4) {
            c++;
            matrix[r][c] = '-';
        }
    }
}

int main() {
    char **labMatrix;
    int r, c;
    int start_r, start_c;
    readFile("../input.txt", &labMatrix, &r, &c, &start_r, &start_c);

    // 1
    printf("----------------- 1 --------------\n");
    findOnePath(labMatrix, start_r, start_c);
    labMatrix[start_r][start_c] = '@';

    // 2
    printf("\n----------------- 2 --------------\n");
    int n_paths = 0;
    path **paths = malloc(sizeof(path *));
    findAllPaths(labMatrix, start_r, start_c, &n_paths, paths);
    labMatrix[start_r][start_c] = '@';


    // 3
    printf("\n----------------- 3 --------------\n");
    findBestPath(labMatrix, start_r, start_c, n_paths, paths);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%c", labMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
