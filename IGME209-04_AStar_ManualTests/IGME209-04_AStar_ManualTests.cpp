#include "pch.h"
#include <iostream>
#include <limits>

__declspec(dllimport) char* GetTeam();
__declspec(dllimport) void SetMaze(const int** data, int width, int height);
__declspec(dllimport) int** GetMaze(int& width, int& height);
__declspec(dllimport) void GetNextPosition(int& xpos, int& ypos);
__declspec(dllimport) void SetStart(int xpos, int ypos);
__declspec(dllimport) void GetStart(int& xpos, int& ypos);
__declspec(dllimport) void SetEnd(int xpos, int ypos);
__declspec(dllimport) void GetEnd(int& xpos, int& ypos);

void wait();

class MazeItem
{
public:
    int value;
};

namespace testSpace
{
    const int rows = 15;
    const int columns = 7;

    MazeItem** myMaze = nullptr;
    int** returnedMaze = nullptr;
}

int main()
{
	std::cout << GetTeam() << "\n" << std::endl;
    
	int setX = 5;
	int setY = 10;
	int getX = 0;
	int getY = 0;

	std::cout << "Setting X-end to 5 and y-end to 10" << std::endl;
	std::cout << "x : " << setX << std::endl;
	std::cout << "y : " << setY << std::endl;
	SetEnd(setX, setY);

	std::cout << "Getting X-end and Y-end" << std::endl;
	GetEnd(getX, getY);

	std::cout << "x : " << getX << std::endl;
	std::cout << "y : " << getY << std::endl;

	setX = 2;
	setY = 20;

	std::cout << "Getting X-end and Y-end" << std::endl;
	std::cout << "x : " << setX << std::endl;
	std::cout << "y : " << setY << std::endl;
	SetEnd(setX, setY);

	std::cout << "Getting X-end and Y-end" << std::endl;
	GetEnd(getX, getY);

	std::cout << "x : " << getX << std::endl;
    std::cout << "y : " << getY << std::endl;

    testSpace::myMaze = new MazeItem*[testSpace::rows];
    testSpace::returnedMaze = new int*[testSpace::rows];

    for (size_t i = 0; i < testSpace::rows; i++)
    {
        testSpace::myMaze[i] = new MazeItem[testSpace::columns];
        testSpace::returnedMaze[i] = new int[testSpace::columns];
    }

    int counter = 1;

    for (size_t i = 0; i < testSpace::rows; i++)
    {
        for (size_t j = 0; j < testSpace::columns; j++)
        {
            testSpace::myMaze[i][j].value = counter;            
            counter++;
        }
    }

    SetMaze((const int**)testSpace::myMaze, testSpace::columns, testSpace::rows);

    int getColumn = 0;
    int getRow = 0;

    testSpace::returnedMaze = GetMaze(getColumn, getRow);

    for (size_t i = 0; i < testSpace::rows; i++)
    {
        for (size_t j = 0; j < testSpace::columns; j++)
        {
            std::cout << testSpace::returnedMaze[i][j];
        }

        std::cout << std::endl;
    }

    wait();
}

void wait()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}