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
#include <vector>
#include "Graph.h"
#include "Vertex.h"

using namespace std;


// Namespace used for global variables
namespace prAstar
{
	const char* pTeamMembers{ "Adam McAree and Benjamin Kleynhans\n" };

	int** maze = nullptr;
	bool validMaze = false;

	int xCoords[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int yCoords[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int currentX = 0;
	int currentY = 0;

	int mazeRows = 0;
	int mazeColumns = 0;

	int listRows = 10;
	int listColumns = 10;

	int pXPosStart = -1;
	int pYPosStart = -1;
	bool startPosValid = false;

	int pXPosEnd = -1;
	int pYPosEnd = -1;
	bool endPosValid = false;

	bool pathCalculated = false;

	Vertex *startPosition = nullptr;
	Vertex *endPosition = nullptr;
	Vertex *currentPosition = nullptr;
	vector<Vertex> *path = new vector<Vertex>;
	int countPath = 0;
	Graph* graph = new Graph();

	bool returnValue;
}

void setHuristic(Vertex* currentV, Vertex* previousV)
{
	if (currentV->x - previousV->x != 0 && currentV->y - previousV->y != 0)
	{
		if (currentV->pathCost == -1 || previousV->pathCost + 14 < currentV->pathCost)
		{
			currentV->previousPoint = previousV;
			currentV->pathCost = previousV->pathCost + 14;
		}
	}
	else
	{
		if (currentV->pathCost == -1 || previousV->pathCost + 10 < currentV->pathCost)
		{
			currentV->previousPoint = previousV;
			currentV->pathCost = previousV->pathCost + 10;
		}
	}

	if (currentV->distanceToExit == -1)
	{
		int xDistance = abs(currentV->x - prAstar::endPosition->x);
		int yDistance = abs(currentV->y - prAstar::endPosition->y);
		if (xDistance > yDistance)
		{
			currentV->distanceToExit = yDistance * 14 + (xDistance - yDistance) * 10;
		}
		else
		{
			currentV->distanceToExit = xDistance * 14 + (yDistance - xDistance) * 10;
		}
	}

	currentV->heuristic = currentV->distanceToExit + currentV->pathCost;
	cout << "setHuristic";
}

//calculates the path using A*
void AstarAlgorithm()
{
	cout << "start astar";
	for (int i = 0; i < prAstar::graph->vertices.size(); i++)
	{
		if (prAstar::graph->vertices[i].x == prAstar::pXPosStart && prAstar::graph->vertices[i].y == prAstar::pYPosStart)
		{
			*prAstar::startPosition = prAstar::graph->vertices[i];
		}
		if (prAstar::graph->vertices[i].x == prAstar::pXPosEnd && prAstar::graph->vertices[i].y == prAstar::pYPosEnd)
		{
			*prAstar::endPosition = prAstar::graph->vertices[i];
		}
	}
	prAstar::startPosition->pathCost = 0;
	int xDistance = abs(prAstar::startPosition->x - prAstar::endPosition->x);
	int yDistance = abs(prAstar::startPosition->y - prAstar::endPosition->y);

	if (xDistance > yDistance)
	{
		prAstar::startPosition->distanceToExit = yDistance * 14 + (xDistance - yDistance) * 10;
	}
	else
	{
		prAstar::startPosition->distanceToExit = xDistance * 14 + (yDistance - xDistance) * 10;
	}

	prAstar::startPosition->heuristic = prAstar::startPosition->distanceToExit + prAstar::startPosition->pathCost;
	prAstar::startPosition->previousPoint = nullptr;

	prAstar::currentPosition = prAstar::startPosition;
	vector<Vertex> *lookedAtVertices = new vector<Vertex>;
	lookedAtVertices->push_back(*prAstar::currentPosition);

	
	while (prAstar::currentPosition != prAstar::endPosition)
	{

		for (int i = 0; i < prAstar::currentPosition->adjacentVertices.size(); i++)
		{
			if (prAstar::currentPosition->adjacentVertices[i]->previousPoint == nullptr)
			{
				prAstar::currentPosition->adjacentVertices[i]->previousPoint = prAstar::currentPosition;
			}
			if (prAstar::currentPosition->adjacentVertices[i] != prAstar::endPosition)
			{
				setHuristic(prAstar::currentPosition->adjacentVertices[i], prAstar::currentPosition);
			}
			lookedAtVertices->push_back(*prAstar::currentPosition->adjacentVertices[i]);
		}
		prAstar::currentPosition->completed = true;
		Vertex *nextNode = nullptr;
		for (int i = 0; i < lookedAtVertices->size(); i++)
		{
			if (nextNode == nullptr && (*lookedAtVertices)[i].completed == false)
			{
				*nextNode = (*lookedAtVertices)[i];
			}
			if ((*lookedAtVertices)[i] == *prAstar::endPosition || *nextNode == *prAstar::endPosition)
			{
				*nextNode = *prAstar::endPosition;
			}
			else if (nextNode->heuristic < (*lookedAtVertices)[i].heuristic && (*lookedAtVertices)[i].completed == false)
			{
				*nextNode = (*lookedAtVertices)[i];
			}
		}

		prAstar::currentPosition = nextNode;
	}

	vector<Vertex> *reversePath = new vector<Vertex>;

	while (prAstar::currentPosition != prAstar::startPosition)
	{
		reversePath->push_back(*prAstar::currentPosition);
		prAstar::currentPosition = prAstar::currentPosition->previousPoint;
	}

	for (int reverseCount = reversePath->size() - 1; reverseCount >= 0; reverseCount--)
	{
		prAstar::path->push_back((*reversePath)[reverseCount]);
	}
	cout << "end astar";
}



// Ben
// Returns a string that has both team members name.  Have the C string value 
// return both team member names.  There is no defined format for this.
__declspec(dllexport) char* GetTeam()
{
	cout << "getteam";
	return (char*)prAstar::pTeamMembers;
}

// Sets the maze data from the main program into the DLL.  Save the data into a 
// variable in the DLL.  Use this data for the GetMaze function.
__declspec(dllexport) bool SetMaze(const int** data, int width, int height)
{
	prAstar::returnValue = false;
	prAstar::pathCalculated = false;

	std::cout << " Start SetMaze " << std::endl;

	if ((!width <= 0) && (!height <= 0))
	{
		prAstar::mazeRows = width;
		prAstar::mazeColumns = height;

		prAstar::maze = new int*[prAstar::mazeRows];

		for (size_t i = 0; i < prAstar::mazeRows; i++)
		{
			prAstar::maze[i] = new int[prAstar::mazeColumns];
		}
		
		// Final project version
		try
		{
			for (size_t i = 0; i < prAstar::mazeRows; i++)
			{
				for (size_t j = 0; j < prAstar::mazeColumns; j++)
				{
					if ((data[i][j] == 0) || (data[i][j] == 1))
					{
						prAstar::maze[i][j] = data[i][j];
						if (prAstar::maze[i][j] == 0)
						{
							Vertex *v = new Vertex(i, j);
							prAstar::graph->vertices.push_back(*v);
						}
					}
					else
					{
						throw 1;
					}
				}
			}

			for (int i = 0; i < prAstar::graph->vertices.size(); i++)
			{
				for (int x = -1; x < 1; x++)
				{
					for (int y = -1; y < 1; y++)
					{
						Vertex *v = new Vertex(x + prAstar::graph->vertices[i].x, y + prAstar::graph->vertices[i].y);
						for (int j = 0; j < prAstar::graph->vertices.size(); j++)
						{
							if (v->x == prAstar::graph->vertices[j].x && v->y == prAstar::graph->vertices[j].y)
							{
								prAstar::graph->vertices[i].adjacentVertices.push_back(&prAstar::graph->vertices[j]);
							}
						}
						delete(v);
					}
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

	std::cout << " End SetMaze \n" << std::endl;

	

	//checks to see if conditions for calculating path are met
	if (prAstar::validMaze == true && prAstar::startPosValid == true && prAstar::endPosValid == true && prAstar::pathCalculated != true) 
	{
		AstarAlgorithm();
	}

	return prAstar::returnValue;
}

// Gets the maze data from the DLL.  Return the maze data that was passed in using 
// the SetMaze funtion, and the width/height using the references to the arguments.
__declspec(dllexport) int** GetMaze(int& width, int& height)
{
	std::cout << " Start GetMaze " << std::endl;

	height = prAstar::mazeColumns;
	width = prAstar::mazeRows;

	std::cout << " End GetMaze " << std::endl;

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
__declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos)
{
	prAstar::returnValue = true;

	if (prAstar::countPath < prAstar::path->size())
	{
		xpos = (*prAstar::path)[prAstar::countPath].x;
		ypos = (*prAstar::path)[prAstar::countPath].y;
		prAstar::countPath++;
	}
	else
	{
		xpos = prAstar::endPosition->x;
		ypos = prAstar::endPosition->y;
	}

	/*xpos = prAstar::xCoords[prAstar::currentX];
	ypos = prAstar::yCoords[prAstar::currentY];

	prAstar::currentX++;
	prAstar::currentY++;

	if ((prAstar::currentX == sizeof(prAstar::xCoords) / sizeof(int)) ||
		(prAstar::currentY == sizeof(prAstar::yCoords) / sizeof(int)))
	{
		prAstar::returnValue = false;
	}*/

	return prAstar::returnValue;
}

// Adam
// Sets the starting location for the player.  Save the x and y values for the start
// location.
__declspec(dllexport) bool SetStart(int xpos, int ypos)
{
	prAstar::startPosValid = false;
	prAstar::pathCalculated = false;

	if ((xpos >= prAstar::xCoords[0]) &&
		(xpos <= prAstar::xCoords[(sizeof(prAstar::xCoords) / sizeof(int)) - 1]) &&
		(ypos >= prAstar::yCoords[0]) &&
		(ypos <= prAstar::yCoords[(sizeof(prAstar::yCoords) / sizeof(int)) - 1]))
	{
		prAstar::pXPosStart = xpos;
		prAstar::pYPosStart = ypos;

		prAstar::startPosValid = true;
	}

	//checks to see if conditions for calculating path are met
	if (prAstar::validMaze == true && prAstar::startPosValid == true && prAstar::endPosValid == true && prAstar::pathCalculated != true)
	{
		AstarAlgorithm();
	}

	return prAstar::startPosValid;
}

// Adam
// Gets the starting location for the player.  Return the saved x and y starting locations.
// If the x and y locations for the start have not been saved yet, then return -1 for both.
__declspec(dllexport) bool GetStart(int& xpos, int& ypos)
{
	if (prAstar::startPosValid)
	{
		xpos = prAstar::pXPosStart;
		ypos = prAstar::pYPosStart;
	}

	return  prAstar::startPosValid;
}

// Ben
// Sets the ending location for the player.  Save the x and y values for the ending location.
__declspec(dllexport) bool SetEnd(int xpos, int ypos)
{

	prAstar::endPosValid = false;
	prAstar::pathCalculated = false;

	if ((xpos >= prAstar::xCoords[0]) &&
		(xpos <= prAstar::xCoords[(sizeof(prAstar::xCoords) / sizeof(int)) - 1]) &&
		(ypos >= prAstar::yCoords[0]) &&
		(ypos <= prAstar::yCoords[(sizeof(prAstar::yCoords) / sizeof(int)) - 1]))
	{
		prAstar::pXPosEnd = xpos;
		prAstar::pYPosEnd = ypos;
		prAstar::endPosValid = true;
	}

	//checks to see if conditions for calculating path are met
	if (prAstar::validMaze == true && prAstar::startPosValid == true && prAstar::endPosValid == true && prAstar::pathCalculated != true)
	{
		AstarAlgorithm();
	}

	return prAstar::endPosValid;
}

// Ben
// Gets the ending location for the player. Return the saved x and y end locations.  If the
// x and y locations for the end have not been saved yet, then return -1 for both.
__declspec(dllexport) bool GetEnd(int& xpos, int& ypos)
{
	if (prAstar::endPosValid)
	{
		xpos = prAstar::pXPosEnd;
		ypos = prAstar::pYPosEnd;
	}

	return prAstar::endPosValid;
}

// Move the player back to the staring position
__declspec(dllexport) bool Restart()
{
	if (prAstar::currentX = -1)
	{
		return false;
	}
	prAstar::currentX = prAstar::pXPosStart;
	prAstar::currentY = prAstar::pYPosStart;
	return true;
}