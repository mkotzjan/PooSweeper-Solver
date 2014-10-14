// Copyright 2014, University of Freiburg,
// Author: Michael Kotzjan

#include "./PooSweeperDisplay.h"
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <string>

PooSweeperDisplay display;
PooSweeperDisplayBase* DISPLAY = &display;

// ___________________________________________________________________________
void PooSweeperDisplay::show(const PooSweeperStateBase* state) const {
  for (int i = 0; i < state->numRows(); ++i) {
    for (int j = 0; j < state->numCols(); ++j) {
      printf("\x1b[%d;%dH", i + 1, j + 1);
      switch (state->getCellInfo(i, j)) {
        case PooSweeperStateBase::UNREVEALED:
          printf("\x1b[7m");
          printf("?");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::MARKED:
          printf("\x1b[7m");
          printf("\x1b[41m");
          printf("\u2691");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_POO:
          printf("\x1b[0;32m");
          printf("\u2601");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_ZERO:
          printf(" ");
          break;
        case PooSweeperStateBase::REVEALED_ONE:
          printf("\x1b[34m");
          printf("1");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_TWO:
          printf("\x1b[1;32m");
          printf("2");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_THREE:
          printf("\x1b[32;1m");
          printf("3");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_FOUR:
          printf("\x1b[32;1m");
          printf("4");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_FIVE:
          printf("\x1b[32;1m");
          printf("5");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_SIX:
          printf("\x1b[32;1m");
          printf("6");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_SEVEN:
          printf("\x1b[32;1m");
          printf("7");
          printf("\x1b[0m");
          break;
        case PooSweeperStateBase::REVEALED_EIGHT:
          printf("\x1b[32;1m");
          printf("8");
          printf("\x1b[0m");
          break;
      }
    }
  }
  printf("\x1b[%d;%dH", state->numRows() + 2, 2);
  printf("Revealed: %u", state->numRevealed());
  printf("\x1b[%d;%dH", state->numRows() + 3, 2);
  printf("Marked: %u   ", state->numMarked());
  printf("\x1b[%d;%dH", state->numRows() + 4, 2);
  printf("Poos: %u", state->numPoos());
  // mvprintw(state->numRows() + 2, 2, "Revealed: %u", state->numRevealed());
  // refresh();
}
