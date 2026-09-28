#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Функция для поиска необработанной вершины с минимальным расстоянием
int minDistance(int V, int dist[], int visited[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Функция для вывода массивов расстояний и путей
void printSolution(int V, int dist[], int parent[], int src) {
    printf("--- Результаты алгоритма Дейкстры (Старт из %d) ---\n", src);
    printf("Вершина \t Расстояние от источника \t Родитель\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("%d \t\t Недостижима \t\t -\n", i);
        } else {
            printf("%d \t\t %d \t\t\t\t %d\n", i, dist[i], parent[i]);
        }
    }
}

// Основная функция алгоритма Дейкстры
void dijkstra(int V, int** graph, int src) {
    int* dist = (int*)malloc(V * sizeof(int));    // Выходной массив кратчайших расстояний
    int* visited = (int*)malloc(V * sizeof(int)); // Массив флагов посещенных/обработанных вершин
    int* parent = (int*)malloc(V * sizeof(int));  // Массив для восстановления самого пути

    // Инициализация исходных массивов
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    // Расстояние от вершины до самой себя всегда равно 0
    dist[src] = 0;

    // Поиск кратчайшего пути для всех V вершин
    for (int count = 0; count < V - 1; count++) {
        // Выбираем вершину с минимальным расстоянием из набора еще не обработанных
        int u = minDistance(V, dist, visited);

        // Если minDistance вернул -1, значит оставшиеся вершины недостижимы из src
        if (u == -1) break;

        // Помечаем выбранную вершину как обработанную
        visited[u] = 1;

        // Обновляем dist[v] для соседних вершин выбранной вершины `u`
        for (int v = 0; v < V; v++) {
            // Условия релаксации:
            // 1. Вершина v еще не обработана (visited[v] == 0)
            // 2. Есть ребро из u в v (graph[u][v] != 0)
            // 3. Путь до u в принципе существует (dist[u] != INF)
            // 4. Суммарный вес пути через u меньше текущего значения dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Запоминаем, что в v мы пришли из u
            }
        }
    }

    printSolution(V, dist, parent, src);

    // Освобождение динамической памяти
    free(dist);
    free(visited);
    free(parent);
}

int main() {
    int V = 5;

    // Выделяем память под двумерную матрицу смежности графа
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)calloc(V, sizeof(int));
    }

    // Заполнение графа (тот же тестовый набор весов рёбер)
    graph[0][1] = 2; graph[1][0] = 2;
    graph[0][2] = 3; graph[2][0] = 3;
    graph[1][2] = 1; graph[2][1] = 1;
    graph[1][3] = 4; graph[3][1] = 4;
    graph[2][3] = 5; graph[3][2] = 5;
    graph[2][4] = 6; graph[4][2] = 6;
    graph[3][4] = 2; graph[4][3] = 2;

    // Запуск алгоритма из стартовой вершины 0 (A)
    dijkstra(V, graph, 0);

    // Освобождение памяти матрицы
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}

/*
gcc dijkstra.c -o dijkstra
./dijkstra
*/

/*
С матрицей смежности и линейным поиском (как в коде выше): 
Сложность составляет O(V^2). Мы V раз ищем минимум среди всех вершин графа. 
Это оптимально для плотных графов. 
С очередью с приоритетами (кучей) и списком смежности: 
Сложность падает до O(Elog V). 
Поиск минимума в куче занимает O(log V), и мы делаем это для каждого ребра. Это идеальный вариант для разреженных графов (где рёбер мало). 
*/