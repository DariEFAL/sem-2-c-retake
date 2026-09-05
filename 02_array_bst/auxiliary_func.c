#include "struct.h"

//--вспомогательные функции()--------------
int init(BinaryTree *tree) {
    if (tree == NULL) return -1;

    tree->size = 0;

    for (int i = 0; i<MAX_SIZE; i++) {
        (tree->data[i]).occupaied = false;
    }

    return 0;
}

int is_empty(BinaryTree *tree, int index) {
    if (index >= MAX_SIZE) return -2;
    return !(tree->data[index]).occupaied;
}

