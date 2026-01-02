import java.util.Random;

public class Algorithms {

    static void swap(int[] arr, int i, int j) { int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }

    static void bubbleSort(int[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            boolean swapped = false;
            for (int j = 0; j < arr.length - i - 1; j++) {
                if (arr[j] > arr[j + 1]) { swap(arr, j, j + 1); swapped = true; }
            }
            if (!swapped) break;
        }
    }

    static int partition(int[] arr, int low, int high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) { i++; swap(arr, i, j); }
        }
        swap(arr, i + 1, high);
        return i + 1;
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int binarySearch(int[] arr, int target) {
        int l = 0, r = arr.length - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) l = mid + 1;
            else r = mid - 1;
        }
        return -1;
    }

    static long fibonacci(int n) {
        if (n < 2) return n;
        long a = 0, b = 1, c = 0;
        for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
        return b;
    }

    static int[] randomArray(int n) {
        Random rand = new Random(42);
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = rand.nextInt(100000);
        return arr;
    }

    static void time(String name, Runnable action) {
        long start = System.nanoTime();
        action.run();
        long end = System.nanoTime();
        System.out.printf("Java: %s took %.3f s%n", name, (end - start) / 1e9);
    }

    public static void main(String[] args) {
        int n = 20000;
        int[] arr1 = randomArray(n);
        int[] arr2 = arr1.clone();

        time(String.format("Bubble sort %d elements", n), () -> bubbleSort(arr1));
        time(String.format("Quick sort %d elements", n), () -> quickSort(arr2, 0, arr2.length - 1));

        int target = arr2[arr2.length / 2];
        int idx = binarySearch(arr2, target);
        System.out.println("Java: Binary search found target at index " + idx);

        int fibN = 45;
        time("Fibonacci(" + fibN + ")", () -> {
            long v = fibonacci(fibN);
            System.out.println("Java: Fibonacci(" + fibN + ") = " + v);
        });
    }
}
