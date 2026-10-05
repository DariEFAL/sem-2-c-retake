#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define V 5

// Функция для поиска вершины с минимальным ключом (весом) среди еще не включенных в MST
int minKey(int key[], int mstSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Функция для вывода построенного MST
void printMST(int parent[], int** graph) {
    int totalWeight = 0;
    printf("--- Алгоритм Прима ---\n");
    printf("Рёбра в составе MST:\n");
    for (int i = 1; i < V; i++) {
        printf("%d -- %d == %d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Общий вес MST: %d\n", totalWeight);
}

// Основная функция алгоритма Прима
void primMST(const int graph[V][V]) {
    int parent[V]; // Массив для хранения построенного MST
    int key[V];    // Ключевые значения для выбора минимального ребра
    int visited[V];  // 1, если вершина уже включена в MST, иначе 0

    // Инициализируем все ключи бесконечностью, а visited нулями
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        visited[i] = 0;
    }

    // Всегда начинаем с 0-й вершины
    key[0] = 0;     // Делаем ключ 0, чтобы эта вершина выбралась первой
    parent[0] = -1; // У первой вершины дерева нет родителя

    // Остовное дерево будет иметь ровно V вершин
    for (int count = 0; count < V - 1; count++) {
        // Выбираем вершину с минимальным ключом из множества еще не обработанных
        int u = minKey(key, visited);

        // Добавляем выбранную вершину в множество MST
        visited[u] = 1;

        // Обновляем ключи и родителей для соседних вершин выбранной вершины
        for (int v = 0; v < V; v++) {
            // Обновляем key[v], только если:
            // 1. graph[u][v] существует (не 0)
            // 2. v еще не в mstSet
            // 3. Вес ребра u-v меньше, чем текущее значение key[v]
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);

    // Освобождаем память
    free(parent);
    free(key);
    free(visited);
}

int main() {

    // Выделяем память под двумерную динамическую матрицу смежности
    /*int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)calloc(V, sizeof(int)); // Инициализируем нулями
    }*/
    int graph[V][V] = {0};

    // Заполнение матрицы смежности значениями весов (0 означает отсутствие ребра)
    graph[0][1] = 2; graph[1][0] = 2; // (A, B) = 2
    graph[0][2] = 3; graph[2][0] = 3; // (A, C) = 3
    graph[1][2] = 1; graph[2][1] = 1; // (B, C) = 1
    graph[1][3] = 4; graph[3][1] = 4; // (B, D) = 4
    graph[2][3] = 5; graph[3][2] = 5; // (C, D) = 5
    graph[2][4] = 6; graph[4][2] = 6; // (C, E) = 6
    graph[3][4] = 2; graph[4][3] = 2; // (D, E) = 2

    primMST(graph);

    // Очистка памяти матрицы
    /*for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);*/

    return 0;
}

/*
gcc prim.c -o prim
./prim
*/