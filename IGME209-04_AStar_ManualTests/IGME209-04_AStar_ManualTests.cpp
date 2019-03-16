#include "pch.h"
#include <iostream>
#include <limits>
#include <time.h>

__declspec(dllimport) char* GetTeam();
__declspec(dllimport) bool SetMaze(const int** data, int width, int height);
__declspec(dllimport) int** GetMaze(int& width, int& height);
__declspec(dllimport) bool GetNextPosition(int& xpos, int& ypos);
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
    const int rows = 5;
    const int columns = 10;

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

    testSpace::myMaze = new MazeItem*[testSpace::columns];
    testSpace::returnedMaze = new int*[testSpace::columns];

    for (size_t i = 0; i < testSpace::columns; i++)
    {
        testSpace::myMaze[i] = new MazeItem[testSpace::rows];
        testSpace::returnedMaze[i] = new int[testSpace::rows];
    }

    srand(time(NULL));

    for (size_t i = 0; i < testSpace::columns; i++)
    {
        for (size_t j = 0; j < testSpace::rows; j++)
        {
            testSpace::myMaze[i][j].value = rand() % 2;
        }
    }

    std::cout << "\n\nPrinting maze to set\n" << std::endl;

    for (size_t i = 0; i < testSpace::columns; i++)
    {
        for (size_t j = 0; j < testSpace::rows; j++)
        {
            std::cout << testSpace::myMaze[i][j].value;
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
            std::cout << testSpace::returnedMaze[i][j];
        }

        std::cout << std::endl;
    }

    std::cout << "\n" << std::endl;

    wait();

    int x = 0;
    int y = 0;

    for (int i = 0; i < 10; i++)
    {
        GetNextPosition(x, y);

        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << y << std::endl;
    }
}

void wait()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}