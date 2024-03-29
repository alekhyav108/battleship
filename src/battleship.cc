// Copyright (c) 2020 [Alekhya Vakkalagadda]. All rights reserved.

#include <mylibrary/battleship.h>

#include <string>
#include <chrono>

namespace mylibrary {

Battleship::Battleship()
: ship_grid_arr_(),
  ship_a_{Ship("shipA", kShipASize)},
  ship_b_{Ship("shipB", kShipBSize)},
  ship_c_{Ship("shipC", kShipCSize)}

{}

void Battleship::InitializeGrid() {
  for (int row = 1; row < kGridSize; row++) {
    for (int col = 1; col < kGridSize; col++) {
      battle_grid_[row][col] = TileState::kEmpty;
    }
  }
}

void Battleship::InitializeShipGrid() {
  for (int row = 1; row < kGridSize; row++) {
    for (int col = 1; col < kGridSize; col++) {
      ship_grid_arr_[row][col].has_ship_ = false;
    }
  }
}

void Battleship::PlaceShip() {
  std::string ship_name;
  int size_ship;

  ship_name = ship_a_.GetName();
  size_ship = ship_a_.GetSize();
  PlaceVShip(ship_name, size_ship);

  ship_name = ship_b_.GetName();
  size_ship = ship_b_.GetSize();
  PlaceVShip(ship_name, size_ship);

  ship_name = ship_c_.GetName();
  size_ship = ship_c_.GetSize();
  PlaceHShip(ship_name, size_ship);
}

void Battleship::PlaceHShip(const std::string& ship_name, int size_ship) {
  std::srand(time(0));

  //generating random coordinates for a ship horizontally
  for (int i = 0; i < 20; i++) {
    int rand_x, rand_y, x1, y1, x2, y2;
    rand_x = (rand() % (size_ship - 1)) + 1;
    rand_y = (rand() % (kGridSize - 1)) + 1;

    //used to check surroundings of the potentially placed ship
    x1 = rand_x - 1;
    y1 = rand_y - 1;
    x2 = rand_x + size_ship;
    y2 = rand_y + 1;
    bool does_have_ship = HasShip(x1, y1, x2, y2);
    if (!does_have_ship) {
      for (int x = rand_x; x < (rand_x + size_ship); x++) {
        ship_grid_arr_[x][rand_y].has_ship_ = true;
        ship_grid_arr_[x][rand_y].ship_name_ = ship_name;
      }
      //so it doesn't keep on looking for a place to put the ship
      break;
    }
  }
}

void Battleship::PlaceVShip(const std::string& ship_name, int size_ship) {
  std::srand(time(0));

  //generating random coordinates for a ship vertically
  for (int i = 0; i < kNumCheck; i++) {
    int rand_x, rand_y, x1, y1, x2, y2;
    rand_x = (rand() % (kGridSize - 1)) + 1;
    rand_y = (rand() % (size_ship - 1)) + 1;

    //used to check surroundings of the potentially placed ship
    x1 = rand_x - 1;
    y1 = rand_y - 1;
    x2 = rand_x + 1;
    y2 = rand_y + size_ship;
    bool does_have_ship = HasShip(x1, y1, x2, y2);
    if (!does_have_ship) {
      for (int y = rand_y; y < (rand_y + size_ship); y++) {
        ship_grid_arr_[rand_x][y].has_ship_ = true;
        ship_grid_arr_[rand_x][y].ship_name_ = ship_name;
      }
      //so it doesn't keep on looking for a place to put the ship
      break;
    }
  }
}

bool Battleship::HasShip(int x1, int y1, int x2, int y2) {
  //checks from top left tile to bottom right tile
  for (int x = x1; x <= x2; x++) {
    for (int y = y1; y <= y2; y++) {
      if (ship_grid_arr_[x][y].has_ship_) {
        return true;
      }
    }
  }
  return false;
}

void Battleship::SetGridItem(int row, int col) {
  if (battle_grid_[row][col] == TileState::kHit) {
    return;
  }

  //checks to see if the tile has a ship
  if (ship_grid_arr_[row][col].has_ship_) {
    int counter;
    std::string ship_name = ship_grid_arr_[row][col].ship_name_;

    //finding counter (initially size of the ship) and name of ship
    if (ship_name == ship_a_.GetName()) {
      counter = ship_a_.GetCounter();
      //every time part of a ship is hit, the counter for that ship decrements
      if (counter > 0) {
        counter--;
        ship_a_.SetCounter(counter);
        battle_grid_[row][col] = TileState::kHit;
      }
    } else if (ship_name == ship_b_.GetName()) {
      counter = ship_b_.GetCounter();
      if (counter > 0) {
        counter--;
        ship_b_.SetCounter(counter);
        battle_grid_[row][col] = TileState::kHit;
      }
    } else if (ship_name == ship_c_.GetName()) {
      counter = ship_c_.GetCounter();
      if (counter > 0) {
        counter--;
        ship_c_.SetCounter(counter);
        battle_grid_[row][col] = TileState::kHit;
      }
    }
    //makes all the tiles for that ship sink once the counter for that ship is 0
    SetSinkTiles();
  } else {
    battle_grid_[row][col] = TileState::kMiss;
  }
}

void Battleship::SetSinkTiles() {
  std::string ship_name;
  int ship_count;

  for (int row = 1; row < kGridSize; row++) {
    for (int col = 1; col < kGridSize; col++) {
      //checks to see if that tile has a ship
      if (ship_grid_arr_[row][col].has_ship_) {
        //checks to see if the ship count is 0 for a ship
        ship_name = ship_grid_arr_[row][col].ship_name_;
        if (ship_name == ship_a_.GetName()) {
          ship_count = ship_a_.GetCounter();
        } else if (ship_name == ship_b_.GetName()) {
          ship_count = ship_b_.GetCounter();
        } else if (ship_name == ship_c_.GetName()) {
          ship_count = ship_c_.GetCounter();
        }
        //sets the tile to be a sink
        if (ship_count == 0) {
          battle_grid_[row][col] = TileState::kSink;
        }
      }
    }
  }
}

void Battleship::SetHasShip(int row, int col) {
  ship_grid_arr_[row][col].has_ship_ = true;
}

bool Battleship::GetHasShip(int row, int col) {
  return ship_grid_arr_[row][col].has_ship_;
}

TileState Battleship::GetGridItem(int row, int col) {
  return battle_grid_[row][col];
}


}  // namespace mylibrary
