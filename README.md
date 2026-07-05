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

- [src/main.cpp](src/main.cpp) - Core C++ source code containing the cellular automata logic and Raylib loop.
- [include/](include/) - Raylib header files (`raylib.h`, `raymath.h`, `rlgl.h`).
- [lib/](lib/) - Raylib pre-compiled static and dynamic libraries for linking on Windows.
- [Makefile](Makefile) - Build configuration for the compiler.

---

## How it Works

### 1. Cellular Automata Rules

An elementary cellular automaton uses a binary rule to determine the next state of a cell based on its own state and its left and right neighbors:
$$\text{Next State} = f(\text{Left}, \text{Current}, \text{Right})$$

The indices of the rule lookup array are calculated by converting the three-cell state to a 3-bit binary integer:
$$\text{Index} = (\text{Left} \times 4) + (\text{Current} \times 2) + \text{Right}$$

The application now supports a database of **20 pre-configured Wolfram rules** defined in a lookup map:

| Class | Supported Rule Numbers |
| :--- | :--- |
| **Classics / Standard** | `18`, `22`, `30`, `45`, `54`, `60`, `90`, `110`, `150`, `184` |
| **Additional Rules** | `26`, `73`, `94`, `105`, `126`, `129`, `146`, `161`, `190`, `250` |

In [src/main.cpp](src/main.cpp), each rule is represented by an 8-element array containing the rule's binary digits written from MSB (left, representing bit 7) to LSB (right, representing bit 0).

You can specify which rule to run by passing the rule number as a command-line argument. If no argument is provided, the simulation defaults to **Rule 18**.

### 2. State & Grid Initialization

- **Grid Dimensions**: Grid size has been expanded to $128 \times 128$ cells:
  ```cpp
  const int COLS = 128;
  const int ROWS = 128;
  ```
- **Random Initial State**: Instead of starting with a single active cell in the center, the initial generation (row 0) is randomized (each cell has a 50% chance of being active or inactive):
  ```cpp
  for (int &cell : cells) {
    cell = rand() % 2;
  }
  ```
- **Frame-by-Frame Generation**: Generations are calculated incrementally inside the main Raylib update loop. One new generation (row) is computed per frame by calling the [generate](src/main.cpp#L10) function, until the grid is filled.

### 3. Rendering

The simulation runs at a target rate of 60 FPS in an $800 \times 450$ window.
Each active cell (`1`) is drawn on the screen as an $8 \times 8$ pixel black rectangle:
```cpp
DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
```
*(Note: With a grid size of $128 \times 128$ and a cell size of 8, the total rendering area is $1024 \times 1024$ pixels. Since the window is $800 \times 450$ pixels, the right and bottom portions of the grid will be clipped by the window edges.)*

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

To run the default rule (Rule 18):
```bash
make run
```

To run a custom rule (e.g., Rule 30 or Rule 90):
```bash
./build/game 30
```

To clean build artifacts:
```bash
make clean
```
