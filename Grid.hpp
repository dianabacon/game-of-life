/*********************************************************************
 ** Program Filename: Grid.hpp, Grid class specification
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description:  Attributes and functions related to the game grid
 **   for the Game of Life.
 ** Input: dimensions of grid, number of hidden and boundary cells,
 **    and state of each grid cell (live or dead).
 ** Output:  Grid parameters, display grid to screen.
 *********************************************************************/

#ifndef Grid_hpp
#define Grid_hpp

#include <iostream> // header file for input and output stream objects

class Grid {
private:
    bool **state;   // 2D array with state of cell (1=live, 0=dead)
    int sizeX;      // x dimension of visible portion of array
    int sizeY;      // y dimension of visible portion of array
    int hide;       // number of extra cells to hide on each boundary
public:
    Grid(int,int);                  // constructor
    Grid();                         // default constructor
    ~Grid();                        // destructor
    void setState(int,int,bool);    // set state of a single cell
    bool getState(int,int);         // get state of a single cell
    void clearGrid();               // set state of all cells to zero
    int sumNeighbors(int,int);      // get sum of neighbor state
    int getSizeX();                 // get x dimension of visible portion
    int getSizeY();                 // get y dimension of visible portion
    int getHide();                  // get number of hidden cells
    void displayGrid();             // print all cell states to screen
};

#endif /* Grid_hpp */
