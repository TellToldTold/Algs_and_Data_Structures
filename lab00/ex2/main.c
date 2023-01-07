#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double x_a;
    double y_a;
    double x_b;
    double y_b;
    double area;
    double perimeter;
    char id[5];
} rect;

int main(int argc, char *argv[]) {
    rect *r;
    int n_rects;
    int n = 0;
    FILE *f_in;

    if (argc < 2) {
        return 1;
    }

    f_in = fopen(argv[1], "r");

    fscanf(f_in, "%d", &n_rects);
    r = (rect *) malloc(n_rects * sizeof(rect));

    char id[5];
    float x;
    float y;
    while(fscanf(f_in, "%s %f %f", id, &x, &y) != EOF) {
        int present = 0;
        for (int i = 0; i < n && present == 0; i++) {
            if (strcmp((*(r+i)).id, id) == 0) {
                present = 1;
                (*(r+i)).x_b = x;
                (*(r+i)).y_b = y;
                (*(r+i)).area = (fabs((*(r+i)).x_b - (*(r+i)).x_a) * fabs((*(r+i)).y_b - (*(r+i)).y_a));
                (*(r+i)).perimeter = fabs((*(r+i)).x_b - (*(r+i)).x_a) * 2 + fabs((*(r+i)).y_b - (*(r+i)).y_a) * 2;
            }
        }
        if (present == 0) {
            strcpy((*(r+n)).id, id);
            (*(r+n)).x_a = x;
            (*(r+n)).y_a = y;
            n++;
        }
    }

    for (int i = 0; i < n_rects; i++) {
        printf("Rect: %s  -  Area: %f  -  Perimeter: %f\n", (*(r+i)).id, (*(r+i)).area, (*(r+i)).perimeter);
    }

    return 0;
}
