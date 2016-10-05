/*********************************************************************
 ** Program Filename: Seed.cpp, Seed class implementation
 ** Author: Diana Bacon
 ** Date: 2015-09-26
 ** Description: Attributes and functions of a seed pattern that can
 **   be used as the initial condition for a Game of Life simulation.
 ** Input: Reads seed pattern from a standard text file format
 ** Output: Extent and size of pattern, live cell coordinates
 *********************************************************************/

#include "Seed.hpp"

/*********************************************************************
 ** Function:  Seed
 ** Description: Seed class default constructor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: A seed object is created and its attributes
 **   are initialized.  
 *********************************************************************/

Seed::Seed() {
    sizeX = 0;      // extent of pattern in the x direction
    sizeY = 0;      // extent of pattern in the y direction
    length = 0;     // number of live cell coordinates in the pattern
}


/*********************************************************************
 ** Function: readFile
 ** Description: Read seed pattern from Life 1.06 format text file.
 ** Parameters: String with name of seed pattern.
 ** Pre-Conditions: The requested *.lif file must be in the same 
 **   directory as the executable.
 ** Post-Conditions:  The coordinates of the live cells in the pattern
 **   will be read into a vector.
 *********************************************************************/

void Seed::readFile(std::string name) {
        
    // open the file
    std::string fileName = name + "_106.lif";
    std::ifstream inputFile;
    inputFile.open(fileName.c_str());
    
    // read the header line
    std::string header;
    getline(inputFile,header);
    
    // read the coordinates from file
    coord myCoord;
    pattern.clear();
    while (inputFile >> myCoord.x >> myCoord.y) {
        pattern.push_back(myCoord);
    }
    inputFile.close();
    
    // calculate the length of the pattern and extent in x and y dimensions
    std::sort(pattern.begin(), pattern.end(), byX);
    sizeX = pattern.back().x - pattern.front().x + 1;
    std::sort(pattern.begin(), pattern.end(), byY);
    sizeY = pattern.back().y - pattern.front().y + 1;
    length = static_cast<int>(pattern.size());
}


/*********************************************************************
 ** Function: byX
 ** Description:  Compares the x coordinates of two points.
 ** Parameters:  The coordinates of two points.
 ** Pre-Conditions:  The coordinates must have been initialized.
 ** Post-Conditions: Returns true if the first x coordinate is larger
 *    than the second, false otherwise.
 *********************************************************************/

bool Seed::byX(coord c1, coord c2) {
    return (c1.x < c2.x);
}


/*********************************************************************
 ** Function: byY
 ** Description:  Compares the y coordinates of two points.
 ** Parameters:  The coordinates of two points.
 ** Pre-Conditions:  The coordinates must have been initialized.
 ** Post-Conditions: Returns true if the first y coordinate is larger
 *    than the second, false otherwise.
 *********************************************************************/

bool Seed::byY(coord c1, coord c2) {
    return (c1.y < c2.y);
}


/*********************************************************************
 ** Function: getLength
 ** Description: Get the number of live cells in the pattern.
 ** Parameters: none
 ** Pre-Conditions:  The seed pattern object must exist and have read
 **   its coordinates from a file.
 ** Post-Conditions: Returns the number of live cells in the pattern.
 *********************************************************************/

int Seed::getLength() {
    return length;
}


/*********************************************************************
 ** Function: getSizeX
 ** Description:  Get the extent of the pattern in the x direction.
 ** Parameters:
 ** Pre-Conditions:  The seed pattern object must exist and have read
 **   its coordinates from a file.
 ** Post-Conditions: Returns the extent of the pattern in the x
 **   direction.
 *********************************************************************/

int Seed::getSizeX() {
    return sizeX;
}


/*********************************************************************
 ** Function: getSizeY
 ** Description: Get the extent of the pattern in the y direction.
 ** Parameters: none
 ** Pre-Conditions:  The seed pattern object must exist and have read
 **   its coordinates from a file.
 ** Post-Conditions: Returns the extent of the pattern in the y 
 **   direction.
 *********************************************************************/

int Seed::getSizeY() {
    return sizeY;
}


/*********************************************************************
 ** Function: getX
 ** Description:  Get the x coordinate of a coordinate pair.
 ** Parameters:  The index number of the coordinate pair.
 ** Pre-Conditions:  The seed pattern object must exist and have read
 **   its coordinates from a file.
 ** Post-Conditions:  Returns the x coordinate of a single live cell
 **   in the pattern.
 *********************************************************************/

int Seed::getX(int i) {
    return pattern.at(i).x;
}


/*********************************************************************
 ** Function: getY
 ** Description:  Get the y coordinate of a coordinate pair.
 ** Parameters:  The index number of the coordinate pair.
 ** Pre-Conditions:  The seed pattern object must exist and have read
 **   its coordinates from a file.
 ** Post-Conditions:  Returns the y coordinate of a single live cell
 **   in the pattern.
 *********************************************************************/

int Seed::getY(int i) {
    return pattern.at(i).y;
}
