#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *left;
    struct Node *right;
};

//------------------------------Для задания с нахождением ширины-------------------------------------------
struct QueueNode {
    struct Node *node;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front, *rear; 
    //front-первый элемент, rear-последний элент, куда добавляем;
};

//подключение функций
int create_node(struct Node **new, int value);
int insert_node(struct Node **treetop, int value);
int delete_node(struct Node **treetop, int value);
void print_node(struct Node *treetop, int deep);
void free_tree(struct Node *root);

//поиск глубины дерева
int max_depth_dfs(struct Node *top);

//поиск ширины дерева
int enqueue(struct Queue *q, struct Node *node);
int dequeue(struct Queue *q, struct Node **remote_node);
int is_queue_empty(struct Queue *q);
struct Queue *create_queue();
int max_width_bsf(struct Node *root);

#endif