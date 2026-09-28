#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Тип узла дерева: может быть операцией (например, '+') или числом
typedef enum { NODE_OP, NODE_NUM } NodeType;

// Структура узла двоичного дерева выражения
typedef struct Node {
    NodeType type;
    char op;            // Используется, если type == NODE_OP (+, -, *, /)
    int value;          // Используется, если type == NODE_NUM
    struct Node *left;
    struct Node *right;
} Node;

// Структура для простого стека (нужен для разбора и вычислений)
#define STACK_MAX 100
typedef struct {
    void* data[STACK_MAX];
    int top;
} Stack;

// Функции стека
void stack_init(Stack *s);
int stack_is_empty(Stack *s);
void stack_push(Stack *s, void *item);
void* stack_pop(Stack *s);

// Вспомогательные функции дерева
Node* create_num_node(int val);
Node* create_op_node(char op, Node *left, Node *right);
void free_tree(Node *root);
void print(Node *treetop, int deep);

// --- Обязательные функции по заданию ---
void print_non_terminals_lkp(Node *root);
int evaluate_tree(Node *root);
int evaluate_postfix(const char *postfix);
Node* build_tree_from_postfix(const char *postfix);
void infix_to_postfix(const char *infix, char *postfix);
void print_tree_infix(Node *root);
void print_tree_postfix(Node *root);
Node* optimize_multiply_by_one(Node *root);

#endif