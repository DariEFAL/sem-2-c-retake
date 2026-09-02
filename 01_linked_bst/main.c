#include "struct.h"

int main() {
    struct Node *treetop = NULL;
    printf("width: %d\n--------------------", max_width_bsf(treetop));

    insert_node(&treetop, 26);
    insert_node(&treetop, 10);
    insert_node(&treetop, 6);
    insert_node(&treetop, 13);
    insert_node(&treetop, 57);
    insert_node(&treetop, 60);
    printf("width: %d\n--------------------", max_width_bsf(treetop));

    insert_node(&treetop, 55);
    insert_node(&treetop, 44);
    insert_node(&treetop, 33);
    insert_node(&treetop, 37);
    print_node(treetop, 0);
    printf("---------------------------\n");

    delete_node(&treetop, 26);
    print_node(treetop, 0);
    printf("---------------------------\n");
    
    printf("height: %d\n", max_depth_dfs(treetop));
    printf("width: %d\n", max_width_bsf(treetop));

    free_tree(treetop);
    treetop = NULL;
    return 0;
}