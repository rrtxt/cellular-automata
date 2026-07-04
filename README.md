# Elementary Cellular Automata Visualizer

A C++ implementation of a 1D **Elementary Cellular Automaton** using the **Raylib** library for visualization.

## Overview

This project implements a 1-Dimensional Cellular Automaton that evolves over time. The generations are stacked vertically (row by row) to visualize the evolution pattern on a 2D grid (a common representation of Wolfram's cellular automata).

### Key Features
- **1D Cellular Automata Evolution**: Evolves a single array of cells over multiple generations.
- **Wolfram Rule Configuration**: Currently configured to run **Rule 145**.
- **Fixed Boundary Conditions**: The edge cells maintain their initial state, while internal cells evolve based on their neighbors.
- **Raylib Visualization**: Renders the active cells as black blocks on a clean white canvas.

---

## Project Structure

- [src/main.cpp](file:///C:/Users/rizfi/main/Hobbies/Projects/cellular-automata/src/main.cpp) - Core C++ source code containing the cellular automata logic and Raylib loop.
- [include/](file:///C:/Users/rizfi/main/Hobbies/Projects/cellular-automata/include) - Raylib header files (`raylib.h`, `raymath.h`, `rlgl.h`).
- [lib/](file:///C:/Users/rizfi/main/Hobbies/Projects/cellular-automata/lib) - Raylib pre-compiled static and dynamic libraries for linking on Windows.
- [Makefile](file:///C:/Users/rizfi/main/Hobbies/Projects/cellular-automata/Makefile) - Build configuration for the compiler.

---

## How it Works

### 1. The Cellular Automata Rule
An elementary cellular automaton uses a binary rule to determine the next state of a cell based on its own state and its left and right neighbors:
$$\text{Next State} = f(\text{Left}, \text{Current}, \text{Right})$$

The indices of the rule lookup array are calculated by converting the three-cell state to a 3-bit binary integer:
$$\text{Index} = (\text{Left} \times 4) + (\text{Current} \times 2) + \text{Right}$$

In [src/main.cpp](file:///C:/Users/rizfi/main/Hobbies/Projects/cellular-automata/src/main.cpp), the active rule is defined as:
```cpp
int rules[] = {1, 0, 0, 0, 1, 0, 0, 1};
```
This maps to **Rule 145** (binary `10010001`):
* `111` (Index 7) ➔ `1`
* `110` (Index 6) ➔ `0`
* `101` (Index 5) ➔ `0`
* `100` (Index 4) ➔ `1`
* `011` (Index 3) ➔ `0`
* `010` (Index 2) ➔ `0`
* `001` (Index 1) ➔ `0`
* `000` (Index 0) ➔ `1`

### 2. State & Grid Initialization
- A grid of $100 \times 100$ cells is allocated: `int grid[ROWS][COLS] = {0}`.
- Row `0` (the first generation) is initialized with a single active cell in the center:
  ```cpp
  cells[COLS / 2] = 1;
  ```
- Before entering the rendering loop, the application pre-calculates the states of all subsequent rows (from row 1 to 99) by sequentially running the `generate()` function on the state of the previous row.

### 3. Rendering
The simulation runs at a target rate of 60 FPS in an $800 \times 450$ window.
Each active cell (`1`) is drawn on the screen as an $8 \times 8$ pixel black rectangle (`DrawRectangle`):
```cpp
DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
```

---

## Build & Run Instructions

### Prerequisites
- GCC / G++ compiler installed (e.g. MinGW-w64 on Windows).
- Make utility.

### Commands

To compile the project:
```bash
make
```

To run the compiled binary:
```bash
make run
```

To clean build artifacts:
```bash
make clean
```


