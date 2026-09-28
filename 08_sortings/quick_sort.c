#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Разделение Хоара
int partition(int arr[], int low, int high) {
    int pivot = arr[low + (high - low) / 2]; // Выбор опорного элемента (середина)
    //можно выбирать случайно, но медиана лучше, есть еще медиана трех
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j) return j;
        swap(&arr[i], &arr[j]);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {23, 5, 8, 1, 19, 12, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив (Хоар): ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("Отсортированный массив: ");
    printArray(arr, n);
    return 0;
}
/*
Для чего используется: Универсальная высокоэффективная сортировка общего назначения. 
Является основой для стандартных функций сортировки во многих библиотеках (например, qsort в C). 
Сложность:
    Лучшая/Средняя: O(nlog n)
    Худшая: (O(n^2)) (когда опорный элемент постоянно выбирается неудачно, например, на уже отсортированном массиве) 
    Память: (O(log n)) (затраты на стек рекурсии). 
Стабильность: Нестабильная.

gcc quick_sort.c -o quick_sort
./quick_sort
*/