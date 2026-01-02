# Algorithm Playground

Implementations of classic algorithms in C, C#, and Java. Includes execution-time comparisons.

## Algorithms
- Bubble sort (O(n^2))
- Quicksort (average O(n log n))
- Binary search (O(log n))
- Fibonacci (iterative)

## Structure
- `c/algorithms.c`
- `csharp/Program.cs` (+ `AlgorithmPlayground.csproj`)
- `java/Algorithms.java`

## Run
run-all.ps1

### C (MinGW / MSYS2)
```bash
cd c
gcc algorithms.c -O2 -o algorithms.exe
./algorithms.exe

