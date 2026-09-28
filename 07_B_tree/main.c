#include "struct.h"

int main() {
    BTree *tree = B_Tree_Create();
    
    // Заполняем дерево числами
    int items[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 4, 8, 9};
    int n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++) {
        B_Tree_Insert(tree, items[i]);
        printf("--- insert in B-дерево  %d ---\n", items[i]);
        // Визуализируем структуру дерева
        B_Tree_Print(tree->root, 0);
        printf("----------------------------------------\n\n");
    }

    printf("--- insert in B-дерево ---\n");
    // Визуализируем структуру дерева
    B_Tree_Print(tree->root, 0);
    printf("----------------------------------------\n\n");

    // Выполняем операции удаления, если нужно...
    printf("Удаляем ключ 10...\n");
    B_Tree_Delete(tree, 10);
    
    printf("\n--- Структура после удаления ---\n");
    B_Tree_Print(tree->root, 0);
    printf("--------------------------------\n\n");

    // --- Очистка памяти перед завершением процесса ---
    printf("Освобождение памяти всей структуры...\n");
    B_Tree_Free(tree->root); // Освобождаем все узлы дерева
    free(tree);             // Освобождаем саму обертку дерева
    
    printf("Память успешно очищена. Программа завершена.\n");
    return 0;
}