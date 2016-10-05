/*********************************************************************
 ** Program Filename: Game.hpp
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description: Game class specification, handles high-level control
 **   of the Game of Life
 ** Input: menu-driven user input
 ** Output: displays time step and simulation result
 *********************************************************************/

#ifndef Game_hpp
#define Game_hpp

#include <iostream> // header file for input and output stream objects
#include <string>   // header file for string objects
#include <cstdlib>  // header file for system clear
#include <limits>   // header file for properties of numeric types
#include "Grid.hpp"
#include "Seed.hpp"

class Game {
private:
    Grid oddGrid, evenGrid; // current grids for odd and even time steps
    std::string patternName;    // name of seed pattern
    int xLoc, yLoc;         // x and y coordinates to center pattern
    int tick;               // current time step
    Seed mySeed;            // object to hold seed pattern coordinates
public:
    Game();                 // default constructor
    int getUserInput();     // get user input
    void setSeed();         // apply seed pattern to grid
    void calcTick();        // calculate grid state at single time step
};

#endif /* Game_hpp */
