#include <stdio.h>
#include "treePublic.h"
#include "st.h"
#include "treePrivate.h"

void inOrderInsertion(ST *hashTB, node_t *n);

int main() {
    char fileOne[20];
    char fileTwo[20];
    FILE *fOne, *fTwo;
    ST hashTb;
    node_t *bst;

    printf("Enter first file name: ");
    scanf("%s", fileOne);

    fOne = fopen("../input.txt","r");
    fTwo = fopen("../output.txt","w");
    bst = readTree(fOne);
    hashTb = STinit(-1);
    inOrderInsertion(&hashTb, bst);

    STprint(hashTb, fTwo);

    link *l = listUnique(hashTb);
    for (int i = 0; i < 15; i++) {
        printf("%s %d\n", l[i]->item->id, getLevel(bst, *l[i]->item));
    }

    return 0;
}

void inOrderInsertion(ST *hashTB, node_t *n) {
    if (n == NULL) {
        return;
    }

    inOrderInsertion(hashTB, n->left);
    STinsert(*hashTB, &n->val);
    inOrderInsertion(hashTB, n->right);
}

