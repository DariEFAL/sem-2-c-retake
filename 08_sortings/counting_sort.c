#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    if (n <= 0) return;

    // Находим максимум и минимум для определения диапазона
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int range = max - min + 1;

    // Выделяем память под массивы подсчета и результата
    int *count = (int *)calloc(range, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    // Подсчитываем количество вхождений каждого элемента
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    // Преобразуем count так, чтобы он содержал реальные позиции элементов
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Строим выходной массив (идем с конца для сохранения стабильности)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // Копируем результат обратно в исходный массив
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("\nИсходный массив (Подсчет): ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    
    countingSort(arr, n);
    
    printf("\nОтсортированный массив: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

/*
Для чего используется: Не использует сравнения. 
Применяется, когда диапазон возможных значений элементов (разность между MAX и MIN) 
небольшой и сопоставим с количеством элементов. 
Идеальна для сортировки целых чисел, оценок, возрастов. 
Сложность:
    Лучшая/Средняя/Худшая: (O(n + k)), где [n] — количество элементов, а [k] — диапазон значений. 
    Память: O(n + k) (требует дополнительный массив подсчета и массив для результата). 
Стабильность: Стабильная (в правильной реализации с обратным обходом).

gcc counting_sort.c -o counting_sort
./counting_sort
*/