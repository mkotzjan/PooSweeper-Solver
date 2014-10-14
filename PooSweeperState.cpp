// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#include "./PooSweeperState.h"
#include <stdlib.h>
#include <vector>
#include "./PooSweeperMove.h"

PooSweeperState poo;
PooSweeperStateBase* POO = &poo;

// _____________________________________________________________________________
PooSweeperState::CellInfo PooSweeperState::getCellInfo(
    size_t rowIndex, size_t colIndex) const {
  return CellInfoStorage[rowIndex][colIndex];
}

// _____________________________________________________________________________
void PooSweeperState::initialize(
    size_t numRows, size_t numCols, size_t numPoos) {
  _numRows = numRows;
  _numCols = numCols;
  _numPoos = numPoos;

  // Set other variable to default
  _numRevealed = 0;
  _numMarked = 0;
  _status = ONGOING;

  size_t pooRow;
  size_t pooCol;
  // Clear vector in case of last game
  CellInfoStorage.clear();
  CellInfoPoo.clear();
  // Set game to unrevealed and poos to no poos
  CellInfoStorage.resize(_numRows);
  CellInfoPoo.resize(_numRows);
  for (int i = 0; i < _numRows; ++i) {
    for (int j = 0; j < _numCols; ++j) {
      CellInfoStorage[i].push_back(UNREVEALED);
      CellInfoPoo[i].push_back(NO_POO);
    }
  }
  // Only for debugging
  // CellInfoStorage[0][0] = MARKED;
  // CellInfoStorage[0][1] = REVEALED_POO;
  // CellInfoStorage[1][0] = REVEALED_TWO;
  // CellInfoStorage[2][0] = REVEALED_ONE;
  // CellInfoStorage[3][0] = REVEALED_ZERO;

  // Set poos
  for (int i = 0; i < _numPoos;) {
    pooRow = random() % _numRows;
    pooCol = random() % _numCols;
    if (CellInfoPoo[pooRow][pooCol] == NO_POO) {
      CellInfoPoo[pooRow][pooCol] = POO;
      ++i;
    }
  }
}

// _____________________________________________________________________________
void PooSweeperState::applyMove(const PooSweeperMove& move) {
  size_t posRow;
  size_t posCol;
  size_t countPoo = 0;

  if (move.type == PooSweeperMove::REVEAL) {
    if (checkPoo(move.row, move.col) == true) {
      CellInfoStorage[move.row][move.col] = REVEALED_POO;
      ++_numRevealed;
      revealPoos();
      _status = LOST;
      return;
    }
    if (CellInfoStorage[move.row][move.col] != UNREVEALED) return;
    for (int x = -1; x < 2; ++x) {
      for (int y = -1; y < 2; ++y) {
        posRow = move.row + x;
        posCol = move.col + y;
        if (posRow >= 0 && posCol >= 0 && posRow < _numRows &&
          posCol < _numCols) {
          if (CellInfoPoo[posRow][posCol] == POO) {
            ++countPoo;
          }
        }
      }
    }
    CellInfoStorage[move.row][move.col] = CellInfo(countPoo);
    ++_numRevealed;
    if (countPoo == 0) { autoReveal(move.row, move.col); }
    return;

  } else if (move.type == PooSweeperMove::TOGGLE_MARK) {
    if (CellInfoStorage[move.row][move.col] == UNREVEALED) {
      CellInfoStorage[move.row][move.col] = MARKED;
      ++_numMarked;
    } else if (CellInfoStorage[move.row][move.col] == MARKED) {
      CellInfoStorage[move.row][move.col] = UNREVEALED;
      --_numMarked;
    }
    wonGame();
    return;

  } else if (move.type == PooSweeperMove::LEFT_RIGHT) {
    if (CellInfoStorage[move.row][move.col] >= 1) {
      size_t posX;
      size_t posY;

      for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
          posX = move.row + i;
          posY = move.col + j;
          if (CellInfoPoo[posX][posY] == POO &&
              CellInfoStorage[posX][posY] == UNREVEALED) {
            CellInfoStorage[posX][posY] = REVEALED_POO;
            ++_numRevealed;
            revealPoos();
            _status = LOST;
            return;
          }
          if (CellInfoStorage[posX][posY] == UNREVEALED) {
            for (int x = -1; x < 2; ++x) {
              for (int y = -1; y < 2; ++y) {
                posRow = posX + x;
                posCol = posY + y;
                if (CellInfoPoo[posRow][posCol] == POO) {
                  ++countPoo;
                }
              }
            }
            CellInfoStorage[posX][posY] = CellInfo(countPoo);
            ++_numRevealed;
            return;
          }
        }
      }
    }
    return;
  }
}

// _____________________________________________________________________________
PooSweeperState::GameStatus PooSweeperState::status() const {
  return _status;
}

// _____________________________________________________________________________
size_t PooSweeperState::numRows() const { return _numRows; }

// _____________________________________________________________________________
size_t PooSweeperState::numCols() const { return _numCols; }

// _____________________________________________________________________________
size_t PooSweeperState::numPoos() const { return _numPoos; }

// _____________________________________________________________________________
size_t PooSweeperState::numRevealed() const { return _numRevealed; }

// _____________________________________________________________________________
size_t PooSweeperState::numMarked() const { return _numMarked; }

// _____________________________________________________________________________
void PooSweeperState::autoReveal(size_t rowIndex, size_t colIndex) {
  size_t posRow;
  size_t posCol;
  if (CellInfoStorage[rowIndex][colIndex] == REVEALED_ZERO) {
  // Iterate throug all fields around the position
    for (int x = -1; x < 2; ++x) {
      for (int y = -1; y < 2; ++y) {
        posRow = rowIndex + x;
        posCol = colIndex + y;
        // Reveal the position
        if (posRow >= 0 && posCol >= 0 && posRow < _numRows &&
         posCol < _numCols) {
          if (CellInfoStorage[posRow][posCol] == UNREVEALED) {
            PooSweeperMove autoReveal;
            autoReveal.row = posRow;
            autoReveal.col = posCol;
            autoReveal.type = PooSweeperMove::REVEAL;
            applyMove(autoReveal);
          }
        }
      }
    }
  }
}

// _____________________________________________________________________________
bool PooSweeperState::checkPoo(size_t rowIndex, size_t colIndex) const {
  if (CellInfoPoo[rowIndex][colIndex] == POO) {
    return true;
  } else {
    return false;
  }
}

// _____________________________________________________________________________
bool PooSweeperState::wonGame() {
  // size_t unrevealed = 0;
  // size_t rightMarked = 0;
  // for (int i = 0; i < _numRows; ++i) {
  //   for (int j = 0; j < _numCols; ++j) {
  //     if (CellInfoPoo[i][j] == POO && CellInfoStorage[i][j] == MARKED) {
  //       ++rightMarked;
  //     }
  //     if (CellInfoStorage[i][j] == UNREVEALED) {
  //       ++unrevealed;
  //     }
  //   }
  // }
  size_t numCells = _numRows * _numCols;
  size_t numUnrevealed = numCells - _numRevealed;
  if (_numMarked + numUnrevealed == _numPoos) _status = WON;
}

// _____________________________________________________________________________
void PooSweeperState::revealPoos() {
  for (int i = 0; i < _numRows; ++i) {
    for (int j = 0; j < _numCols; ++j) {
      if (checkPoo(i, j)) {
        CellInfoStorage[i][j] = REVEALED_POO;
      }
    }
  }
}
