#include "struct.h"

RBNode* find_node(RBNode *root, int key) {
    while (root != NULL) {
        if (key == root->key) return root;
        root = (key < root->key) ? root->left : root->right;
    }
    return NULL;
}

/* Поиск минимального (самого левого) узла в поддереве */
RBNode* minimum(RBNode *root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

/* Пересадка поддеревьев: заменяет узел u на узел v */
void transplant(RBNode **root, RBNode *u, RBNode *v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

/* ================================================================
 *  fix_delete
 *  ----------
 *  Восстанавливает баланс черной высоты после удаления ЧЁРНОГО узла.
 * ================================================================ */
void fix_delete(RBNode **root, RBNode *x, RBNode *x_parent) {
    while (x != *root && (x == NULL || x->color == 0)) {
        
        /* 
         * БЕЗОПАСНОЕ ОПРЕДЕЛЕНИЕ СТОРОНЫ (Защита от x == NULL):
         * Если x существует, мы точно знаем его сторону: (x == x_parent->left).
         * Если x равен NULL, то смотрим, с какой стороны от x_parent остался пустой слот.
         */
        int left_side = 0;
        if (x != NULL) {
            left_side = (x == x_parent->left);
        } else {
            if (x_parent->left == NULL && x_parent->right != NULL) left_side = 1;
            else if (x_parent->right == NULL && x_parent->left != NULL) left_side = 0;
            else left_side = 1; /* Если оба ребенка NULL, дефолтно считаем левым слотом */
        }

        RBNode *w = left_side ? x_parent->right : x_parent->left; /* Брат узла x */

        /* --- Случай 1: Брат w КРАСНЫЙ --- */
        if (w != NULL && w->color == 1) {
            w->color = 0;
            x_parent->color = 1;
            if (left_side) rotate_left(root, x_parent);
            else           rotate_right(root, x_parent);
            w = left_side ? x_parent->right : x_parent->left; /* Обновляем структуру брата */
        }

        /* --- Случай 2: Брат w ЧЁРНЫЙ, и оба его ребёнка тоже ЧЁРНЫЕ (или NULL) --- */
        if (w == NULL || 
            ((w->left == NULL || w->left->color == 0) &&
             (w->right == NULL || w->right->color == 0))) {
            if (w != NULL) w->color = 1; /* Окрашиваем брата в КРАСНЫЙ */
            x = x_parent;                /* Поднимаем двойную черноту к родителю */
            x_parent = x->parent;
        }
        else {
            /* --- Случай 3: Брат w ЧЁРНЫЙ, у него есть хотя бы один КРАСНЫЙ ребёнок --- */
            if (left_side) {
                /* Подслучай 3a (внутренний внук красный, внешний черный) -> сводим к 3b */
                if (w->right == NULL || w->right->color == 0) {
                    if (w->left) w->left->color = 0;
                    w->color = 1;
                    rotate_right(root, w);
                    w = x_parent->right;
                }
                /* Подслучай 3b (внешний внук красный) */
                w->color = x_parent->color;
                x_parent->color = 0;
                if (w->right) w->right->color = 0; /* ФИКС: Красим внешний узел в ЧЁРНЫЙ */
                rotate_left(root, x_parent);
            } 
            /* Симметричная ситуация для правой стороны */
            else {
                /* Подслучай 3a' */
                if (w->left == NULL || w->left->color == 0) {
                    if (w->right) w->right->color = 0;
                    w->color = 1;
                    rotate_left(root, w);
                    w = x_parent->left;
                }
                /* Подслучай 3b' */
                w->color = x_parent->color;
                x_parent->color = 0;
                if (w->left) w->left->color = 0;
                rotate_right(root, x_parent);
            }
            x = *root; /* Балансировка завершена, перенаправляем на выход */
            break;
        }
    }
    if (x != NULL)
        x->color = 0; /* Удаляем лишнюю черноту, окрашивая в чистый черный */
}

/* ================================================================
 *  delete_node
 *  -----------
 *  Удаляет физический узел из памяти и перестраивает дерево.
 * ================================================================ */
void delete_node(RBNode **root, RBNode *z) {
    if (root == NULL || *root == NULL || z == NULL) return;

    RBNode *y = z;                       /* Узел, который физически исчезнет или переместится */
    int y_original_color = y->color;     /* Запоминаем его исходный цвет */
    RBNode *x = NULL;                    /* Ребёнок, занимающий место y */
    RBNode *x_parent = NULL;             /* Будущий родитель для x */

    /* Случай 1: Нет левого ребенка */
    if (z->left == NULL) {
        x = z->right;
        x_parent = z->parent;
        transplant(root, z, z->right);
    }
    /* Случай 2: Нет правого ребенка */
    else if (z->right == NULL) {
        x = z->left;
        x_parent = z->parent;
        transplant(root, z, z->left);
    }
    /* Случай 3: Есть оба ребенка */
    else {
        y = minimum(z->right);           /* Преемник (самый левый узел справа) */
        y_original_color = y->color;
        x = y->right;                    /* Запоминаем правого ребенка преемника */

        if (y->parent == z) {
            x_parent = y;                /* Так как y встанет на место z, он станет родителем для x */
        } else {
            x_parent = y->parent;        /* Родителем x временно становится родитель y */
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);          /* y занимает место удаляемого z */
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;             /* y полностью наследует цвет удаленного z */
    }

    /* Если физически удаленный/смещенный узел y был ЧЁРНЫМ, нарушена черная высота */
    if (y_original_color == 0) {
        fix_delete(root, x, x_parent);
    }

    free(z); /* Безопасно освобождаем память удаленного элемента */
}

/* Публичная обёртка удаления по ключу */
int delete(RBNode **root, int key) {
    RBNode *z = find_node(*root, key);
    if (z == NULL) return -1; /* Узел не найден */
    delete_node(root, z);
    return 0;
}