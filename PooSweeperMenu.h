// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#ifndef PROJEKT_POOSWEEPERMENU_H_
#define PROJEKT_POOSWEEPERMENU_H_

#include <stdlib.h>

class PooSweeperMenu{
 public:
  // Constructor
  PooSweeperMenu();

  // Shows the starting menu
  void startScreen();

  // Shows the end menu
  void endScreen();

  // Destructor
  ~PooSweeperMenu();

  bool exit;

 private:
  // The informations from the menu
  size_t _rows;
  size_t _cols;
  size_t _poos;
};
#endif  // PROJEKT_POOSWEEPERMENU_H_
