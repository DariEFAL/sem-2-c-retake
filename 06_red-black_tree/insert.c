#include "struct.h"

/* Создание нового красного узла */
RBNode* create(int key) {
    RBNode *new_node = (RBNode *)malloc(sizeof(RBNode));
    if (new_node == NULL) return NULL;

    new_node->color = 1; /* Вставляем всегда RED, красим в 1 */
    new_node->key = key;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

/* Балансировка после вставки */
int fix_insert(RBNode **root, RBNode *z) {
    if (root == NULL || *root == NULL || z == NULL) return -1;

    /* Пока нарушается свойство (у красного узла красный родитель) */
    while (z->parent != NULL && z->parent->color == 1) {
        RBNode *parent  = z->parent;
        RBNode *grandpa = parent->parent;

        if (grandpa == NULL) break; 

        /* СЛУЧАЙ А: Родитель является ЛЕВЫМ ребёнком дедушки */
        if (parent == grandpa->left) {
            RBNode *uncle = grandpa->right;

            if (uncle != NULL && uncle->color == 1) {
                /* Случай 1: Дядя КРАСНЫЙ -> Перекраска */
                parent->color  = 0;
                uncle->color   = 0;
                grandpa->color = 1;
                z = grandpa; /* Поднимаемся выше для проверки дедушки */
            } else {
                /* Случай 2: Дядя ЧЁРНЫЙ, z — правый ребёнок (зигзаг LR) */
                if (z == parent->right) {
                    z = parent;
                    rotate_left(root, z);
                    parent = z->parent;
                }
                /* Случай 3: Дядя ЧЁРНЫЙ, z — левый ребёнок (линия LL) */
                parent->color  = 0;
                grandpa->color = 1;
                rotate_right(root, grandpa);
            }
        } 
        /* СЛУЧАЙ Б: Родитель является ПРАВЫМ ребёнком дедушки (Симметрично) */
        else {
            RBNode *uncle = grandpa->left;

            if (uncle != NULL && uncle->color == 1) {
                /* Случай 1': Дядя КРАСНЫЙ -> Перекраска */
                parent->color  = 0;
                uncle->color   = 0;
                grandpa->color = 1;
                z = grandpa;
            } else {
                /* Случай 2': Дядя ЧЁРНЫЙ, z — левый ребёнок (зигзаг RL) */
                if (z == parent->left) {
                    z = parent;
                    rotate_right(root, z);
                    parent = z->parent;
                }
                /* Случай 3': Дядя ЧЁРНЫЙ, z — правый ребёнок (линия RR) */
                parent->color  = 0;
                grandpa->color = 1;
                rotate_left(root, grandpa);
            }
        }
    }

    (*root)->color = 0; /* Корень дерева всегда должен оставаться ЧЁРНЫМ */
    return 0;
}

/* Публичная функция вставки ключа в BST структуру */
int insert(RBNode **root, int key) {
    if (root == NULL) return -1;

    RBNode *z = create(key);
    if (z == NULL) return -1;

    if (*root == NULL) {
        z->color = 0; /* Первый узел — корень, он чёрный */
        *root = z;
        return 0;
    }

    RBNode *parent = NULL;
    RBNode *current = *root;
    while (current != NULL) {
        parent = current;
        if (key == current->key) {
            free(z);
            return 1; /* Дубликат запрещен */
        }
        current = (key < current->key) ? current->left : current->right;
    }

    z->parent = parent;
    if (key < parent->key) parent->left  = z;
    else                   parent->right = z;

    return fix_insert(root, z);
}