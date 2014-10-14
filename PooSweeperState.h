// Copyright 2014, University of Freiburg.
// Author: Michael Kotzjan

#ifndef PROJEKT_POOSWEEPERSTATE_H_
#define PROJEKT_POOSWEEPERSTATE_H_

#include <gtest/gtest.h>
#include <vector>
#include "./PooSweeperMove.h"
#include "./PooSweeperStateBase.h"

class PooSweeperStateBase;
extern PooSweeperStateBase* POO;

// Class representing a state of the Minesweeper game.
class PooSweeperState : public PooSweeperStateBase{
 public:
  // Get cell information (for playing):
  CellInfo getCellInfo(size_t rowIndex, size_t colIndex) const;

  // Initialize (randomly).
  void initialize(size_t numRows, size_t numCols, size_t numPoos);

  // Apply move.
  void applyMove(const PooSweeperMove& move);

  // Status of the game:
  GameStatus status() const;

  // Getters.
  size_t numRows() const;
  size_t numCols() const;
  size_t numPoos() const;
  size_t numRevealed() const;
  size_t numMarked() const;

  // To be poo, or not to be poo, that is the question
  enum CellInfoPoo {
    POO = 1, NO_POO = 0
  };

 private:
  // Variables
  size_t _numRows;
  size_t _numCols;
  size_t _numPoos;
  size_t _numRevealed;
  size_t _numMarked;

  // Stores the status of the game as membervariable
  GameStatus _status;

  // Stores the entire field without poos
  std::vector<std::vector<CellInfo>> CellInfoStorage;

  // Holds the position of the poos
  std::vector<std::vector<CellInfoPoo>> CellInfoPoo;

  FRIEND_TEST(PooSweeperStateTest, initialize);

  // Reveal more fields automaticly if possible
  void autoReveal(size_t rowIndex, size_t colIndex);

  // Check for a poo on given position
  bool checkPoo(size_t rowIndex, size_t colIndex) const;

  // Check for won game
  bool wonGame();

  // Reveal all poos at the end of an game
  void revealPoos();
};

#endif  // PROJEKT_POOSWEEPERSTATE_H_
