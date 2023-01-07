#include "data.h"

int rData( FILE *fp, data_t *data) {
    char row[MAXC];
    char *res;

    res = fgets(row, MAXC, fp);
    if (res == NULL) {
        return EOF;
    }

    data->id = (char *) malloc(MAXC * sizeof(char));
    data->name = (char *) malloc(MAXC * sizeof(char));

    sscanf(row, "%s %s %d %d", data->id, data->name, &data->creditL, &data->creditP);

    return 1;
}


void writeData( FILE *fp, data_t data) {
    fprintf(fp, "%s %s %d %d\n", data.id, data.name, data.creditL, data.creditP);
    return;
}


int compare( data_t d1, data_t d2) {
    return (strcmp(d1.id, d2.id));
}

