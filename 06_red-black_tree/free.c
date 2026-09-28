#include "struct.h"

void free_tree(RBNode *root) {
    if (root == NULL) return;

    free_tree(root->right);
    free_tree(root->left);
    
    free(root);
}