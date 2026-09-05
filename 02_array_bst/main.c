#include "struct.h"

int main() {
    BinaryTree tree; 
    init(&tree);

    insert(&tree, 28); //i=0
    insert(&tree, 51); //i=2
    insert(&tree, 35); //i=5
    insert(&tree, 10); //i=1
    insert(&tree, 6); //i=3
    insert(&tree, 8); //i=8

    for (int i=0;i<2*(tree.size);i++) {
        if (is_empty(&tree, i)) printf("empty ");
        else printf("%d ", tree.data[i].value);
    }
    printf("size: %d\n", tree.size);

    insert(&tree, 42); //i=12
    insert(&tree, 48); //i=26
    insert(&tree, 15); //i=4
    insert(&tree, 2); //i=7
    insert(&tree, 40); //i=25

    for (int i=0;i<3*(tree.size);i++) {
        if (is_empty(&tree, i)) printf("empty ");
        else printf("%d ", tree.data[i].value);
    }
    printf("size: %d \n", tree.size);

    return 0;
}