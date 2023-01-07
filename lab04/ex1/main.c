#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct product_t {
    struct product_t *next;
    char *id;
    char *name;
    int price;
} product;

typedef struct producer_t {
    struct producer_t *next;
    char *manufacturer;
    char *id;
    product *products;
} producer;

producer *get_new_producer(char *line);
product *get_new_product(char *line);

int main() {
    FILE *f_producer = fopen("../producer", "r");
    FILE *f_product = fopen("../product", "r");
    producer *head;
    producer *current;
    char line[1000];

    // reading
    fgets(line, 1000, f_producer);
    head = get_new_producer(line);
    while (fgets(line, 1000, f_producer) != NULL) {
        producer *new_producer = get_new_producer(line);
        new_producer->next = head;
        head = new_producer;
    }

    while (fgets(line, 1000, f_product) != NULL) {
        product *new_product = get_new_product(line);
        current = head;
        while (current != NULL) {
            if (strcmp(current->id, new_product->id) == 0) {
                if (current->products == NULL) {
                    current->products = new_product;
                } else {
                    new_product->next = current->products;
                    current->products = new_product;
                }
                break;
            }
            current = current->next;
        }
    }

    // printing
    current = head;
    while (current != NULL) {
        printf("\n%s %s: \n", current->manufacturer, current->id);
        product *c = current->products;
        while (c != NULL) {
            printf("    %s %s %d: \n", c->name, c->id, c->price);
            c = c->next;
        }
        current = current->next;
    }

    return 0;
}

producer *get_new_producer(char *line) {
    producer *new = malloc(sizeof(producer));
    char manuf[100], id[100];
    sscanf(line, "%s %s", manuf, id);
    new->manufacturer = strdup(manuf);
    new->id = strdup(id);
    new->next = NULL;
    new->products = NULL;
    return new;
}

product *get_new_product(char *line) {
    product *new = malloc(sizeof(product));
    char name[100], id[100];
    int price;
    sscanf(line, "%s %s %i", id, name, &price);
    new->name = strdup(name);
    new->id = strdup(id);
    new->price = price;
    new->next = NULL;
    return new;
}