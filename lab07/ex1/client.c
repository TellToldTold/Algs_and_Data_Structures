#include "treePublic.h"

#define OK 1
#define KO 0

int
main(
        void
) {
    node_t *root, *tmp;
    data_t d;
    int retValue, end = 0;
    char row[MAXC];
    FILE *fp = NULL;

    int l;
    int *levels;
    int nPaths;
    int totLength;
    int a,b;
    int dist;

    root = NULL;
    root = createEmptyTree();

    while (!end) {

        fprintf(stdout, "User selection\n");
        fprintf(stdout, "\t1) Insert one single node\n\t2) Cancel one single node\n\t3) Search a node\n");
        fprintf(stdout, "\t4) Print BST on stdout\n\t5) Write BST on file\n\t6) Read BST from file\n");
        fprintf(stdout, "\t7) Compute min and max\n\t8) End\n\t9) Count nodes\n");
        fprintf(stdout, "\t10) Count nodes in n levels\n\t11) Count paths \n\t12) Visit 2 nodes\n\t> ");
        scanf("%s", row);

        int counts[3] = {0,0,0};

        switch (atoi(row)) {

            case 1:
                fprintf(stdout, "data: ");
                retValue = readData(stdin, &d);
                if (retValue == 0) {
                    fprintf(stderr, "Input erro.\n");
                    exit(0);
                }
                root = insert(root, d);
                break;

            case 2:
                fprintf(stdout, "data: ");
                retValue = readData(stdin, &d);
                if (retValue == 0) {
                    fprintf(stderr, "Input erro.\n");
                    exit(0);
                }
                root = delete(root, d);
                break;

            case 3:
                fprintf(stdout, "data: ");
                retValue = readData(stdin, &d);
                if (retValue == 0) {
                    fprintf(stderr, "Input error.\n");
                    exit(0);
                }

                tmp = searchI(root, d);
                if (tmp != NULL) {
                    fprintf(stdout, "Iterative Search: Found -> ");
                    writeData(stdout, getData(tmp));
                } else {
                    fprintf(stdout, "Iterative Search: Not Found\n");
                }
                tmp = searchR(root, d);
                if (tmp != NULL) {
                    fprintf(stdout, "Recursive Search: Found -> ");
                    writeData(stdout, getData(tmp));
                } else {
                    fprintf(stdout, "Recursive Search: Not Found\n");
                }
                break;

            case 4:
                writeTree(stdout, root, INORDER);
                break;

            case 5:
                fprintf(stdout, "File Name: ");
                scanf("%s", row);

                if (strcmp(row, "stdout") == 0) {
                    fp = stdout;
                } else {
                    fp = fopen(row, "w");
                }

                if (fp == NULL) {
                    fprintf(stderr, "Error Opening File %s\n", row);
                    break;
                }

                writeTree(fp, root, PREORDER);

                if (strcmp(row, "stdout") != 0) {
                    fclose(fp);
                }
                break;

            case 6:
                fprintf(stdout, "File Name: ");
                scanf("%s", row);

                fp = fopen(row, "r");
                if (fp == NULL) {
                    fprintf(stderr, "Error Opening File %s\n", row);
                } else {
                    freeTree(root);
                    root = readTree(fp);
                }
                break;

            case 7:
                fprintf(stdout, "Tree minimum iterative: ");
                tmp = treeMinI(root);
                writeData(stdout, getData(tmp));
                fprintf(stdout, "Tree minimum recursive: ");
                tmp = treeMinR(root);
                writeData(stdout, getData(tmp));
                fprintf(stdout, "Tree maximum iterative: ");
                tmp = treeMaxI(root);
                writeData(stdout, getData(tmp));
                fprintf(stdout, "Tree maximum recursive: ");
                tmp = treeMaxR(root);
                writeData(stdout, getData(tmp));
                break;

            case 8:
                end = 1;
                break;

            case 9:
                countNode(root, counts);
                printf("%d %d %d\n", counts[0], counts[1], counts[2]);
                break;

            case 10:
                fprintf(stdout, "Recursion level: ");
                scanf("%d", &l);
                levels = (int *)calloc(l, sizeof(int));
                countLevel(root, levels, l);
                for (int i = 0; i < l; i++) {
                    printf("Nodes at level %d: %d\n", i, levels[i]);
                }
                break;

            case 11:
                nPaths = 0;
                totLength = 0;
                countPath(root, &nPaths, &totLength);
                printf("N of paths: %d\nTot length: %d\n", nPaths, totLength);
                break;

            case 12:
                fprintf(stdout, "Key one: ");
                scanf("%d", &a);
                fprintf(stdout, "Key two: ");
                scanf("%d", &b);
                dist = visit(root, a, b);
                printf("Distance: %d\n", dist);
                break;

            default:
                fprintf(stderr, "Unknown Option.\n");
                break;
        }
    }

    freeTree(root);

    return (OK);
}



