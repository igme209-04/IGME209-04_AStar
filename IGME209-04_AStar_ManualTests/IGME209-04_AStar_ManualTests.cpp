#include "pch.h"
#include <iostream>
#include <limits>
#include <time.h>
#include "../IGME209-04_AStar/Graph.h"

struct MazeItem
{
public:
    int value;
};

namespace testSpace
{
    const int rows = 10;
    const int columns = 10;

	MazeItem** autoMaze = nullptr;
	MazeItem** myMaze = nullptr;

	int mazeTemplate[100] = {
	//	    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	/*0*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*1*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*2*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/*3*/	0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	/*4*/	0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
	/*5*/	0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
	/*6*/	0, 0, 0, 1, 0, 1, 0, 1, 0, 0,
	/*7*/	0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
	/*8*/	0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
	/*9*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	
	
    int** returnedMaze = nullptr;
}

int main()
{
	// Test name function
	std::cout << GetTeam() << "\n" << std::endl;
    
	//// Create, set and get auto maze
	//testSpace::autoMaze = new MazeItem*[testSpace::columns];
	//testSpace::returnedMaze = new int*[testSpace::columns];

	//for (size_t i = 0; i < testSpace::columns; i++)
	//{
	//	testSpace::autoMaze[i] = new MazeItem[testSpace::rows];
	//	testSpace::returnedMaze[i] = new int[testSpace::rows];
	//}

	//srand((int)time(NULL));

	//for (size_t i = 0; i < testSpace::columns; i++)
	//{
	//	for (size_t j = 0; j < testSpace::rows; j++)
	//	{
	//		testSpace::autoMaze[i][j].value = rand() % 2;
	//	}
	//}

	//std::cout << "Printing maze to set\n" << std::endl;

	//for (size_t i = 0; i < testSpace::columns; i++)
	//{
	//	for (size_t j = 0; j < testSpace::rows; j++)
	//	{
	//		std::cout << testSpace::autoMaze[i][j].value << " ";
	//	}

	//	std::cout << std::endl;
	//}

	//std::cout << "Maze was set : " << (SetMaze((const int**)testSpace::autoMaze, testSpace::columns, testSpace::rows)) << std::endl;

	//int getColumn = 0;
	//int getRow = 0;

	//testSpace::returnedMaze = GetMaze(getColumn, getRow);

	//std::cout << "\nPrinting returned maze\n" << std::endl;

	//for (size_t i = 0; i < testSpace::columns; i++)
	//{
	//	for (size_t j = 0; j < testSpace::rows; j++)
	//	{
	//		std::cout << testSpace::returnedMaze[i][j] << " ";
	//	}

	//	std::cout << std::endl;
	//}

	//std::cout << "\n" << std::endl;

	// Set and get myMaze
	testSpace::myMaze = new MazeItem*[testSpace::columns];
	testSpace::returnedMaze = new int*[testSpace::columns];

	for (size_t i = 0; i < testSpace::columns; i++)
	{
		testSpace::myMaze[i] = new MazeItem[testSpace::rows];
		testSpace::returnedMaze[i] = new int[testSpace::rows];
	}
	
	int item = 0;

	for (size_t i = 0; i < testSpace::columns; i++)
	{		
		for (size_t j = 0; j < testSpace::rows; j++)
		{
			testSpace::myMaze[i][j].value = testSpace::mazeTemplate[item];
			item++;
		}
	}

	std::cout << "Printing maze to set\n" << std::endl;

	for (size_t i = 0; i < testSpace::columns; i++)
	{
		for (size_t j = 0; j < testSpace::rows; j++)
		{
			std::cout << testSpace::myMaze[i][j].value << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "Maze was set : " << (SetMaze((const int**)testSpace::myMaze, testSpace::columns, testSpace::rows)) << std::endl;

	int getColumn = 0;
	int getRow = 0;

	testSpace::returnedMaze = GetMaze(getColumn, getRow);

	std::cout << "\nPrinting returned maze\n" << std::endl;

	for (size_t i = 0; i < testSpace::columns; i++)
	{
		for (size_t j = 0; j < testSpace::rows; j++)
		{
			std::cout << testSpace::returnedMaze[i][j] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << "\n" << std::endl;

	// Test set and get of start and end points
	int localStart[2] = { 8, 7 };	// (row/column NOT x/y)
	int localEnd[2] = { 1, 1 };		// (row/column NOT x/y)
	int remoteStart[2] = { 0, 0 };
	int remoteEnd[2] = { 0, 0 };

	std::cout << "Setting Remote Start to (8,7)" << std::endl;
	SetRemoteStart(localStart);

	std::cout << "Setting Remote End to (1,1)" << std::endl;
	SetRemoteEnd(localEnd);

	std::cout << "Getting Remote Start" << std::endl;
	GetRemoteStart(remoteStart);

	std::cout << "Getting Remote End" << std::endl;
	GetRemoteEnd(remoteEnd);

	localStart[0] = 9;		localStart[1] = 14;
	localEnd[0]	= 17;		localEnd[1] = 1;
	remoteStart[0] = 0;		remoteStart[1] = 0;
	remoteEnd[0] = 0;		remoteEnd[1] = 0;

	std::cout << "Setting Remote Start to (9,14)" << std::endl;
	SetRemoteStart(localStart);

	std::cout << "Setting Remote End to (17,1)" << std::endl;
	SetRemoteEnd(localEnd);

	std::cout << "Getting Remote Start" << std::endl;
	GetRemoteStart(remoteStart);

	std::cout << "Getting Remote End" << std::endl;
	GetRemoteEnd(remoteEnd);

	std::cout << std::endl;

    int x = 0;
    int y = 0;

    for (int i = 0; i < 10; i++)
    {
        GetNextPosition(x, y);

        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << y << std::endl;
    }
}

void SetRemoteStart(int* start)
{
	std::cout << "x : " << start[0] << std::endl;
	std::cout << "y : " << start[1] << std::endl;

	SetStart(start[0], start[1]);
}

void SetRemoteEnd(int* end)
{	
	std::cout << "x : " << end[0] << std::endl;
	std::cout << "y : " << end[1] << std::endl;

	SetEnd(end[0], end[1]);
}

void GetRemoteStart(int* start)
{
	GetStart(start[0], start[1]);

	std::cout << "x : " << start[0] << std::endl;
	std::cout << "y : " << start[1] << std::endl;
}

void GetRemoteEnd(int* end)
{
	GetEnd(end[0], end[1]);

	std::cout << "x : " << end[0] << std::endl;
	std::cout << "y : " << end[1] << std::endl;
}