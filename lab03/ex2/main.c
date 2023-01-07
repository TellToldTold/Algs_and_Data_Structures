#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee{
    int salary;
    char date_hiring[11];
    char id[17];
    char name[1000];
    struct employee *next;
    struct employee *prev;
} employee;

employee *new_employee();

int main() {
    FILE *f_in;
    char *arg1 = "Giallo_Antonio\0";
    char *arg2 = "---+";
    employee *head;
    employee *new;

    f_in = fopen("../input.txt", "r");

    char *line = malloc(1000 * sizeof(char));
    fgets(line, 1000, f_in);
    head = new_employee();
    head->prev = head;
    sscanf(line, "%s %s %s %d", head->name, head->id, head->date_hiring, &head->salary);

    while (fgets(line, 1000, f_in) != NULL) {
        new = new_employee();
        new->next = head;
        new->prev = head->prev;
        head->prev = new;
        head = new;
        sscanf(line, "%s %s %s %d", head->name, head->id, head->date_hiring, &head->salary);
    }
    new->prev->next = new;

    employee *current = head;
    while (current->next != head) {
        if (strcmp(current->name, arg1) == 0) {
            printf("%s %s %s %d\n\n", current->name, current->id, current->date_hiring, current->salary);
            break;
        }
        current = current->next;
    }
    for (int i = 0; i < strlen(arg2); i++) {
        if (arg2[i] == '-') {
            current = current->prev;
        } else if (arg2[i] == '+') {
            current = current->next;
        }
        printf("%s %s %s %d\n", current->name, current->id, current->date_hiring, current->salary);
    }
    return 0;
}

employee *new_employee() {
    employee *new;
    new = malloc(sizeof(employee));
    return new;
}