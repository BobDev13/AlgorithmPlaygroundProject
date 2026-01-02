#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//Swap
void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

// Bubble sort (O(n^2)) 
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { swap(&arr[j], &arr[j + 1]); swapped = true; }
        }
        if (!swapped) break;
    }
}

// Partition for quicksort 
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { i++; swap(&arr[i], &arr[j]); }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quicksort (average O(n log n))
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Binary search (array must be sorted)
int binary_search(int arr[], int n, int target) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

// Fibonacci (iterative) 
long long fibonacci(int n) {
    if (n < 2) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
    return b;
}

// Timing helper 
double seconds_since(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Generate random array 
void fill_random(int* arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

int main() {
    srand((unsigned)time(NULL));
    int n = 20000; // adjust size for quick experiments
    int* arr1 = malloc(n * sizeof(int));
    int* arr2 = malloc(n * sizeof(int));
    fill_random(arr1, n);
    for (int i = 0; i < n; i++) arr2[i] = arr1[i];

    clock_t t1 = clock();
    bubble_sort(arr1, n);
    clock_t t2 = clock();
    printf("C: Bubble sort %d elements took %.3f s\n", n, seconds_since(t1, t2));

    clock_t t3 = clock();
    quick_sort(arr2, 0, n - 1);
    clock_t t4 = clock();
    printf("C: Quick sort %d elements took %.3f s\n", n, seconds_since(t3, t4));

    int target = arr2[n / 2]; // pick a value in middle
    int idx = binary_search(arr2, n, target);
    printf("C: Binary search found target at index %d\n", idx);

    int fibN = 45; // adjust for speed
    clock_t t5 = clock();
    long long fib = fibonacci(fibN);
    clock_t t6 = clock();
    printf("C: Fibonacci(%d) = %lld, took %.6f s\n", fibN, seconds_since(t5, t6));

    free(arr1); free(arr2);
    return 0;
}
