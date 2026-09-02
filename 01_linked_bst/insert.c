#include "struct.h"

int create_node(struct Node **new, int value) {
    if (new == NULL) return -1; //error: **node cannot be equal NULL
    if (*new != NULL) return 1; //error: it is only possible to create a new node in an empty cell

    *new = (struct Node*)malloc(sizeof(struct Node));
    if (*new == NULL) return -2; //memory error

    (*new)->value = value;
    (*new)->left = NULL;
    (*new)->right = NULL;

    return 0; //success
}
 
int insert_node(struct Node **treetop, int value) {
    if (treetop == NULL) return -1;

    if (*treetop == NULL) {
        struct Node *new = NULL;
        int error = create_node(&new, value);
        if (error != 0) return error;
        *treetop = new;
        return 0;
    }
    else if ((*treetop)->value == value) return 2; //error: no duplicates
    return insert_node((value < (*treetop)->value ? &((*treetop)->left) 
                                                  : &((*treetop)->right)), value);
}
