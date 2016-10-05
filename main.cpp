/*********************************************************************
 ** Program Filename: main.cpp
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description: Main program for Game of Life
 ** Input:  The user chooses from a menu of starting patterns and
 **         specifies the starting location and number of time steps.
 ** Output: Animation showing the evolution of the pattern with time.
 *********************************************************************/

#include <iostream>
#include "Game.hpp"


int main(int argc, const char * argv[]) {
    
    int nticks; // number of time steps (ticks)
    char again; // Loop again? Y or N
    
    // create a new game
    Game myGame;
    std::cout << "*** Welcome to the Game of Life ***" << std::endl;
    std::cout << std::endl;
    
    do {
        // get user input
        nticks = myGame.getUserInput();
        
        // set the starting pattern
        myGame.setSeed();
        
        // run for specified number of time steps (ticks)
        for (int t = 0; t < nticks; t++) {
            myGame.calcTick();
        }
        
        std::cout << "Do you want to try another pattern? (Y/N) ";
        std::cin >> again;
        
    } while (again == 'Y' || again == 'y');
    
    return 0;
}
