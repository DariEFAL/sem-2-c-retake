#include <stdio.h>
#include <stdlib.h>

// Структура для представления ребра графа
typedef struct {
    int src, dest, weight;
} Edge;

// Структура для подмножеств в СНМ (Disjoint Set Union)
typedef struct {
    int parent;
    int rank;
} Subset;

// Функция сравнения рёбер по весу для qsort
int compareEdges(const void* a, const void* b) {
    Edge* a_edge = (Edge*)a;
    Edge* b_edge = (Edge*)b;
    return a_edge->weight - b_edge->weight;
}

// Функция СНМ: Поиск корня множества (с оптимизацией сжатия путей)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Функция СНМ: Объединение двух множеств (по рангу)
// Возвращает 1, если объединение произошло успешно, и 0, если вершины уже в одном множестве (цикл)
int unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (xroot != yroot) {
        if (subsets[xroot].rank < subsets[yroot].rank) {
            subsets[xroot].parent = yroot;
        } else if (subsets[xroot].rank > subsets[yroot].rank) {
            subsets[yroot].parent = xroot;
        } else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
        return 1; 
    }
    return 0; 
}

// Основная функция алгоритма Краскала
void kruskalMST(int V, int E, Edge edges[]) {
    // Выделяем память под массив для хранения ребер минимального остова
    Edge* result = (Edge*)malloc((V - 1) * sizeof(Edge));
    int resultCount = 0; // Индекс для ребер в результирующем дереве
    int totalWeight = 0; // Общий вес MST

    // Шаг 1: Сортируем все рёбра графа по возрастанию веса O(E log E)
    qsort(edges, E, sizeof(Edge), compareEdges);

    // Выделяем память для СНМ
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Шаг 2: Перебираем отсортированные рёбра
    for (int i = 0; i < E && resultCount < V - 1; i++) {
        Edge next_edge = edges[i];

        // Проверяем, создаёт ли текущее ребро цикл
        if (unionSets(subsets, next_edge.src, next_edge.dest)) {
            result[resultCount++] = next_edge;
            totalWeight += next_edge.weight;
        }
    }

    // Вывод результатов
    printf("--- Алгоритм Краскала ---\n");
    printf("Рёбра в составе MST:\n");
    for (int i = 0; i < resultCount; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }
    printf("Общий вес MST: %d\n", totalWeight);

    // Освобождаем память
    free(subsets);
    free(result);
}

int main() {
    int V = 5; // Количество вершин (0=A, 1=B, 2=C, 3=D, 4=E)
    int E = 7; // Количество рёбер

    // Создаем массив всех рёбер графа
    Edge edges[] = {
        {0, 1, 2}, // (A, B) = 2
        {0, 2, 3}, // (A, C) = 3
        {1, 2, 1}, // (B, C) = 1
        {1, 3, 4}, // (B, D) = 4
        {2, 3, 5}, // (C, D) = 5
        {2, 4, 6}, // (C, E) = 6
        {3, 4, 2}  // (D, E) = 2
    };

    kruskalMST(V, E, edges);
    return 0;
}

/*
gcc kruskal.c -o kruskal
./kruskal
*/
