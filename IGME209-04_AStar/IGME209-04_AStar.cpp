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

	int xCoords[10]{ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int yCoords[10]{ 0, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

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
	vector<Vertex *> path;
	int countPath = 0;
	Graph* graph = new Graph();
	bool returnValue;
}

//Calculates the Huristic value
void setHeuristic(Vertex* currentV, Vertex* previousV)
{
	//cout << "setHuristic test 1" << endl;
	if (currentV->x - previousV->x != 0 && currentV->y - previousV->y != 0)
	{
		if (currentV->pathCost == -1 || previousV->pathCost + 14 < currentV->pathCost)
		{
			currentV->previousPoint = previousV;
			currentV->pathCost = previousV->pathCost + 10;
		}
		//cout << "setHuristic test 2" << endl;
	}
	else
	{
		if (currentV->pathCost == -1 || previousV->pathCost + 10 < currentV->pathCost)
		{
			currentV->previousPoint = previousV;
			currentV->pathCost = previousV->pathCost + 10;
		}
		//cout << "setHuristic test 3" << endl;
	}
	//cout << "setHuristic test 4" << endl;
	if (currentV->distanceToExit == -1)
	{
		int xDistance = abs(currentV->x - prAstar::endPosition->x);
		int yDistance = abs(currentV->y - prAstar::endPosition->y);
		if (xDistance > yDistance)
		{
			currentV->distanceToExit = yDistance * 10 + (xDistance - yDistance) * 10;
		}
		else
		{
			currentV->distanceToExit = xDistance * 10 + (yDistance - xDistance) * 10;
		}
		//cout << "setHuristic test 5" << endl;
	}
	//cout << "setHuristic test 6" << endl;
	currentV->heuristic = currentV->distanceToExit + currentV->pathCost;
	//cout << "setHuristic";
}

//calculates the path using A*
void AstarAlgorithm()
{
	//cout << endl << "start astar" << endl;
	cout << "Size of graph: " << prAstar::graph->vertices.size() << endl;

	//sets the startPosition and the endPosition
	for (int i = 0; i < prAstar::graph->vertices.size(); i++)
	{
		cout << "x: " << prAstar::graph->vertices[i]->x << " y: " << prAstar::graph->vertices[i]->y << endl;
		if (prAstar::graph->vertices[i]->x == prAstar::pXPosStart && prAstar::graph->vertices[i]->y == prAstar::pYPosStart)
		{
			prAstar::startPosition = prAstar::graph->vertices[i];
			//cout << "start set" << endl;
		}
		if (prAstar::graph->vertices[i]->x == prAstar::pXPosEnd && prAstar::graph->vertices[i]->y == prAstar::pYPosEnd)
		{
			
			prAstar::endPosition = prAstar::graph->vertices[i];
			//cout << "end set" << endl;
		}
	}

	//cout << "end and start set" << endl;
	//cout << "end x : " << prAstar::endPosition->x << endl;
	//cout << "start x: " << prAstar::startPosition->x << " start y: " << prAstar::startPosition->y << endl;

	//gets the startPosition and current Position ready for the loop
	prAstar::startPosition->pathCost = 0;
	//cout << "is this where it ends" << endl;
	int xDistance = abs(prAstar::startPosition->x - prAstar::endPosition->x);
	int yDistance = abs(prAstar::startPosition->y - prAstar::endPosition->y);
	//cout << "is this where it ends" << endl;
	if (xDistance > yDistance)
	{
		//cout << "is this where it ends" << endl;
		prAstar::startPosition->distanceToExit = yDistance * 14 + (xDistance - yDistance) * 10;
	}
	else
	{
		//cout << "is this where it ends" << endl;
		prAstar::startPosition->distanceToExit = xDistance * 14 + (yDistance - xDistance) * 10;
	}

	cout << endl << "x: " << prAstar::startPosition->x << " y: " << prAstar::startPosition->y << endl;
	
	prAstar::startPosition->heuristic = prAstar::startPosition->distanceToExit + prAstar::startPosition->pathCost;
	prAstar::startPosition->previousPoint = nullptr;

	prAstar::currentPosition = prAstar::startPosition;
	cout << "Current x: " << prAstar::currentPosition->x << " y: " << prAstar::currentPosition->y << endl;
	vector<Vertex *> lookedAtVertices;
	lookedAtVertices.push_back(prAstar::currentPosition);
	//cout << "time for loop" << endl;
	bool foundEnd = false;
	int count = 0;
	//loops until the end is found
	while (prAstar::currentPosition != prAstar::endPosition)
	{
		cout << count<< "Adjacency amount: " << prAstar::currentPosition->adjacentVertices.size() << endl << endl << endl;
		//checks each adjacent vertex from current vertex
		for (int i = 0; i < prAstar::currentPosition->adjacentVertices.size(); i++)
		{
			if (prAstar::currentPosition->adjacentVertices[i]->previousPoint == nullptr)
			{
				prAstar::currentPosition->adjacentVertices[i]->previousPoint = prAstar::currentPosition;
			}
			if (prAstar::currentPosition->adjacentVertices[i] != prAstar::endPosition)
			{
				setHeuristic(prAstar::currentPosition->adjacentVertices[i], prAstar::currentPosition);
			}
			else
			{
				foundEnd = true;
			}
			//cout << "is this where it fails in loop 1" << endl;
			bool alreadyInList = false;
			for (int j = 0; j < lookedAtVertices.size(); j++)
			{
				if (lookedAtVertices[j] == prAstar::currentPosition->adjacentVertices[i])
				{
					alreadyInList = true;
				}
			}
			if (alreadyInList == false)
			{
				lookedAtVertices.push_back(prAstar::currentPosition->adjacentVertices[i]);
			}
			
		}
		//cout << "is this where it fails in loop 2" << endl;
		prAstar::currentPosition->completed = true;
		Vertex *nextNode = nullptr;

		//cout << "is this where it fails in loop 3" << endl;
		//find the lower heuristic value or checks for the end and sets that as the nextnode
		if (foundEnd != true)
		{
			for (int i = 0; i < lookedAtVertices.size(); i++)
			{
				//cout << "is this where it fails in loop 3.5" << endl;
				if (nextNode == nullptr && lookedAtVertices[i]->completed == false)
				{
					//cout << "is this where it fails in loop 4" << endl;
					nextNode = lookedAtVertices[i];
					//cout << "is this where it fails in loop 4.5" << endl;
				}
				else if (nextNode != nullptr)
				{
					//cout << "is this where it fails in loop 3.75" << endl;
					if (lookedAtVertices[i] == prAstar::endPosition)
					{
						//cout << "is this where it fails in loop 5" << endl;
						nextNode = lookedAtVertices[i];
						//cout << "is this where it fails in loop 5.5" << endl;
					}
					else if (nextNode->heuristic >= lookedAtVertices[i]->heuristic && lookedAtVertices[i]->completed == false && nextNode->distanceToExit > lookedAtVertices[i]->distanceToExit)
					{
						//cout << "is this where it fails in loop 6.5" << endl;
						nextNode = lookedAtVertices[i];
						//cout << "is this where it fails in loop 6" << endl;
					}
					//cout << "is this where it fails in loop 7" << endl;
				}
			}
		}

		else
		{
			for (int i = 0; i < lookedAtVertices.size(); i++)
			{
				if (lookedAtVertices[i] == prAstar::endPosition)
				{
					//cout << "is this where it fails in loop 5" << endl;
					nextNode = lookedAtVertices[i];
					//cout << "is this where it fails in loop 5.5" << endl;
				}
			}
		}
		
		
		
		//cout << "does it get here???" << endl;
		//cout << "x: " << nextNode->x << " y: " << nextNode->y << endl;
		prAstar::currentPosition = nextNode;
		count++;
	}
	//cout << "does loop work" << endl;
	vector<Vertex *> reversePath;
	//gets the path in reverse
	while (prAstar::currentPosition != prAstar::startPosition)
	{
		reversePath.push_back(prAstar::currentPosition);
		prAstar::currentPosition = prAstar::currentPosition->previousPoint;
	}
	reversePath.push_back(prAstar::currentPosition);
	//reverses the reverse path to get a normal path
	for (int reverseCount = reversePath.size() - 1; reverseCount >= 0; reverseCount--)
	{
		prAstar::path.push_back(reversePath[reverseCount]);
		
	}
	/*
	for (int i = 0; i < prAstar::path.size(); i++)
	{
		cout << "path x: " << prAstar::path[i]->x << " y: " << prAstar::path[i]->y << endl;
	}*/
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
							prAstar::graph->vertices.push_back(new Vertex(i,j));
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
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if ( x != 0 || y !=0)
						{
							Vertex *v = new Vertex(x + prAstar::graph->vertices[i]->x, y + prAstar::graph->vertices[i]->y);
							for (int j = 0; j < prAstar::graph->vertices.size(); j++)
							{
								if (v->x == prAstar::graph->vertices[j]->x && v->y == prAstar::graph->vertices[j]->y)
								{
									prAstar::graph->vertices[i]->adjacentVertices.push_back(prAstar::graph->vertices[j]);
								}
								else
								{
									delete v;
								}
							}
						}
						
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
	if (prAstar::pathCalculated == false)
	{
		AstarAlgorithm();
		prAstar::pathCalculated = true;
	}
	if (prAstar::countPath < prAstar::path.size())
	{
		xpos = prAstar::path[prAstar::countPath]->x;
		ypos = prAstar::path[prAstar::countPath]->y;
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
	cout << "start setstart" << endl;
	prAstar::startPosValid = false;

	if ((xpos >= prAstar::xCoords[0]) &&
		(ypos >= prAstar::yCoords[0]))
	{
		prAstar::pXPosStart = xpos;
		prAstar::pYPosStart = ypos;

		prAstar::startPosValid = true;
	}

	cout << "end setstart" << endl;
	return prAstar::startPosValid;
}

// Adam
// Gets the starting location for the player.  Return the saved x and y starting locations.
// If the x and y locations for the start have not been saved yet, then return -1 for both.
__declspec(dllexport) bool GetStart(int& xpos, int& ypos)
{
	cout << "start getstart";
	if (prAstar::startPosValid)
	{
		xpos = prAstar::pXPosStart;
		ypos = prAstar::pYPosStart;
	}
	cout << "end getstart";
	return  prAstar::startPosValid;
}

// Ben
// Sets the ending location for the player.  Save the x and y values for the ending location.
__declspec(dllexport) bool SetEnd(int xpos, int ypos)
{
	cout << "start setend";
	prAstar::endPosValid = false;
	prAstar::pathCalculated = false;

	if ((xpos >= prAstar::xCoords[0]) &&
		(ypos >= prAstar::yCoords[0]) )
	{
		prAstar::pXPosEnd = xpos;
		prAstar::pYPosEnd = ypos;
		prAstar::endPosValid = true;
	}

	//checks to see if conditions for calculating path are met
	
	cout << "end setend";
	return prAstar::endPosValid;
}

// Ben
// Gets the ending location for the player. Return the saved x and y end locations.  If the
// x and y locations for the end have not been saved yet, then return -1 for both.
__declspec(dllexport) bool GetEnd(int& xpos, int& ypos)
{
	cout << "start getend";
	if (prAstar::endPosValid)
	{
		xpos = prAstar::pXPosEnd;
		ypos = prAstar::pYPosEnd;
	}
	cout << "end getend";
	return prAstar::endPosValid;
}

// Move the player back to the staring position
__declspec(dllexport) bool Restart()
{
	cout << "start restart";
	if (prAstar::currentX = -1)
	{
		cout << "end restart";
		return false;
	}

	prAstar::currentX = prAstar::pXPosStart;
	prAstar::currentY = prAstar::pYPosStart;
	cout << "end restart";
	return true;
}