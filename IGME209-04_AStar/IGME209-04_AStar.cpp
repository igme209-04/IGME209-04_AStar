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
#include <map>
#include "Graph.h"

using namespace std;

void ProcessPath();
void VerifyRequirements();

// Namespace used for global variables
namespace prAstar
{
	const char* pTeamMembers{ "Adam McAree and Benjamin Kleynhans\n" };

	int** maze = nullptr;
	bool validMaze = false;

	int** shortestPath = nullptr;
	int pathSize = 0;

	int currentStep = 0;

	int mazeRows = 0;
	int mazeColumns = 0;
	bool mazeSet = false;

	int listRows = 10;
	int listColumns = 10;

	int pPosStart[2] = { -1, -1 };
	bool startPosValid = false;
	bool startPosSet = false;

	int pPosEnd[2] = { -1, -1 };
	bool endPosValid = false;
	bool endPosSet = false;

	bool dataReady = false;
	bool dataProcessed = false;

	bool returnValue;
}

// Ben
// Returns a string that has both team members name.  Have the C string value 
// return both team member names.  There is no defined format for this.
extern "C" __declspec(dllexport) char* GetTeam()
{
	return (char*)prAstar::pTeamMembers;
}

// Sets the maze data from the main program into the DLL.  Save the data into a 
// variable in the DLL.  Use this data for the GetMaze function.
extern "C" __declspec(dllexport) bool SetMaze(const int** data, int width, int height)
{
	prAstar::mazeSet = false;
	prAstar::returnValue = false;
	prAstar::dataProcessed = false;

	if (!(width <= 0) && !(height <= 0))
	{
		prAstar::mazeRows = width;
		prAstar::mazeColumns = height;

		prAstar::maze = new int*[prAstar::mazeRows];

		for (int i = 0; i < prAstar::mazeRows; i++)
		{
			prAstar::maze[i] = new int[prAstar::mazeColumns];
		}

		// Final project version
		try
		{
			for (int i = 0; i < prAstar::mazeRows; i++)
			{
				for (int j = 0; j < prAstar::mazeColumns; j++)
				{
					prAstar::maze[i][j] = data[i][j];
				}
			}

			prAstar::returnValue = true;
			prAstar::validMaze = true;
		}
		catch (int e)
		{
			std::cout << "An exception occurred.  Exception Nr. " << e << '\n';
		}
	}

	prAstar::mazeSet = true;

	VerifyRequirements();

	if (prAstar::dataReady && !prAstar::dataProcessed)
	{
		ProcessPath();
		prAstar::dataProcessed = true;
	}

	return prAstar::returnValue;
}

// Gets the maze data from the DLL.  Return the maze data that was passed in using 
// the SetMaze funtion, and the width/height using the references to the arguments.
extern "C" __declspec(dllexport) int** GetMaze(int& width, int& height)
{
	height = prAstar::mazeColumns;
	width = prAstar::mazeRows;

	if (prAstar::validMaze)
	{
		return prAstar::maze;
	}
	else
	{
		return nullptr;
	}

}

// Returns the next x/y position to move to.  For this first part, save a list of
// x and y values (at least 10) and then keep track of which is your current location.
// Return those variables for the current position.
extern "C" __declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos)
{
	prAstar::returnValue = true;

	if ((prAstar::shortestPath != nullptr) && (prAstar::currentStep != prAstar::pathSize))
	{
		xpos = prAstar::shortestPath[prAstar::currentStep][0];
		ypos = prAstar::shortestPath[prAstar::currentStep][1];

		prAstar::currentStep++;
	}
	else
	{
		xpos = prAstar::pPosStart[0];
		ypos = prAstar::pPosStart[1];

		prAstar::returnValue = false;
	}

	return prAstar::returnValue;
}

// Adam
// Sets the starting location for the player.  Save the x and y values for the start
// location.
extern "C" __declspec(dllexport) bool SetStart(int xpos, int ypos)
{
	prAstar::startPosSet = false;
	prAstar::startPosValid = false;
	prAstar::dataProcessed = false;

	if ((xpos >= 0) &&
		(xpos <= prAstar::mazeColumns) &&
		(ypos >= 0) &&
		(ypos <= prAstar::mazeRows))
	{
		prAstar::pPosStart[0] = xpos;
		prAstar::pPosStart[1] = ypos;

		prAstar::startPosValid = true;
	}

	prAstar::startPosSet = true;

	VerifyRequirements();

	if (prAstar::dataReady && !prAstar::dataProcessed)
	{
		ProcessPath();
		prAstar::dataProcessed = true;
	}

	return prAstar::startPosValid;
}

// Adam
// Gets the starting location for the player.  Return the saved x and y starting locations.
// If the x and y locations for the start have not been saved yet, then return -1 for both.
extern "C" __declspec(dllexport) bool GetStart(int& xpos, int& ypos)
{
	if (prAstar::startPosValid)
	{
		xpos = prAstar::pPosStart[0];
		ypos = prAstar::pPosStart[1];
	}

	return  prAstar::startPosValid;
}

// Ben
// Sets the ending location for the player.  Save the x and y values for the ending location.
extern "C" __declspec(dllexport) bool SetEnd(int xpos, int ypos)
{
	prAstar::endPosValid = false;
	prAstar::endPosSet = false;
	prAstar::dataProcessed = false;

	if ((xpos >= 0) &&
		(xpos <= prAstar::mazeColumns) &&
		(ypos >= 0) &&
		(ypos <= prAstar::mazeRows))
	{
		prAstar::pPosEnd[0] = xpos;
		prAstar::pPosEnd[1] = ypos;

		prAstar::endPosValid = true;
	}

	prAstar::endPosSet = true;

	VerifyRequirements();

	if (prAstar::dataReady && !prAstar::dataProcessed)
	{
		ProcessPath();
		prAstar::dataProcessed = true;
	}

	return prAstar::endPosValid;
}

// Ben
// Gets the ending location for the player. Return the saved x and y end locations.  If the
// x and y locations for the end have not been saved yet, then return -1 for both.
extern "C" __declspec(dllexport) bool GetEnd(int& xpos, int& ypos)
{
	if (prAstar::endPosValid)
	{
		xpos = prAstar::pPosEnd[0];
		ypos = prAstar::pPosEnd[1];
	}

	return prAstar::endPosValid;
}

// Move the player back to the staring position
extern "C" __declspec(dllexport) bool Restart()
{
	prAstar::currentStep = 0;

	return true;
}

void VerifyRequirements()
{
	if (prAstar::startPosSet && prAstar::endPosSet && prAstar::mazeSet)
	{
		prAstar::dataReady = true;
	}
}

void ProcessPath()
{
	Graph* pGraph = new Graph((const int**)prAstar::maze, prAstar::mazeRows, prAstar::mazeColumns);
	pGraph->CalculateShortestPath(prAstar::pPosStart, prAstar::pPosEnd);
	prAstar::pathSize = pGraph->closestVertices.size();

	prAstar::shortestPath = new int*[prAstar::pathSize];

	for (int i = 0; i < prAstar::pathSize; i++)
	{
		prAstar::shortestPath[i] = new int[2];
	}

	for (int i = 0; i < prAstar::pathSize; i++)
	{
		prAstar::shortestPath[i][0] = pGraph->shortestPath[i][0];
		prAstar::shortestPath[i][1] = pGraph->shortestPath[i][1];
	}

	for (int i = 0; i < prAstar::pathSize; i++)
	{
		delete(pGraph->shortestPath[i]);
	}

	// Still need to delete the returned array.

	delete(pGraph);
}