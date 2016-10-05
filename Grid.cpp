/*********************************************************************
 ** Program Filename: Grid.cpp, Grid class implementation
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description:  Attributes and functions related to the game grid
 **   for the Game of Life.
 ** Input: dimensions of grid, number of hidden and boundary cells,
 **    and state of each grid cell
 ** Output:  Grid parameters, display grid to screen
 *********************************************************************/

#include "Grid.hpp"

// constructor (nrow x ncol grid with boundary and hidden cells)
Grid::Grid(int ncol, int nrow) {
    sizeX = ncol;
    sizeY = nrow;
    hide = 4;
    state = new bool*[sizeX+2*(hide+1)];
    for (int i = 0; i < sizeX+2*(hide+1); i++) {
        state[i] = new bool[sizeY+2*(hide+1)];
    }
    clearGrid();
}

// default constructor (40 x 20 grid with boundary and hidden cells)
Grid::Grid(){
    sizeX = 40;
    sizeY = 20;
    hide = 4;
    state = new bool*[sizeX+2*(hide+1)];
    for (int i = 0; i < sizeX+2*(hide+1); i++) {
        state[i] = new bool[sizeY+2*(hide+1)];
    }
    clearGrid();
}

// destructor, deallocate memory
Grid::~Grid() {
    for (int i = 0; i < sizeX+2*(hide+1); i++) {
        delete [] state[i];
    }
    delete [] state;
}

// set grid cell state
void Grid::setState(int i, int j, bool s) {
    state[i][j] = s;
}

// return grid cell state
bool Grid::getState(int i, int j){
    return state[i][j];
}

// set all grid states to zero
void Grid::clearGrid() {
    for (int i = 0; i < sizeX+2*(hide+1); i++) {
        for (int j = 0; j < sizeY+2*(hide+1); j++) {
            setState(i, j, 0);
        }
    }
}

// return sum of neigbor cell states
int Grid::sumNeighbors(int i, int j){
    return state[i-1][j+1] + state[i+1][j+1] +
            state[i-1][j] + state[i+1][j] +
            state[i-1][j-1] + state[i+1][j-1] +
            state[i][j+1] + state[i][j-1];
}

// get visible X dimension of grid
int Grid::getSizeX(){
    return sizeX;
}

// get visible Y dimension of grid
int Grid::getSizeY(){
    return sizeY;
}

// get number of hidden cells at boundary
int Grid::getHide(){
    return hide;
}
// print grid to screen
void Grid::displayGrid() {
    
    // display the grid
    for (int j = 1 + hide; j <= sizeY + hide; j++) {
        for (int i = 1 + hide; i <= sizeX + hide; i++) {
            if (state[i][j] == 1) {
                std::cout << '@';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

