#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

void generate(std::vector<int> &cells, const std::array<int, 8> &rules) {
  std::vector<int> next(cells.size());

  next[0] = cells[0];
  next[cells.size() - 1] = cells[cells.size() - 1];

  for (size_t i = 1; i < cells.size() - 1; i++) {
    int left = cells[(i - 1 + cells.size()) % cells.size()];
    int current = cells[i];
    int right = cells[(i + 1) % cells.size()];

    int ruleIndex = left * 4 + current * 2 + right;
    next[i] = rules[ruleIndex];
  }

  cells = std::move(next);
}

int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  const std::unordered_map<int, std::array<int, 8>> rules = {
      {18, {0, 0, 0, 1, 0, 0, 1, 0}},  {22, {0, 0, 0, 1, 0, 1, 1, 0}},
      {30, {0, 0, 0, 1, 1, 1, 1, 0}},  {45, {0, 0, 1, 0, 1, 1, 0, 1}},
      {54, {0, 0, 1, 1, 0, 1, 1, 0}},  {60, {0, 0, 1, 1, 1, 1, 0, 0}},
      {90, {0, 1, 0, 1, 1, 0, 1, 0}},  {110, {0, 1, 1, 0, 1, 1, 1, 0}},
      {150, {1, 0, 0, 1, 0, 1, 1, 0}}, {184, {1, 0, 1, 1, 1, 0, 0, 0}},

      {26, {0, 0, 0, 1, 1, 0, 1, 0}},  {73, {0, 1, 0, 0, 1, 0, 0, 1}},
      {94, {0, 1, 0, 1, 1, 1, 1, 0}},  {105, {0, 1, 1, 0, 1, 0, 0, 1}},
      {126, {0, 1, 1, 1, 1, 1, 1, 0}}, {129, {1, 0, 0, 0, 0, 0, 0, 1}},
      {146, {1, 0, 0, 1, 0, 0, 1, 0}}, {161, {1, 0, 1, 0, 0, 0, 0, 1}},
      {190, {1, 0, 1, 1, 1, 1, 1, 0}}, {250, {1, 1, 1, 1, 1, 0, 1, 0}},
  };

  InitWindow(screenWidth, screenHeight, "Cellular Automata");
  SetTargetFPS(60);

  const int COLS = 128;
  const int ROWS = 128;
  std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));

  std::vector<int> cells(COLS);
  for (int &cell : cells) {
    cell = rand() % 2;
  }

  int rulesKey = 18;

  if (argc > 1) {
    rulesKey = std::stoi(argv[1]);
  }

  auto it = rules.find(rulesKey);

  if (it == rules.end()) {
    std::cerr << "ERROR: Unknown rule: " << rulesKey << '\n';
    std::cerr << "Available rules:\n";

    for (const auto &[key, _] : rules) {
      std::cout << " " << key << ',';
    }

    std::cout << "\n";

    return 1;
  }

  const auto &currentRule = it->second;

  size_t length = cells.size();

  int currentWidth = GetScreenWidth();
  int currentHeight = GetScreenHeight();
  int currentRow = 0;

  for (int i = 0; i < COLS; i++) {
    grid[0][i] = cells[i];
  }

  const int CELL_SIZE = 8;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentRow < ROWS) {
      for (int i = 0; i < COLS; i++) {
        grid[currentRow][i] = cells[i];
      }
      generate(cells, currentRule);
      currentRow++;
    }

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
