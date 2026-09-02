#include "struct.h"

void free_tree(struct Node *root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}