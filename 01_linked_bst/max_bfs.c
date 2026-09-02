#include "struct.h"

//обход в ширину. Работает на очереде, 
//поэтому для очереди надо реализовать команды: create_queue, enqueue, dequeue, пустая ли очередь

int enqueue(struct Queue *q, struct Node *node) {
    if (node == NULL) return -1;

    struct QueueNode *new = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (new == NULL) return -2; //memory error
    new->node = node;
    new->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new;
        return 0;
    }
    q->rear->next = new;
    q->rear = new;

    return 0;
}

int dequeue(struct Queue *q, struct Node **remote_node) {
    if (remote_node == NULL) return -1;
    if (q == NULL  || *remote_node != NULL || q->front == NULL) return 3;

    struct QueueNode *temp = q->front;
    *remote_node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);

    return 0;
}

int is_queue_empty(struct Queue *q) {
    return (q->front == NULL ? 1 : 0);
}

struct Queue *create_queue() {
    struct Queue *new = (struct Queue*)malloc(sizeof(struct Queue));
    if (new == NULL) return NULL; //memory error
    new->front = new->rear = NULL;
    return new;
}


int max_width_bsf(struct Node *root) {
    if (root == NULL) return 0;

    struct Queue *q = create_queue();
    if (q == NULL) return -1;

    enqueue(q, root);
    int max_width = 0;

    while (!is_queue_empty(q)) {
        int level_size = 0;

        //считаем количество элементов на уровне
        struct QueueNode *temp = q->front;
        while (temp != NULL) {
            level_size++;
            temp = temp->next;
        }

        //меняем максимальную ширину
        max_width = (level_size > max_width ? level_size : max_width);

        //проходимся по всем элементам и заменяем их на их детей
        for (int i=0;i<level_size;i++) {
            struct Node *current = NULL;
            int error = dequeue(q, &current);
            if (error != 0) return error;

            if (current->left != NULL) enqueue(q, current->left);
            if (current->right != NULL) enqueue(q, current->right);
        }
    }
    free(q);
    return max_width;
}
