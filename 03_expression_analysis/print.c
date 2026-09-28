#include "tree.h"

void print(Node *treetop, int deep) {
    if (treetop == NULL) return;

    print(treetop->right, deep+1);
    for (size_t i = 0; i < deep; i++) {
        printf("    ");
    }
    if (treetop->type == NODE_NUM) printf("%d\n", treetop->value);
    else printf("%c\n", treetop->op);
    print(treetop->left, deep+1);
}