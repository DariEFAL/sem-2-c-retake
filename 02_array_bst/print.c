#include "struct.h"

void print_tree_structure(BinaryTree *tree, int index, int depth) {
    if (index >= MAX_SIZE || is_empty(tree, index)) return;

    print_tree_structure(tree, 2 * index + 2, depth + 1); /* Правое поддерево — сверху */

    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d (i:%d)\n", tree->data[index].value, index);

    print_tree_structure(tree, 2 * index + 1, depth + 1); /* Левое поддерево — снизу */
}