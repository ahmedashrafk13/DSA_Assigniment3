# Counting Sort, Radix Sort, Bucket Sort & Pigeonhole Sort — Performance Comparison

##  Overview
This project implements and benchmarks several non-comparison-based sorting algorithms:

- **Stable Counting Sort**
- **Non‑Stable Counting Sort**
- **LSD Radix Sort**
- **Bucket Sort (for floats)**
- **Pigeonhole Sort**

The program automatically:
- Generates multiple input datasets  
- Runs benchmark tests  
- Displays execution time for each sorting algorithm under each scenario  

---

##  Files
| File | Description |
|------|-------------|
| `main.cpp` | Full C++ implementation of all sorting algorithms and benchmarking framework |
| `README.md` | Instructions, explanation, and usage guide |

---

##  How to Compile & Run

### **1. Requirements**
You need a **C++17** (or newer) compiler such as:
- GCC / MinGW
- Clang
- MSVC (Visual Studio)
- Xcode (macOS)

---

## **2. Compile**

### Windows (MinGW)
```sh
g++ main.cpp -o sorting.exe -O2
```

### Linux / macOS
```sh
g++ main.cpp -o sorting -O2
```

---

## **3. Run the Program**

### Windows:
```sh
sorting.exe
```

### Linux/macOS:
```sh
./sorting
```

---

##  Output Example
The program prints execution time (in ms) for each algorithm under:

- Random data
- Already sorted data
- Reverse sorted data
- Many duplicates
- Floats (bucket sort)

Example:
```
=== Scenario: Random ===
Stable Counting Sort:      12 ms
Non-Stable Counting Sort:  10 ms
LSD Radix Sort:            5 ms
Pigeonhole Sort:           13 ms
```

---

##  Notes
- Counting Sort, Pigeonhole Sort, and Radix Sort are extremely efficient when the numeric range is small.
- Bucket Sort is ideal when input floats fall within `[0,1)`.

---





---


