#include "struct.h"

// Создание B-дерева. Соответствует процедуре B-TREE-CREATE(T) из книги.
BTree* B_Tree_Create() {
    BTree *tree = (BTree*)malloc(sizeof(BTree)); // Выделяем память под саму структуру дерева
    tree->root = B_Tree_Create_Node(true);       // Изначально корень — это пустой узел-лист
    return tree;
}

// Выделение памяти под один узел. Аналог ALLOCATE-NODE() у Кормена.
BTreeNode* B_Tree_Create_Node(bool leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->n = 0;          // Новый узел пока не содержит ключей
    node->leaf = leaf;    // Устанавливаем флаг, является ли узел листом
    
    // Зануляем все указатели на будущих детей, чтобы избежать "диких" указателей
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->c[i] = NULL;
    }
    return node;
}

// Симметричный обход дерева (In-order). Выводит все ключи строго по возрастанию.
void B_Tree_Traverse(BTreeNode *x) {
    if (x != NULL) {
        int i;
        // Проходим по всем ключам текущего узла
        for (i = 0; i < x->n; i++) {
            // Если узел внутренний, сначала рекурсивно выводим всё левое поддерево
            if (!x->leaf) {
                B_Tree_Traverse(x->c[i]);
            }
            // Выводим сам разделяющий ключ
            printf("%d ", x->keys[i]);
        }
        // Не забываем посетить самое последнее (правое) поддерево
        if (!x->leaf) {
            B_Tree_Traverse(x->c[i]);
        }
    }
}


