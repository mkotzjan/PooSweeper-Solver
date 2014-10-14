// Copyright 2014, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast

#ifndef PROJEKT_POOSWEEPERSTATEBASE_H_
#define PROJEKT_POOSWEEPERSTATEBASE_H_

#include <vector>
#include "./PooSweeperMove.h"

class PooSweeperStateBase;
extern PooSweeperStateBase* POO;

// Class representing a state of the Minesweeper game.
//
// NOTE: This class *must* be used both by the people programming the game (to
// be played by a human via the keyboard), as well as by the people programming
// a solver (which automatically generates a move given a state).
class PooSweeperStateBase {
 public:
  // Virtual destructor.
  virtual ~PooSweeperStateBase() { }

  // Get cell information (for playing):
  enum CellInfo {
    REVEALED_POO = -3, MARKED = -2, UNREVEALED = -1,
    REVEALED_ZERO = 0, REVEALED_ONE = 1, REVEALED_TWO =2,
    REVEALED_THREE = 3, REVEALED_FOUR = 4, REVEALED_FIVE = 5,
    REVEALED_SIX = 6, REVEALED_SEVEN = 7, REVEALED_EIGHT = 8
  };
  virtual CellInfo getCellInfo(size_t rowIndex, size_t colIndex) const = 0;

  // Initialize (randomly).
  virtual void initialize(size_t numRows, size_t numCols, size_t numPoos) = 0;

  // Apply move.
  virtual void applyMove(const PooSweeperMove& move) = 0;

  // Status of the game:
  enum GameStatus { ONGOING, LOST, WON };
  virtual GameStatus status() const = 0;

  // Getters.
  virtual size_t numRows() const = 0;
  virtual size_t numCols() const = 0;
  virtual size_t numPoos() const = 0;
  virtual size_t numRevealed() const = 0;
  virtual size_t numMarked() const = 0;
};

#endif  // PROJEKT_POOSWEEPERSTATEBASE_H_
