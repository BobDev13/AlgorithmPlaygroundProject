# Algorithm Playground - consolidated runner
Write-Host "=== Algorithm Playground Comparison ===`n"

# Paths (adjust if your folders differ)
$CExe     = "c\algorithms.exe"
$CSProj   = "csharp\AlgorithmPlayground.csproj"
$JavaFile = "java\Algorithms.class"

# Compile C if needed
if (-Not (Test-Path $CExe)) {
    Write-Host "Compiling C program..."
    gcc c\algorithms.c -O2 -o $CExe
}

# Compile Java if needed
if (-Not (Test-Path $JavaFile)) {
    Write-Host "Compiling Java program..."
    javac java\Algorithms.java
}

# Run C
Write-Host "`n--- Running C ---"
$COutput = & $CExe

# Run C#
Write-Host "`n--- Running C# ---"
$CSOutput = dotnet run --project $CSProj -c Release

# Run Java
Write-Host "`n--- Running Java ---"
$JavaOutput = java -cp java Algorithms

# Parsing function: returns a collection of PSCustomObject rows
function Parse-Output {
    param(
        [string[]]$Lines,
        [string]$Lang
    )

    $rows = @()
    foreach ($line in $Lines) {
        # Expected: "<Lang>: <Algorithm text> took <seconds> s"
        if ($line -match "^\s*.*:\s+(.+)\s+took\s+([0-9\.]+)\s+s\s*$") {
            $algorithm = $matches[1].Trim()
            $seconds   = [double]$matches[2]
            $rows += [PSCustomObject]@{
                Language  = $Lang
                Algorithm = $algorithm
                Time_s    = $seconds
            }
        }
    }
    return $rows
}

# Consolidate results by collecting returned rows (avoid += inside function scope issues)
$results = @()
$results += Parse-Output $COutput   "C"
$results += Parse-Output $CSOutput  "C#"
$results += Parse-Output $JavaOutput "Java"

Write-Host "`n=== Consolidated Results ==="
if ($results.Count -gt 0) {
    $results | Sort-Object Algorithm, Language | Format-Table -AutoSize
} else {
    Write-Host "No parsable results found. Ensure each program prints lines like:"
    Write-Host "C: Bubble sort 20000 elements took 0.123 s"
    Write-Host "C#: Quick sort 20000 elements took 0.010 s"
    Write-Host "Java: Fibonacci(45) took 0.001 s"
}

# Optional: also export to CSV for your CV/README
# $results | Export-Csv -Path results.csv -NoTypeInformation