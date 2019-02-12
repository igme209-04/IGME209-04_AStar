#include "pch.h"
#include <iostream>

__declspec(dllimport) char* GetTeam();
__declspec(dllimport) void SetMaze(const int** data, int width, int height);
__declspec(dllimport) int** GetMaze(int& width, int& height);
__declspec(dllimport) void GetNextPosition(int& xpos, int& ypos);
__declspec(dllimport) void SetStart(int xpos, int ypos);
__declspec(dllimport) void GetStart(int& xpos, int& ypos);
__declspec(dllimport) void SetEnd(int xpos, int ypos);
__declspec(dllimport) void GetEnd(int& xpos, int& ypos);

class MazeItem
{
public:
    int value;
};

namespace testSpace
{
    const int rows = 5;
    const int columns = 5;

    MazeItem** myMaze = nullptr;
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

    for (size_t i = 0; i < testSpace::rows; i++)
    {
        testSpace::myMaze[i] = new MazeItem[testSpace::columns];
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

    SetMaze((const int**)testSpace::myMaze, testSpace::rows, testSpace::columns);

    std::cout << std::endl;
}
