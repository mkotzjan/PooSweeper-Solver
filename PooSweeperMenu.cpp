// Copyright 2014, University of Freiburg
// Author: Michael Kotzjan

#include <ncurses.h>
#include "./PooSweeperMenu.h"
#include "./PooSweeperStateBase.h"
#include "./PooSweeper.h"

// _____________________________________________________________________________
PooSweeperMenu::PooSweeperMenu() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  exit = false;
}

// _____________________________________________________________________________
void PooSweeperMenu::startScreen() {
  while (true) {
    mvprintw(1, 2, "PooSweeper");
    mvprintw(3, 1, "Choose Difficulty:");
    mvprintw(5, 2, "Beginner");
    mvprintw(7, 2, "Intermediate");
    mvprintw(9, 2, "Expert");
    refresh();
    MEVENT start;
    mousemask(ALL_MOUSE_EVENTS, NULL);
    keypad(stdscr, TRUE);
    size_t ch = getch();
    if (getmouse(&start) == OK) {
      if (start.bstate & BUTTON1_CLICKED) {
        if (start.y == 5) {
          _rows = 9;
          _cols = 9;
          _poos = 10;
          break;
        } else if (start.y == 7) {
          _rows = 16;
          _cols = 16;
          _poos = 40;
          break;
        } else if (start.y == 9) {
          _rows = 16;
          _cols = 30;
          _poos = 99;
          break;
        }
      }
    }
  }
  clear();
  PooSweeper pooSweeper;
  pooSweeper.play(_rows, _cols, _poos);
}

// _____________________________________________________________________________
void PooSweeperMenu::endScreen() {
  while (true) {
    if (POO->status() == PooSweeperStateBase::WON) {
      mvprintw(_rows / 2, _cols + 2, "You've won!");
    } else {
      mvprintw(_rows / 2, _cols + 2, "You've lost");
    }
    mvprintw((_rows / 2) + 1, _cols + 2, "Do you want to play again? [y/n]");
    refresh();
    int end = getch();
    if (end == 'y') break;
    if (end == 'n') {
      exit = true;
      break;
    }
  }
  clear();
}

// _____________________________________________________________________________
PooSweeperMenu::~PooSweeperMenu() {
  endwin();
}
