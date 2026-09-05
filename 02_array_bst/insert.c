#include "struct.h"

int insert(BinaryTree *tree, int value) {
    if (tree == NULL) return -1;

    if (tree->size == 0) {
        (tree->data[0]).value = value;
        (tree->data[0]).occupaied = true;
        tree->size++;
        return 0;
    }

    int i = 0;
    while (i < MAX_SIZE) {
        printf("insert value %d, i: %d \n", value, i);

        if (value == (tree->data[i]).value) {
            return -3;
        }
        if (is_empty(tree, i)) {
            (tree->data[i]).value = value;
            (tree->data[i]).occupaied = true;
            tree->size++;
            return 0;
        }
        
        if (value < (tree->data[i]).value) {
            i = 2*i + 1;
        } else {
            i = 2*i + 2;
        }
    }

    return -1;
}