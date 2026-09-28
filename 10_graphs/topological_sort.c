#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 7  // Количество вершин (не менее 7 по условию)
#define E 8  // Количество рёбер

// Структура для представления ребра (Список рёбер)
typedef struct {
    int src;  // Откуда выходит ребро source 
    int dest; // Куда входит ребро destination
} Edge;

// Функция построения матрицы инцидентности по списку рёбер
// Для ориентированного графа: из какой вершины выходит = -1, в какую входит = 1
void buildIncidenceMatrix(Edge edges[], int incMatrix[V][E]) {
    // Сначала полностью обнуляем матрицу
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            incMatrix[i][j] = 0;
        }
    }
    // Заполняем столбцы (каждый столбец j — это ребро edges[j])
    for (int j = 0; j < E; j++) {
        int src = edges[j].src;
        int dest = edges[j].dest;
        //проверка, что не входит сама в себя
        if (src == dest) incMatrix[src][j] = 2;
        else {
            incMatrix[src][j] = -1; // Ребро выходит из src
            incMatrix[dest][j] = 1;  // Ребро входит в dest
        }
    }
}

// ФУНКЦИЯ ТОПОЛОГИЧЕСКОЙ СОРТИРОВКИ (АЛГОРИТМ КАНА)
void kahnsTopologicalSort(int adjMatrix[V][V]) {
    int in_degree[V] = {0}; // Массив для хранения полустепеней захода (сколько стрелок входит)
    int result[V];          // Массив для хранения финального порядка вершин
    int result_count = 0;   // Счётчик элементов в результате

    // Шаг 1: Подсчитываем, сколько стрелок входит в каждую вершину
    // Мы смотрим на матрицу смежности: если adjMatrix[i][j] == 1, значит в 'j' входит стрелка
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjMatrix[i][j] == 1) {
                in_degree[j]++;
            }
        }
    }

    // Шаг 2: Создаём простую очередь (массив) для вершин, у которых in_degree == 0
    // (в них не входит ни одна стрелка, с них можно начинать)
    int queue[V];
    int head = 0; // Указатель на начало очереди
    int tail = 0; // Указатель на конец очереди

    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0) {
            queue[tail] = i;
            tail++;
        }
    }

    printf("\n--- ПОШАГОВОЕ ВЫПОЛНЕНИЕ АЛГОРИТМА КАНА ---\n");
    printf("Стартовые вершины, в которые никто не входит: ");
    for(int i = head; i < tail; i++) printf("%d ", queue[i]);
    printf("\n");

    // Шаг 3: Основной цикл алгоритма
    while (head < tail) {
        // Достаём вершину из начала очереди
        int u = queue[head];
        head++;

        // Записываем её в итоговый результат
        result[result_count] = u;
        result_count++;

        printf("Взяли вершину %d. Удаляем её связи... ", u);

        // Смотрим на всех «соседей», в которых вели стрелки из вершины u
        for (int v = 0; v < V; v++) {
            if (adjMatrix[u][v] == 1) {
                in_degree[v]--; // «Стираем» стрелку u -> v, уменьшая счётчик соседа

                // Если у соседа больше не осталось входящих стрелок, отправляем его в очередь
                if (in_degree[v] == 0) {
                    queue[tail] = v;
                    tail++;
                    printf("(вершина %d готова, добавлена в очередь) ", v);
                }
            }
        }
        printf("\n");
    }

    // Шаг 4: Проверка на циклы
    // Если мы обработали МЕНЬШЕ вершин, чем всего есть в графе, значит где-то был цикл!
    if (result_count != V) {
        printf("\n[Ошибка]: Обнаружен цикл! Топологическая сортировка невозможна.\n");
        return;
    }

    // Шаг 5: Вывод финального корректного порядка
    printf("\n--- РЕЗУЛЬТАТ ТОПОЛОГИЧЕСКОЙ СОРТИРОВКИ (АЛГОРИТМ КАНА) ---\n");
    for (int i = 0; i < V; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    // --- 1. СПИСОК ВЕРШИН ---
    printf("--- СПИСОК ВЕРШИН ---\n");
    for (int i = 0; i < V; i++) {
        printf("Вершина %d\n", i);
    }

    // --- 2. СПИСОК РЁБЕР ---
    // Наш связный ориентированный граф из 7 вершин без циклов
    Edge edgeList[E] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3},
        {3, 4}, {3, 5}, {4, 6}, {5, 6}
    };

    printf("\n--- СПИСОК РЁБЕР ---\n");
    for (int i = 0; i < E; i++) {
        printf("Ребро %d: %d -> %d\n", i, edgeList[i].src, edgeList[i].dest);
    }

    // --- 3. МАТРИЦА СМЕЖНОСТИ ---
    int adjMatrix[V][V] = {0}; // Заполняем нулями
    for (int i = 0; i < E; i++) {
        adjMatrix[edgeList[i].src][edgeList[i].dest] = 1;
    }

    printf("\n--- МАТРИЦА СМЕЖНОСТИ ---\n  ");
    for (int i = 0; i < V; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("%d ", i);
        for (int j = 0; j < V; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    // --- 4. МАТРИЦА ИНЦИДЕНТНОСТИ ---
    int incMatrix[V][E];
    buildIncidenceMatrix(edgeList, incMatrix);

    printf("\n--- МАТРИЦА ИНЦИДЕНТНОСТИ (Строки - Вершины, Столбцы - Рёбра) ---\n    ");
    for (int j = 0; j < E; j++) printf("e%d ", j);
    printf("\n");
    for (int i = 0; i < V; i++) {
        printf("v%d: ", i);
        for (int j = 0; j < E; j++) {
            if (incMatrix[i][j] >= 0) printf(" "); // Форматирование для выравнивания знаков минуса
            printf("%d ", incMatrix[i][j]);
        }
        printf("\n");
    }

    // --- 5. ЗАПУСК ТОПОЛОГИЧЕСКОЙ СОРТИРОВКИ ---
    // Передаем заполненную матрицу смежности в алгоритм Кана
    // Он сам выполнит сортировку и напечатает результат
    kahnsTopologicalSort(adjMatrix); // Вызываем алгоритм Кана

    return 0;
}

/*
gcc topological_sort.c -o topological_sort
./topological_sort
*/