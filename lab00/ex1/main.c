#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int ocs;
} words_t;

int compare(char *src, char *dst);

int main(int argc, char *argv[]) {
    FILE *in_file = fopen("../input.txt", "r");
    FILE *words_file = fopen("../input2.txt", "r");

    int n;
    fscanf(words_file, "%d", &n);

    words_t *words;
    words = (words_t *)malloc(n * sizeof(words_t));

    char w[21];
    for (int i = 0; i < n; i++) {
        fscanf(words_file, "%s", w);
        words[i].word = (char *)malloc(21 * sizeof(char));
        strcpy(words[i].word, w);
        words[i].ocs = 0;
    }

    char word[21];
    while(fscanf(in_file, "%s", word) != EOF) {
        for (int i = 0; i < n; i++) {
            if (compare(word, words[i].word)) {
                words[i].ocs++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s occurances: %d \n", words[i].word, words[i].ocs);
    }

    return 0;
}

int compare(char *str1, char *str2) {
    int i;

    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

    for (i=0; i<strlen(str1); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return 0;
        }
    }

    return 1;
}
