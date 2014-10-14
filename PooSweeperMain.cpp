// Copyright 2014, University of Freiburg.
// Michael Kotzjan

#include "./PooSweeperMenu.h"

// Main function
int main(int argc, char** argv) {
  PooSweeperMenu menu;
  while (true) {
    menu.startScreen();
    menu.endScreen();
    if (menu.exit == true) break;
  }
}
