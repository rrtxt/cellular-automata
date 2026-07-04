#include <cstdio>
#include <iostream>
#include <raylib.h>

void generate(int cells[], int rules[], int length) {
  int next[length];

  next[0] = cells[0];
  next[length - 1] = cells[length - 1];
  for (int i = 1; i < length - 1; i++) {
    int current = cells[i];
    int left = cells[(i - 1 + length) % length];
    int right = cells[(i + 1) % length];

    int rulesIdx = left * 4 + current * 2 + right;
    next[i] = rules[rulesIdx];
  }

  for (int i = 0; i < length; i++) {
    cells[i] = next[i];
  }
};

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Cellular Automata");
  SetTargetFPS(60);

  const int COLS = 100;
  const int ROWS = 100;
  int grid[ROWS][COLS] = {0};

  int cells[COLS] = {0};
  cells[COLS / 2] = 1;

  int rules[] = {1, 0, 0, 0, 1, 0, 0, 1};
  int length = std::size(cells);

  int currentWidth = GetScreenWidth();
  int currentHeight = GetScreenHeight();

  for (int i = 0; i < COLS; i++) {
    grid[0][i] = cells[i];
  }

  for (int row = 1; row < ROWS; row++) {
    generate(cells, rules, COLS);
    for (int col = 0; col < length; col++) {
      grid[row][col] = cells[col];
    }
  }

  const int CELL_SIZE = 8;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {
        if (grid[row][col] == 1) {
          DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                        BLACK);
        }
      }
    }

    EndDrawing();
  }
  CloseWindow();

  return 0;
};
