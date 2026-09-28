#include "struct.h"

int main() {
    RBNode *root = NULL;

    // Специально подобранная последовательность:
    // 10, 20, 30 → случай 3 (прямая линия, rotate_left)
    // 15         → случай 2/3 (зигзаг)
    // 25         → случай 1 (дядя красный)
    int keys[] = {10, 20, 30, 15, 25, 5, 1, 40, 35, 50, 45, 55};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("=== Inserting keys ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- insert %d ---\n", keys[i]);
        int rc = insert(&root, keys[i]);
        if (rc != 0) {
            printf("insert failed (duplicate?)\n");
            continue;
        }
        print(root, 0);   // печатает дерево + проверки, если используете расширенный print
        int valid = is_valid_rbt(root);
        if (valid < 0) printf("ERROR");
        else printf("OK, bh: %d", valid);
    }

    int keys2[] = {10, 35, 50, 20, 15};
    int n2 = sizeof(keys2) / sizeof(keys2[0]);

    printf("=== Deletions keys ===\n");
    for (int i = 0; i < n2; i++) {
        printf("\n--- Delete %d ---\n", keys2[i]);
        int rc = delete(&root, keys2[i]);
        if (rc != 0) {
            printf("insert failed (duplicate?)\n");
            continue;
        }
        print(root, 0);   // печатает дерево + проверки, если используете расширенный print
        int valid = is_valid_rbt(root);
        if (valid < 0) printf("ERROR");
        else printf("OK, bh: %d", valid);
    }


    free_tree(root);
    return 0;
}