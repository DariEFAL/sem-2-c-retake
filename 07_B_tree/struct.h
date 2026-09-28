#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Минимальная степень дерева (t >= 2). 
// Вы можете изменить это значение по вашему усмотрению.
#define T 3 

// Максимальное количество ключей в узле: 2t - 1
#define MAX_KEYS (2 * T - 1)

// Максимальное количество дочерних указателей: 2t
#define MAX_CHILDREN (2 * T)

// Структура одного узла B-дерева
typedef struct BTreeNode {
    int n;                          // Текущее количество ключей в узле
    int keys[MAX_KEYS];             // Массив ключей (упорядочен по возрастанию)
    struct BTreeNode *c[MAX_CHILDREN]; // Массив указателей на дочерние узлы
    bool leaf;                      // Флаг: true, если узел является листом
} BTreeNode;

// Структура самого B-дерева
typedef struct BTree {
    BTreeNode *root;                // Указатель на корневой узел
} BTree;

// Объявления функций согласно книге Кормена
BTree* B_Tree_Create();
BTreeNode* B_Tree_Create_Node(bool leaf);
void B_Tree_Split_Child(BTreeNode *x, int i);
void B_Tree_Insert(BTree *T_tree, int k);
void B_Tree_Insert_Nonfull(BTreeNode *x, int k);
BTreeNode* B_Tree_Search(BTreeNode *x, int k, int *index_out);

// Вспомогательные функции для удаления и вывода
void B_Tree_Delete(BTree *T_tree, int k);
void B_Tree_Delete_Internal(BTreeNode *x, int k);
void B_Tree_Traverse(BTreeNode *x);

void B_Tree_Print(BTreeNode *x, int level);
void B_Tree_Free(BTreeNode *x);

#endif // STRUCT_H