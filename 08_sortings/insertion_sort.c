#include <stdio.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Сдвигаем элементы, которые больше ключа, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("\nИсходный массив (Вставки): ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    
    insertionSort(arr, n);
    
    printf("\nОтсортированный массив: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

/*
Для чего используется: Эффективна на небольших массивах (обычно до 10-20 элементов) 
или на частично отсортированных данных. Часто используется как финальный этап 
в гибридных алгоритмах (например, в Timsort или IntroSort). 
Сложность:
    Лучшая: O(n) (если массив уже отсортирован).
    Средняя/Худшая: O(n^2). 
    Память: O(1). 
Стабильность: Стабильная (сохраняет исходный порядок одинаковых элементов).

gcc insertion_sort.c -o insertion_sort
./insertion_sort
*/