#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct word *new_element();
int str_comp(char *f, char *s);

struct word {
    char *str;
    int occ;
    struct word *next;
};

int main() {
    FILE *f_in;
    FILE *f_out;
    struct word *head;

    f_in = fopen("../input.txt", "r");
    f_out = fopen("../output.txt", "w");

    char w[1000];
    fscanf(f_in, "%s", w);

    head = (struct word *) malloc(sizeof(struct word));
    head->str = strdup(w);
    head->next = NULL;
    head->occ = 1;

    struct word *current;
    int found;
    while (fscanf(f_in, "%s", w) != EOF) {
        current = head;
        found = 0;

        if (str_comp(w, current->str) == 1) {
            current->occ++;
            found = 1;
        }

        while (found == 0 && current->next != NULL) {
            current = current->next;
            if (str_comp(w, current->str) == 1) {
                current->occ++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            struct word *n = new_element();
            n->str = strdup(w);
            n->occ = 1;
            current->next = n;
        }
    }

    current = head;
    while (current->next != NULL) {
        fprintf(f_out, "%s: %d\n", current->str, current->occ);
        current = current->next;
    }
    fprintf(f_out, "%s: %d\n", current->str, current->occ);

    return 0;
}

struct word *new_element() {
    struct word *e_ptr;
    e_ptr = (struct word *) malloc (sizeof (struct word));
    if (e_ptr==NULL) {
        fprintf (stderr, "Memory allocation error.\n");
        return e_ptr;
    }
    return e_ptr;
}

int str_comp(char *f, char *s) {
    if (strlen(f) != strlen(s)) {
        return 0;
    }

    for (int i = 0; i < strlen(f); i++) {
        if (tolower(f[i]) != tolower(s[i])) {
            return 0;
        }
    }

    return 1;
}