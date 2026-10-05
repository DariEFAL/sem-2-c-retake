#include <stdio.h>

#define INF 10000000
#define V 5

int floydWarshall(const int arr[V][V], int res[V][V]) {
    int i, j, k;

    for (i=0; i < V; i++) {
        for (j=0; j<V; j++) {
            res[i][j] = arr[i][j];
        }
    }

    for (k=0; k<V; k++) {
        for (i=0; i<V; i++) {
            for (j=0; j<V; j++) {
                if (res[i][k] != INF && res[k][j] != INF) {
                    if (res[i][k] + res[k][j] < res[i][j]) {
                        res[i][j] = res[i][k] + res[k][j];
                    }
                }
            }
        }
    }

    //проверка что нету отрицательного цикла
    for (i=0; i<V; i++) {
        if (res[i][i] < 0) return -1;
    }

    return 0;
}

int main() {
    int graph[V][V] = {0};
    graph[0][1] = 5;   // 0 -> 1 вес 5
    graph[0][3] = 10;  // 0 -> 3 вес 10
    graph[1][2] = 3;   // 1 -> 2 вес 3
    graph[2][3] = 1;   // 2 -> 3 вес 1

    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            if (i!=j && graph[i][j] == 0) graph[i][j] = INF;  
        }
    }

    int res[V][V];
    if (floydWarshall(graph, res) != 0) {
        printf("-1");
        return -1;
    }
    printf("--- Матрица кратчайших расстояний между всеми парами ---\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (res[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", res[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}