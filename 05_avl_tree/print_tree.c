#include "struct.h"

void print_node(AVLNode *treetop, int deep) {
    if (treetop == NULL) return;

    print_node(treetop->right, deep+1);
    for (size_t i = 0; i < deep; i++) {
        printf("    ");
    }
    printf("%d\n", treetop->value);
    print_node(treetop->left, deep+1);
}