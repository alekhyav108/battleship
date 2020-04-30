// Copyright (c) 2020 [Alekhya Vakkalagadda]. All rights reserved.

#include <mylibrary/battleship.h>

#include <string>

namespace mylibrary {

void Battleship::InitializeGrid() {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      battle_grid_[row][col] = TileState::kEmpty;
    }
  }
}

void Battleship::SetGridItem(int row, int col, char key1, char key2) {
  int x = (int) key1 - 96;
  int y = (int) key2 - 48;
  if (x == row && y == col && ship_grid_[row][col]) {
    battle_grid_[row][col] = TileState::kHit;
  }
}

TileState Battleship::GetGridItem(int row, int col) {
  return battle_grid_[row][col];
}

void Battleship::InitializeShipGrid() {
  for (int row = 1; row < 5; row+=2) {
    for (int col = 1; col < 5; col+=2) {
      ship_grid_[row][col] = true;
    }
  }

  for (int row = 2; row < 5; row+=2) {
    for (int col = 2; col < 5; col+=2) {
      ship_grid_[row][col] = false;
    }
  }
}





}  // namespace mylibrary
