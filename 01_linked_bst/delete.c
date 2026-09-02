#include "struct.h"

int delete_node(struct Node **treetop, int value) {
     if (treetop == NULL || *treetop == NULL) return -1;

     if ((*treetop)->value == value) {
        if ((*treetop)->left == NULL && (*treetop)->right == NULL) {
            free(*treetop);
            *treetop = NULL;
            return 0;
        }
        else if ((*treetop)->right == NULL) {
            struct Node *new = (*treetop)->left;
            free(*treetop);
            *treetop = new;
            return 0;
        }
        else if ((*treetop)->left == NULL) {
            struct Node *new = (*treetop)->right;
            free(*treetop);
            *treetop = new;
            return 0;
        }

        struct Node *right_tree = (*treetop)->right;

        while (right_tree->left != NULL) {
            right_tree = right_tree->left;
        }

        (*treetop)->value = right_tree->value;
        return delete_node(&((*treetop)->right), right_tree->value);;
     }
     return delete_node((value < (*treetop)->value ? &((*treetop)->left) : &((*treetop)->right)), value);
}