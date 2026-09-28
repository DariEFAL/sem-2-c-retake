#include "tree.h"

// Создание листа (числа)
Node* create_num_node(int val) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->type = NODE_NUM;
    n->value = val;
    n->left = n->right = NULL;
    return n;
}

// Создание внутреннего узла (операции)
Node* create_op_node(char op, Node *left, Node *right) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->type = NODE_OP;
    n->op = op;
    n->left = left;
    n->right = right;
    return n;
}

// Очистка памяти дерева
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// 1. Печать нетерминальных (внутренних) узлов в порядке ЛКП (In-order)
void print_non_terminals_lkp(Node *root) {
    if (!root) return;
    print_non_terminals_lkp(root->left);  // Лево (Л)
    
    // Корень (К): если у узла есть хотя бы один потомок, он нетерминальный
    if (root->left || root->right) {
        if (root->type == NODE_OP) printf("%c ", root->op);
        else printf("%d ", root->value);
    }
    
    print_non_terminals_lkp(root->right); // Право (П)
}

// 2. Вычисление значения арифметического выражения по дереву
int evaluate_tree(Node *root) {
    if (!root) return 0;
    if (root->type == NODE_NUM) return root->value; // Лист
    
    int left_val = evaluate_tree(root->left);
    int right_val = evaluate_tree(root->right);
    
    switch (root->op) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': 
            if (right_val == 0) { printf("Ошибка: деление на ноль\n"); exit(1); }
            return left_val / right_val;
    }
    return 0;
}

// 3. Вычисление значения выражения по постфиксной записи (символы-цифры 0-9)
int evaluate_postfix(const char *postfix) {
    Stack s;
    stack_init(&s);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            // Кладём число в стек (приводим char к int через указатель)
            long val = ch - '0';
            stack_push(&s, (void*)val);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            long op2 = (long)stack_pop(&s);
            long op1 = (long)stack_pop(&s);
            long res = 0;
            if (ch == '+') res = op1 + op2;
            else if (ch == '-') res = op1 - op2;
            else if (ch == '*') res = op1 * op2;
            else if (ch == '/') res = op1 / op2;
            stack_push(&s, (void*)res);
        }
    }
    return (int)(long)stack_pop(&s);
}

// 4. Построение дерева арифметического выражения по постфиксной записи
Node* build_tree_from_postfix(const char *postfix) {
    Stack s;
    stack_init(&s);
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            stack_push(&s, create_num_node(ch - '0'));
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            Node *right = (Node*)stack_pop(&s);
            Node *left = (Node*)stack_pop(&s);
            stack_push(&s, create_op_node(ch, left, right));
        }
    }
    return (Node*)stack_pop(&s);
}

// Вспомогательная функция приоритета операторов
int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 5. Преобразование инфиксной записи в постфиксную (Алгоритм сортировочной станции)
void infix_to_postfix(const char *infix, char *postfix) {
    Stack s;
    stack_init(&s);
    int j = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            stack_push(&s, (void*)(long)ch);
        } else if (ch == ')') {
            char top_ch = (char)(long)stack_pop(&s);
            while (top_ch != '(') {
                postfix[j++] = top_ch;
                top_ch = (char)(long)stack_pop(&s);
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack_is_empty(&s) && 
                   get_precedence((char)(long)s.data[s.top]) >= get_precedence(ch)) {
                postfix[j++] = (char)(long)stack_pop(&s);
            }
            stack_push(&s, (void*)(long)ch);
        }
    }
    while (!stack_is_empty(&s)) {
        postfix[j++] = (char)(long)stack_pop(&s);
    }
    postfix[j] = '\0';
}

// 6. Печать дерева выражения в инфиксной форме со скобками
void print_tree_infix(Node *root) {
    if (!root) return;
    if (root->type == NODE_NUM) {
        printf("%d", root->value);
        return;
    }
    printf("(");
    print_tree_infix(root->left);
    printf("%c", root->op);
    print_tree_infix(root->right);
    printf(")");
}

// 7. Печать дерева выражения в постфиксной записи
void print_tree_postfix(Node *root) {
    if (!root) return;
    print_tree_postfix(root->left);
    print_tree_postfix(root->right);
    if (root->type == NODE_NUM) printf("%d", root->value);
    else printf("%c", root->op);
}

// 8. Замена всех подвыражений x * 1 и 1 * x на x
Node* optimize_multiply_by_one(Node *root) {
    if (!root) return NULL;
    
    // Сначала оптимизируем поддеревья
    root->left = optimize_multiply_by_one(root->left);
    root->right = optimize_multiply_by_one(root->right);
    
    // Если текущий узел — умножение
    if (root->type == NODE_OP && root->op == '*') {
        // Проверяем случай: Левый * 1
        if (root->right && root->right->type == NODE_NUM && root->right->value == 1) {
            Node *left_subtree = root->left;
            free(root->right); // Удаляем узел единицы
            free(root);        // Удаляем сам узел '*'
            return left_subtree;
        }
        // Проверяем случай: 1 * Правый
        if (root->left && root->left->type == NODE_NUM && root->left->value == 1) {
            Node *right_subtree = root->right;
            free(root->left);  // Удаляем узел единицы
            free(root);        // Удаляем сам узел '*'
            return right_subtree;
        }
    }
    return root;
}