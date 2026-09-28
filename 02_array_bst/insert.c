#include "struct.h"

int insert(BinaryTree *tree, int value) {
    if (tree == NULL) return -1;

    /* Если дерево пустое, занимаем корень дерева (индекс 0) */
    if (tree->size == 0) {
        tree->data[0].value = value;
        tree->data[0].occupaied = true;
        tree->size = 1;
        return 0;
    }

    int i = 0;
    while (i < MAX_SIZE) {
        /* Если нашли дубликат, возвращаем ошибку */
        if (tree->data[i].value == value) {
            return -3; 
        }

        /* Двигаемся влево или вправо в зависимости от значения */
        if (value < tree->data[i].value) {
            int next_index = 2 * i + 1;
            if (next_index >= MAX_SIZE) return -2; /* Переполнение массива */
            
            if (is_empty(tree, next_index)) {
                tree->data[next_index].value = value;
                tree->data[next_index].occupaied = true;
                tree->size++;
                return 0;
            }
            i = next_index;
        } else {
            int next_index = 2 * i + 2;
            if (next_index >= MAX_SIZE) return -2; /* Переполнение массива */
            
            if (is_empty(tree, next_index)) {
                tree->data[next_index].value = value;
                tree->data[next_index].occupaied = true;
                tree->size++;
                return 0;
            }
            i = next_index;
        }
    }

    return -2; /* Выход за пределы MAX_SIZE */
}