#include "struct.h"

//--балансировка-----------------------------
//Когда применяется: BF < -1 и правый ребенок имеет BF <= 0 (правое-правое).
AVLNode *rotate_left(AVLNode *y) {
    if(y == NULL) return NULL;

    AVLNode *x = y->right;
    AVLNode *T2 = x->left;

    y->right = T2;
    x->left = y;

    update_height(y);
    update_height(x);

    return x;
}

//Когда применяется: BF > 1 и левый ребенок имеет BF >= 0 (левое-левое)
AVLNode *rotate_right(AVLNode *y) {
    if(y == NULL) return NULL;

    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    y->left = T2;
    x->right = y;

    update_height(y);
    update_height(x);
    
    return x;
}

//Когда применяется: BF > 1 и левый ребенок имеет BF < 0 (левое-правое).
AVLNode *rotate_left_right(AVLNode *x) {
    if(x == NULL) return NULL;
    x->left = rotate_left(x->left);
    return rotate_right(x);
}

//Когда применяется: BF < -1 и правый ребенок имеет BF > 0 (правое-левое).
AVLNode *rotate_right_left(AVLNode *x) {
    if(x == NULL) return NULL;
    x->right = rotate_right(x->right);
    return rotate_left(x);
}
