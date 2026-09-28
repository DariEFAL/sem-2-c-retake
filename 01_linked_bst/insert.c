#include "struct.h"

int insert_node(struct Node **treetop, int value) {
    if (treetop == NULL) return -1;

    /* Если ячейка пустая — выделяем память прямо здесь */
    if (*treetop == NULL) {
        *treetop = (struct Node*)malloc(sizeof(struct Node));
        if (*treetop == NULL) return -2; /* Ошибка памяти */

        (*treetop)->value = value;
        (*treetop)->left = NULL;
        (*treetop)->right = NULL;
        return 0;
    }
    
    if ((*treetop)->value == value) return 2; /* Дубликаты запрещены */

    /* Рекурсивный спуск */
    return insert_node((value < (*treetop)->value ? &((*treetop)->left) 
                                                  : &((*treetop)->right)), value);
}
