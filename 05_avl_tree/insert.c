#include "struct.h"

//--вставка----------------------------------
int insert_avl(AVLNode **root, int key, int value) {
    if (root == NULL) return -1;

    if (*root == NULL) {
        AVLNode *new = create_avl_node(key, value);
        if (new == NULL) return -2;
        *root = new;
        return 0;
    } 
    else if ((*root)->key == key) {
        (*root)->value = value;
        return 0;
    }

    int exit = insert_avl((
                key < (*root)->key 
                ? &((*root)->left) 
                : &((*root)->right)), key, value);
    
    update_height(*root);
    int bf = balance_factor(*root);
    
    if (bf < -1 && balance_factor((*root)->right) <= 0) *root = rotate_left(*root);
    else if (bf > 1 && balance_factor((*root)->left) >= 0) *root = rotate_right(*root);
    else if (bf > 1 && balance_factor((*root)->left) < 0) *root = rotate_left_right(*root);
    else if (bf < -1 && balance_factor((*root)->right) > 0) *root = rotate_right_left(*root);

    return exit;
}