/// 
/// IGME-209.04 - Data Structures and Algorithms
/// 
/// Project 1           :  A* algorithm DLL for use in other programs
/// 
/// Class Description   : Some debugging exercises.
/// Created By          : Benjamin Kleynhans - bxk8027@rit.edu
///                       Adam McAree - arm1686@g.rit.edu
/// Date Created        : February 6, 2019
/// Last Modified By    : Benjamin Kleynhans
/// Date Modified       : February 6, 2019
/// Filename            : PR-AStar.cpp
///

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Item
{
public:
    int value;
};

// Namespace used for global variables
namespace prAstar
{
    //const char teamMembers[60] { "The team members are Adam McAree and Benjamin Kleynhans" };
    //char* pTeamMembers = (char*)&teamMembers;

    const char* pTeamMembers { "The team members are Adam McAree and Benjamin Kleynhans" };

    Item** maze = nullptr;

    int mazeRows = 0;
    int mazeColumns = 0;

    int pXPosStart = 0;
    int pYPosStart = 0;

    int pXPosEnd = 0;
    int pYPosEnd = 0;
}

// Ben
// Returns a string that has both team members name.  Have the C string value 
// return both team member names.  There is no defined format for this.
__declspec(dllexport) char* GetTeam()
{   
    //return prAstar::pTeamMembers;
    return (char*)prAstar::pTeamMembers;
}

// Sets the maze data from the main program into the DLL.  Save the data into a 
// variable in the DLL.  Use this data for the GetMaze function.
__declspec(dllexport) void SetMaze(const int** data, int width, int height)
{
    prAstar::mazeRows = height;
    prAstar::mazeColumns = width;    
    
    prAstar::maze = new Item*[prAstar::mazeRows];

    for (size_t i = 0; i < prAstar::mazeRows; i++)
    {
        prAstar::maze[i] = new Item[prAstar::mazeColumns];
    }

    for (size_t i = 0; i < prAstar::mazeRows; i++)
    {
        for (size_t j = 0; j < prAstar::mazeColumns; j++)
        {
            prAstar::maze[i][j].value = data[i][j];
        }
    }

    std::cout << std::endl;
}

// Gets the maze data from the DLL.  Return the maze data that was passed in using 
// the SetMaze funtion, and the width/height using the references to the arguments.
__declspec(dllexport) int** GetMaze(int& width, int& height)
{
    int** maze = nullptr;



    return maze;
}

// Returns the next x/y position to move to.  For this first part, save a list of
// x and y values (at least 10) and then keep track of which is your current location.
// Return those variables for the current position.
__declspec(dllexport) void GetNextPosition(int& xpos, int& ypos)
{

}

// Adam
// Sets the starting location for the player.  Save the x and y values for the start
// location.
__declspec(dllexport) void SetStart(int xpos, int ypos)
{

}

// Adam
// Gets the starting location for the player.  Return the saved x and y starting locations.
// If the x and y locations for the start have not been saved yet, then return -1 for both.
__declspec(dllexport) void GetStart(int& xpos, int& ypos)
{

}

// Ben
// Sets the ending location for the player.  Save the x and y values for the ending location.
__declspec(dllexport) void SetEnd(int xpos, int ypos)
{
    prAstar::pXPosEnd = xpos;
    prAstar::pYPosEnd = ypos;
}

// Ben
// Gets the ending location for the player. Return the saved x and y end locations.  If the
// x and y locations for the end have not been saved yet, then return -1 for both.
__declspec(dllexport) void GetEnd(int& xpos, int& ypos)
{
    xpos = prAstar::pXPosEnd;
    ypos = prAstar::pYPosEnd;
}