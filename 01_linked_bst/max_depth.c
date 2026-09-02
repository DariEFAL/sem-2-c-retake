#include "struct.h"

//height by vertex
int max_depth_dfs(struct Node *top) {
    if (top == NULL) return 0;
    
    int right = max_depth_dfs(top->right);
    int left = max_depth_dfs(top->left);

    return (right < left ? left : right) + 1;
}