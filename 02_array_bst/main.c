#include "struct.h"

int main() {
    BinaryTree tree; 
    init(&tree);

    printf("=== Вставка элементов ===\n");
    insert(&tree, 28); 
    insert(&tree, 51); 
    insert(&tree, 35); 
    insert(&tree, 10); 
    insert(&tree, 6);  
    insert(&tree, 8);  
    insert(&tree, 42); 

    printf("\nСтруктура дерева после вставки:\n");
    print_tree_structure(&tree, 0, 0);

    printf("\nОтсортированный вывод (In-order traversal): ");
    inorder_traversal(&tree, 0);
    printf("\nКоличество элементов (size): %d\n", tree.size);

    printf("\n=== Удаление листа 8 ===\n");
    delete_value(&tree, 8);
    print_tree_structure(&tree, 0, 0);

    printf("\n=== Удаление узла 51 (с детьми) ===\n");
    delete_value(&tree, 51);
    print_tree_structure(&tree, 0, 0);

    printf("\nФинальный отсортированный вывод: ");
    inorder_traversal(&tree, 0);
    printf("\nКоличество элементов (size): %d\n", tree.size);

    return 0;
}