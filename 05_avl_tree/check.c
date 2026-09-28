#include "struct.h"
#include <stdlib.h>

/* Проверка сбалансированности факторов и корректности высот */
int is_valid_avl(AVLNode *root) {
    if (root == NULL) return 1;

    int left_h = height(root->left);
    int right_h = height(root->right);

    /* Проверяем, что сохраненная высота соответствует реальной */
    int real_h = (left_h > right_h ? left_h : right_h) + 1;
    if (root->height != real_h) {
        printf("[Ошибка АВЛ] Неверно сохранена высота у узла %d (ожидалось %d, записано %d)\n", 
               root->key, real_h, root->height);
        return 0;
    }

    /* Проверяем баланс-фактор */
    int bf = left_h - right_h;
    if (bf < -1 || bf > 1) {
        printf("[Ошибка АВЛ] Нарушен баланс у узла %d (BF = %d)\n", root->key, bf);
        return 0;
    }

    /* Рекурсивно проверяем детей */
    return is_valid_avl(root->left) && is_valid_avl(root->right);
}