#include <stdio.h>
#include <stdlib.h>

#define V 4 // Возьмем для примера граф из 4 вершин

// Функция для перемножения двух матриц: C = A * B
void multiplyMatrices(int A[V][V], int B[V][V], int C[V][V]) {
    int temp[V][V] = {0}; // Используем временную матрицу, чтобы можно было умножать саму на себя A = A * A

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            for (int l = 0; l < V; l++) {
                temp[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    // Копируем результат в результирующую матрицу C
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            C[i][j] = temp[i][j];
        }
    }
}

// ОСНОВНАЯ ФУНКЦИЯ ИЗ БИЛЕТА
// Подсчет количества уникальных простых циклов длины k
int countCyclesOfLengthK(int adjMatrix[V][V], int k) {
    if (k <= 0) return 0;

    int resultMatrix[V][V];
    int baseMatrix[V][V];

    // Инициализируем базовую и результирующую матрицы копией матрицы смежности (степень 1)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            baseMatrix[i][j] = adjMatrix[i][j];
            resultMatrix[i][j] = adjMatrix[i][j];
        }
    }

    // Возводим матрицу смежности в степень k
    // Нам нужно сделать (k - 1) умножений, чтобы получить A^k
    for (int step = 1; step < k; step++) {
        multiplyMatrices(resultMatrix, baseMatrix, resultMatrix);
    }

    // Значение в ячейке [s][t] — это и есть количество путей из s в t длины ровно k
    //return resultMatrix[s][t];
    
    // Считаем след результирующей матрицы A^k (сумма элементов на главной диагонали)
    int trace = 0;
    for (int i = 0; i < V; i++) {
        trace += resultMatrix[i][i];
    }

    // Каждый цикл длины k посчитан ровно k раз (сдвинутый по фазе для каждой вершины цикла).
    // Разделим на k, чтобы получить количество уникальных простых циклов.
    return trace / k;
}

int main() {
    // Пример графа с циклом длины 3: 0 -> 1 -> 2 -> 0
    // И одной вершиной-аппендиксом: 2 -> 3
    int graph[V][V] = {
        {0, 1, 0, 0}, // 0 -> 1
        {0, 0, 1, 0}, // 1 -> 2
        {1, 0, 0, 1}, // 2 -> 0  и  2 -> 3
        {0, 0, 0, 0}  // Из 3 никуда нет путей
    };

    int k = 3;
    int cyclesCount = countCyclesOfLengthK(graph, k);

    printf("Количество циклов длины %d в ориентированном графе: %d\n", k, cyclesCount);

    return 0;
}

/*
gcc count_cycles.c -o count_cycles
./count_cycles
*/