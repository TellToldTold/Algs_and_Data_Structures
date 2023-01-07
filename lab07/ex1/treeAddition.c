#include "treePrivate.h"

void countNode (node_t *root, int *array) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        array[0]++;
    } else{
        if (root->left != NULL && root->right != NULL){
            array[2]++;
        } else {
            array[1]++;
        }
    }
    countNode(root->left, array);
    countNode(root->right, array);
    return;
}

void countLevel (node_t * root, int *array, int l) {
    if (l == 0) {
        return;
    }
    if (root == NULL) {
        return;
    }
    array[0]++;
    countLevel(root->left, &array[1], l-1);
    countLevel(root->right, &array[1], l-1);
    return;
}

void countPath (node_t * root, int *np, int *length) {
    if (root == NULL) { // I am nothing
        return;
    }
    if (root->left == NULL && root->right == NULL) { // I am a leaf
        (*np) = 1;
        return;
    }
    int nLeft = 0;
    int nRight = 0;
    countPath(root->left, &nLeft, length);
    countPath(root->right, &nRight, length);
    (*length) += nLeft + nRight;
    (*np) = nLeft + nRight;
    return;
}

int dist (node_t *root, int key, int l) {
    printf("%d %d\n", root->val, l);
    if (root->val == key) {
        return l;
    }

    if (key < root->val) {
        return dist(root->left, key, l+1);
    } else {
        return dist(root->right, key, l+1);
    }
}

int visit (node_t *root, int key1, int key2) {
    if (root == NULL) {
        return -1;
    }

    int val = root->val;

    if (val == key1) {
        return dist(root, key2, 0);
    }

    if (val == key2) {
        return dist(root, key1, 0);
    }

    if (key1 < val && key2 < val) {
        return visit(root->left, key1, key2);
    } else if (key1 > val && key2 > val) {
        return visit(root->right, key1, key2);
    } else {
        return dist(root, key2, 0) + dist(root, key1, 0);
    }
}
