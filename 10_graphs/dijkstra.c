#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define V 5
#define E 7 // Количество рёбер (для примера)

struct Edge {
    int src;
    int dest;
    int weight;
};

void convertToMatrix(struct Edge edges[], int edge_count, int graph[V][V]) {
    // 1. Инициализируем матрицу нулями (или INF, если у тебя нет путей)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0; // В твоей реализации Дейкстры 0 означает "нет ребра"
        }
    }

    // 2. Переносим рёбра из списка в матрицу
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        
        graph[u][v] = w; // Для ориентированного графа пишем ТОЛЬКО сюда
        // Если бы граф был НЕориентированным, мы бы дописали: graph[v][u] = w;
    }
}


int minDistance(const int res[V], const int visited[V]) {
    //нужно вернуть индекс вершины с минимальным растоянием и непосещенную
    //следовательно работаем с res, visited
    int min = INF, min_index = -1, j;
    for (j=0; j<V; j++) {
        if (visited[j] == 0 && res[j] < min) {
            min = res[j];
            min_index = j;
        }
    }
    return min_index;
}

int dijkstra(const int arr[V][V], int res[V], int parent[V], int src) {
    //происходит работа с тремя массивами res, visited, parent + исходная матрица смежности + нужна стартовая вершина
    //в исходной матрице 0 если нету ребра, и вес если есть
    int j, count;
    int visited[V];

    for (j=0; j<V; j++) {
        res[j] = INF;
        parent[j] = -1;
        visited[j] = 0;
    }

    res[src] = 0;

    for (count=0; count<V-1; count++) {
        int min_i = minDistance(res, visited);
        if (min_i == -1) break; //больше из стартовой вершины попасть никуда нельзя

        visited[min_i] = 1;

        for (j=0; j<V; j++) {
            if (visited[j] == 0 && arr[min_i][j] != 0 && res[min_i] + arr[min_i][j] < res[j]) {
                res[j] = res[min_i] + arr[min_i][j];
                parent[j] = min_i;
            }
        }
    }

    return 0;
}

int main() {
    int graph[V][V] = {0};
    graph[0][1] = 5;   // 0 -> 1 вес 5
    graph[0][3] = 10;  // 0 -> 3 вес 10
    graph[1][2] = 3;   // 1 -> 2 вес 3
    graph[2][3] = 1;   // 2 -> 3 вес 1

    struct Edge edges[E] = {
        {0, 1, 5}, {0, 3, 10}, {1, 2, 3}, {2, 3, 1}
    };

    convertToMatrix(edges, 4, graph); //

    int res[V], parent[V];
    int src = 0;

    dijkstra(graph, res, parent, src);

    printf("--- Результаты алгоритма Дейкстры (Старт из %d) ---\n", src);
    printf("Вершина \t Расстояние от источника \t Родитель\n");
    for (int i = 0; i < V; i++) {
        if (res[i] == INF) {
            printf("%d \t\t Недостижима \t\t -\n", i);
        } else {
            printf("%d \t\t %d \t\t\t\t %d\n", i, res[i], parent[i]);
        }
    }
}

/*
Вершина          Расстояние от источника         Родитель
0                0                               -1
1                5                               0
2                8                               1
3                9                               2
4                Недостижима             -
*/

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