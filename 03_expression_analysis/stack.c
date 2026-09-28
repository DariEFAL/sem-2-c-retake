#include "tree.h"

void stack_init(Stack *s) {
    s->top = -1;
}

int stack_is_empty(Stack *s) {
    return s->top == -1;
}

void stack_push(Stack *s, void *item) {
    if (s->top >= STACK_MAX - 1) {
        fprintf(stderr, "Ошибка: переполнение стека\n");
        exit(1);
    }
    s->data[++(s->top)] = item;
}

void* stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        fprintf(stderr, "Ошибка: стек пуст\n");
        exit(1);
    }
    return s->data[(s->top)--];
}