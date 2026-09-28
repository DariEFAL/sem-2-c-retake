#include <stdio.h>
#include "tree.h"

int main() {
    printf("=== 1. Инфиксная запись -> Постфиксная ===\n");
    const char *infix = "1+(2*3)";
    char postfix[100];
    infix_to_postfix(infix, postfix);
    printf("Инфикс: %s\nПостфикс: %s\n\n", infix, postfix);

    printf("=== 2. Вычисление по постфиксной записи ===\n");
    int res_post = evaluate_postfix(postfix);
    printf("Результат вычисления '%s' = %d\n\n", postfix, res_post);

    printf("=== 3. Построение дерева по постфиксной записи ===\n");
    Node *root = build_tree_from_postfix(postfix);
    print(root, 0);
    printf("Дерево построено успешно.\n\n");

    printf("=== 4. Печать нетерминальных узлов (ЛКП) ===\n");
    printf("Нетерминалы: ");
    print_non_terminals_lkp(root);
    printf("\n\n");

    printf("=== 5. Вычисление значения по дереву ===\n");
    printf("Результат по дереву = %d\n\n", evaluate_tree(root));

    printf("=== 6. Печать дерева в инфиксной и постфиксной форме ===\n");
    printf("Инфиксная форма: "); print_tree_infix(root); printf("\n");
    printf("Постфиксная форма: "); print_tree_postfix(root); printf("\n\n");
    free_tree(root);

    printf("=== 7. Оптимизация дерева (выражение: 5 * 1) ===\n");
    // Вручную соберем дерево для 5 * 1
    Node *expr = create_op_node('*', create_num_node(5), create_num_node(1));
    printf("До оптимизации: "); print_tree_infix(expr); printf("\n");
    
    expr = optimize_multiply_by_one(expr);
    printf("После оптимизации: "); print_tree_infix(expr); printf("\n");

    free_tree(expr);
    return 0;
}