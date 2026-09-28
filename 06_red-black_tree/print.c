#include "struct.h"

void print(RBNode *root, int depth) {
    if (root == NULL) return;
    
    print(root->right, depth + 1);   // правое поддерево — сверху
    
    for (int i = 0; i < depth; i++)
        printf("    ");                   // отступ по глубине
    
    printf("%s%d%s (%s)\n",
           root->color == 1 ? "\033[31m" : "\033[30m",  // красный/чёрный
           root->key,
           "\033[0m",                                     // сброс цвета
           root->color == 1 ? "R" : "B");
    
    print(root->left, depth + 1);    // левое поддерево — снизу
}