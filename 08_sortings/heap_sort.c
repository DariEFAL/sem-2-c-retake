#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если самый большой элемент не корень, меняем их местами и просеиваем дальше
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Шаг 1: Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Шаг 2: Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--) {
        // Перемещаем текущий корень в конец
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("\nИсходный массив (Просеивание): ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    
    heapSort(arr, n);
    
    printf("\nОтсортированный массив: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

/*
Для чего используется: 
В системах общего назначения, где критически важно гарантированное
время выполнения без просадок в худшем случае (в отличие от Быстрой сортировки). 
Часто применяется в робототехнике, ядре ОС и встроенных системах. 
Сложность:
    Лучшая/Средняя/Худшая: O(nlog n). 
    Память: O(1) (сортирует внутри бинарной кучи прямо на месте). 
Стабильность: Нестабильная.

gcc heap_sort.c -o heap_sort
./heap_sort
*/