#include "struct.h"

/* Вспомогательная функция: копирует поддерево из старого индекса в новый */
void move_subtree(BinaryTree *tree, int from_index, int to_index) {
    if (from_index >= MAX_SIZE) return;

    /* Если старый узел пуст, то и новый слот очищаем */
    if (is_empty(tree, from_index)) {
        if (to_index < MAX_SIZE) {
            tree->data[to_index].occupaied = false;
        }
        return;
    }

    /* Проверка на случай выхода за границы нового индекса */
    if (to_index >= MAX_SIZE) {
        printf("[Ошибка] Переполнение при перемещении поддерева!\n");
        return;
    }

    /* Копируем данные текущего узла */
    tree->data[to_index].value = tree->data[from_index].value;
    tree->data[to_index].occupaied = true;
    
    /* Освобождаем старое место */
    tree->data[from_index].occupaied = false;

    /* Рекурсивно переносим левых и правых детей */
    move_subtree(tree, 2 * from_index + 1, 2 * to_index + 1);
    move_subtree(tree, 2 * from_index + 2, 2 * to_index + 2);
}

/* Основная функция удаления */
int delete_value(BinaryTree *tree, int value) {
    if (tree == NULL || tree->size == 0) return -1;

    /* Шаг 1: Ищем индекс узла с искомым значением */
    int i = 0;
    int target_index = -1;
    
    /* Простой проход по заполненным ячейкам для поиска ключа */
    for (int idx = 0; idx < MAX_SIZE; idx++) {
        if (!is_empty(tree, idx) && tree->data[idx].value == value) {
            target_index = idx;
            break;
        }
    }

    if (target_index == -1) return -1; /* Узел не найден */

    int left = 2 * target_index + 1;
    int right = 2 * target_index + 2;

    /* Случай 1: У узла нет детей (лист) */
    if (is_empty(tree, left) && is_empty(tree, right)) {
        tree->data[target_index].occupaied = false;
    }
    /* Случай 2: Есть только левый ребёнок */
    else if (is_empty(tree, right)) {
        move_subtree(tree, left, target_index);
    }
    /* Случай 3: Есть только правый ребёнок */
    else if (is_empty(tree, left)) {
        move_subtree(tree, right, target_index);
    }
    /* Случай 4: Есть оба ребёнка */
    else {
        /* Ищем самый левый узел в правом поддереве (преемник) */
        int successor_idx = right;
        while (!is_empty(tree, 2 * successor_idx + 1)) {
            successor_idx = 2 * successor_idx + 1;
        }

        /* Сохраняем значение преемника */
        int successor_value = tree->data[successor_idx].value;

        /* Рекурсивно удаляем преемника с его старого места */
        delete_value(tree, successor_value);

        /* Записываем значение преемника в текущий удаляемый узел */
        tree->data[target_index].value = successor_value;
        tree->data[target_index].occupaied = true;
        
        tree->size--; /* Компенсируем инкремент от рекурсивного вызова */
    }

    tree->size--;
    return 0;
}