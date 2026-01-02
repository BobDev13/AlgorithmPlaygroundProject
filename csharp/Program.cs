using System;
using System.Diagnostics;

class Program
{
    static void Swap(int[] arr, int i, int j) { (arr[i], arr[j]) = (arr[j], arr[i]); }

    static void BubbleSort(int[] arr)
    {
        for (int i = 0; i < arr.Length - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < arr.Length - i - 1; j++)
            {
                if (arr[j] > arr[j + 1]) { Swap(arr, j, j + 1); swapped = true; }
            }
            if (!swapped) break;
        }
    }

    static int Partition(int[] arr, int low, int high)
    {
        int pivot = arr[high]; int i = low - 1;
        for (int j = low; j < high; j++)
            if (arr[j] <= pivot) { i++; Swap(arr, i, j); }
        Swap(arr, i + 1, high);
        return i + 1;
    }

    static void QuickSort(int[] arr, int low, int high)
    {
        if (low < high)
        {
            int pi = Partition(arr, low, high);
            QuickSort(arr, low, pi - 1);
            QuickSort(arr, pi + 1, high);
        }
    }

    static int BinarySearch(int[] arr, int target)
    {
        int l = 0, r = arr.Length - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) l = mid + 1; else r = mid - 1;
        }
        return -1;
    }

    static long Fibonacci(int n)
    {
        if (n < 2) return n;
        long a = 0, b = 1, c = 0;
        for (int i = 2; i <= n; i++) { c = a + b; a = b; b = c; }
        return b;
    }

    static int[] RandomArray(int n)
    {
        var rand = new Random(42);
        var arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = rand.Next(100000);
        return arr;
    }

    static void Time(string name, Action action)
    {
        var sw = Stopwatch.StartNew();
        action();
        sw.Stop();
        Console.WriteLine($"C#: {name} took {sw.Elapsed.TotalSeconds:F3} s");
    }

    static void Main()
    {
        int n = 20000;
        var arr1 = RandomArray(n);
        var arr2 = (int[])arr1.Clone();

        Time($"Bubble sort {n} elements", () => BubbleSort(arr1));
        Time($"Quick sort {n} elements", () => QuickSort(arr2, 0, arr2.Length - 1));

        int target = arr2[arr2.Length / 2];
        int idx = BinarySearch(arr2, target);
        Console.WriteLine($"C#: Binary search found target at index {idx}");

        int fibN = 45;
        Time($"Fibonacci({fibN})", () => { var v = Fibonacci(fibN); Console.WriteLine($"C#: Fibonacci({fibN}) = {v}"); });
    }
}
