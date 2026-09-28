#include "struct.h"

//обход в ширину. Работает на очереде, 
//поэтому для очереди надо реализовать команды: create_queue, enqueue, dequeue, пустая ли очередь

int enqueue(struct Queue *q, struct Node *node) {
    if (q == NULL || node == NULL) return -1;

    struct QueueNode *new_node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (new_node == NULL) return -2; 
    new_node->node = node;
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return 0;
    }
    q->rear->next = new_node;
    q->rear = new_node;

    return 0;
}

int dequeue(struct Queue *q, struct Node **remote_node) {
    if (q == NULL || remote_node == NULL || q->front == NULL) return 3;

    struct QueueNode *temp = q->front;
    *remote_node = temp->node;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);

    return 0;
}

int is_queue_empty(struct Queue *q) {
    return (q == NULL || q->front == NULL) ? 1 : 0;
}

struct Queue *create_queue() {
    struct Queue *new_q = (struct Queue*)malloc(sizeof(struct Queue));
    if (new_q == NULL) return NULL; 
    new_q->front = new_q->rear = NULL;
    return new_q;
}

int max_width_bsf(struct Node *root) {
    if (root == NULL) return 0;

    struct Queue *q = create_queue();
    if (q == NULL) return -1;

    enqueue(q, root);
    int max_width = 0;

    while (!is_queue_empty(q)) {
        int level_size = 0;

        /* Считаем количество элементов на текущем уровне */
        struct QueueNode *temp = q->front;
        while (temp != NULL) {
            level_size++;
            temp = temp->next;
        }

        max_width = (level_size > max_width ? level_size : max_width);

        /* Проходим по всем элементам уровня и добавляем их детей */
        for (int i = 0; i < level_size; i++) {
            struct Node *current = NULL;
            int error = dequeue(q, &current);
            if (error != 0) {
                free(q); /* ФИКС: освобождаем память перед аварийным выходом */
                return error;
            }

            if (current->left != NULL)  enqueue(q, current->left);
            if (current->right != NULL) enqueue(q, current->right);
        }
    }
    
    free(q); /* Освобождаем память структуры очереди */
    return max_width;
}
