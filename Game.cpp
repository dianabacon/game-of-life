/*********************************************************************
 ** Program Filename: Game.cpp
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description: Game class implementation, handles high-level control
 **   of the Game of Life
 ** Input: menu-driven user input
 ** Output: displays time step and simulation result
 *********************************************************************/

#include "Game.hpp"

/*********************************************************************
 ** Function:  Game
 ** Description:  Game class default constructor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions:  Two grid objects are created and other attributes
 **   are initialized.
 *********************************************************************/

Game::Game() {
    Grid oddGrid(40,20);  // current grid for odd time steps
    Grid evenGrid(40,20); // current grid for even time steps
    patternName = "";     // pattern name
    xLoc = 20;          // x coordinate for centerpoint of seed pattern
    yLoc = 10;          // y coordinate for centerpoint of seed pattern
    tick = 0;           // initial time step
}


/*********************************************************************
 ** Function: getUserInput
 ** Description: Get user choice of starting pattern and location via
 **   interactive menu.  Reads pattern from a file, determines
 **   dimensions of pattern, and limits choice of starting location
 **   accordingly so that pattern will not be written to an out of
 **   memory location.
 ** Parameters: none
 ** Pre-Conditions:  Pattern files must exist in same directory, a 
 **   Seed object named mySeed, a string named pattern,  and integer
 **    variables xLoc and yLoc must exist.
 ** Post-Conditions:  Pattern coordinates will be stored in the Seed
 **   object, and starting coordinates wil be stored in variables
 **   xLoc and yLoc.  Returns the number of time steps to run.
 *********************************************************************/

int Game::getUserInput() {
    int choice = 1;
    
    // display a menu and get user choice of starting pattern
    std::cout << "Choose a seed pattern:" << std::endl;
    std::cout << "1) Blinker" << std::endl;
    std::cout << "2) Glider" << std::endl;
    std::cout << "3) Gosper Glider Gun" << std::endl;
    std::cout << "Enter a value from 1 to 3: ";
    std::cin >> choice;
    while ((choice < 1) || (choice > 3))
    {
        std::cout << "ERROR: Enter a value from 1 to 3: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;
    }
    switch (choice) {
        case 1:
            patternName = "blinker";
            break;
        case 2:
            patternName = "glider";
            break;
        case 3:
            patternName = "gosperglidergun";
            break;
            
        default:
            break;
    }
    
    // read pattern file
    mySeed.readFile(patternName);
    std::cout << std::endl;
    std::cout << "The dimensions of the seed pattern are ";
    std::cout << mySeed.getSizeX() << " x " << mySeed.getSizeY() << std::endl;

    // calculate safe range for starting location
    int x1 = mySeed.getSizeX()/2 + 1;
    int x2 = evenGrid.getSizeX() - mySeed.getSizeX()/2;
    int y1 = mySeed.getSizeY()/2 + 1;
    int y2 = evenGrid.getSizeY() - mySeed.getSizeY()/2;
    
    // display a menu and get user choice of starting location
    std::cout << std::endl;
    std::cout << "Choose location to center the seed pattern: ";
    std::cout << std::endl;
    std::cout << "Enter a horizontal coordinate from ";
    std::cout << x1 << " to ";
    std::cout << x2;
    std::cout << " (left to right): ";
    std::cin >> xLoc;
    while ((xLoc < x1) || (xLoc > x2))
    {
        std::cout << "ERROR: Enter a value from " ;
        std::cout << x1 << " to ";
        std::cout << x2 << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> xLoc;
    }
    std::cout << std::endl;
    std::cout << "Enter a vertical coordinate from ";
    std::cout << y1 << " to ";
    std::cout << y2;
    std::cout << " (top to bottom): ";
    std::cin >> yLoc;
    while ((yLoc < y1) || (yLoc > y2))
    {
        std::cout << "ERROR: Enter a value from " ;
        std::cout << y1 << " to ";
        std::cout << y2 << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> yLoc;
    }
    
    // adjust location to account for hidden cells
    xLoc = xLoc + evenGrid.getHide();
    yLoc = yLoc + evenGrid.getHide();
    
    // get user choice of number of time steps
    int nsteps;
    std::cout << std::endl;
    std::cout << "Enter number of time steps (ticks): ";
    std::cin >> nsteps;
    while (nsteps < 1)
    {
        std::cout << "ERROR: Please enter a positive number" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> nsteps;
    }
    return nsteps;
}


/*********************************************************************
 ** Function: setSeed
 ** Description: Apply seed pattern to grid at specified location and
 **   display time step and grid state to screen.
 ** Parameters: A seed object and a grid object.
 ** Pre-Conditions: A seed object named mySeed must contain coordinates
 **   of starting pattern.  A grid object named evenGrid must exist.
 **   The seed pattern must not be larger than the grid.
 ** Post-Conditions: The initial time step and grid state will be 
 **   displayed.
 *********************************************************************/

void Game::setSeed(){
    
    // set time step to zero and fill grid with zeros
    tick = 0;
    evenGrid.clearGrid();
    
    // apply the starting pattern to the grid
    for (int i = 0; i < mySeed.getLength(); i++) {
        evenGrid.setState(xLoc + mySeed.getX(i),
                          yLoc + mySeed.getY(i), 1);
    }
    
    // display the result
    system("clear");
    std::cout << "Tick = " << tick << std::endl;
    evenGrid.displayGrid();
    usleep(1000000); // pause for 1 second
}


/*********************************************************************
 ** Function: calcTick
 ** Description: Calculate and display grid state at a single time 
 **   step.
 ** Parameters: none
 ** Pre-Conditions:  Grid objects named evenGrid and oddGrid must
 **   exist.
 ** Post-Conditions: The current time step and grid state will be
 **   displayed.
 *********************************************************************/

void Game::calcTick() {
    
    // determine which grid is current based on time step
    Grid *current;
    Grid *future;
    if (tick % 2 == 0) {    // time step is even
        current = &evenGrid;
        future = &oddGrid;
    } else {
        current = &oddGrid;
        future  = &evenGrid;
    }
    
    // calculate future state
    int myNeighbors, myState;
    int jmax = current->getSizeY()+2*current->getHide();
    int imax = current->getSizeX()+2*current->getHide();
    for (int j = 1; j <= jmax; j++) {
        for (int i = 1; i <= imax; i++) {
            myNeighbors = current->sumNeighbors(i, j);
            myState = current->getState(i, j);
            future->setState(i, j, 0);
            if (myNeighbors == 3 || (myNeighbors == 2 && myState == 1) ) {
                future->setState(i, j, 1);
            }
        }
    }
    
    // display the result
    tick++;
    system("clear");
    std::cout << "Tick = " << tick << std::endl;
    future->displayGrid();
    usleep(100000);  // pause for 0.1 second
}
