// Copyright 2014, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast

#include "./PooSweeperStateBase.h"

#ifndef POOSWEEPERDISPLAYBASE_H_
#define POOSWEEPERDISPLAYBASE_H_

class PooSweeperDisplayBase;
extern PooSweeperDisplayBase* DISPLAY;

// Class for showing a state of the game on the screen.
class PooSweeperDisplayBase {
 public:
  virtual void show(const PooSweeperStateBase* state) const = 0;
};

#endif  // POOSWEEPERDISPLAYBASE_H_
