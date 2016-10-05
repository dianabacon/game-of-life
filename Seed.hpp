/*********************************************************************
 ** Program Filename: Seed.hpp, Seed class specification
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description: Attributes and functions of a seed pattern that can
 **   be used as the initial condition for a Game of Life simulation.
 ** Input: Reads seed pattern from a standard text file format
 ** Output: Extent and size of pattern, live cell coordinates
 *********************************************************************/

#ifndef Seed_hpp
#define Seed_hpp

#include <fstream>
#include <vector>
#include <algorithm>

class Seed {
private:
    struct coord {
        int x,y;    // x and y coordinates
    };
    std::vector<coord> pattern; // coordinates of live cells
    int sizeX;  // extent of pattern in the x direction
    int sizeY;  // extent of pattern in the y direction
    int length; // number of live cells in the pattern
    static bool byX(coord, coord); // compares the x coordinates
    static bool byY(coord, coord); // compares the y coordinates
public:
    Seed();     // constructor
    void readFile(std::string); // read seed pattern from file.
    int getSizeX(); // get extent of pattern in the x direction
    int getSizeY(); // extent of pattern in the y direction
    int getLength(); // get the number of live cells in the pattern
    int getX(int);  // get the x coordinate of a coordinate pair
    int getY(int);  // get the y coordinate of a coordinate pair
};

#endif /* Seed_hpp */
