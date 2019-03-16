#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

__declspec(dllimport) char* GetTeam();
__declspec(dllimport) bool SetMaze(const int** data, int width, int height);
__declspec(dllimport) int** GetMaze(int& width, int& height);
__declspec(dllimport) bool GetNextPosition(int& xpos, int& ypos);
__declspec(dllimport) void SetStart(int xpos, int ypos);
__declspec(dllimport) void GetStart(int& xpos, int& ypos);
__declspec(dllimport) void SetEnd(int xpos, int ypos);
__declspec(dllimport) void GetEnd(int& xpos, int& ypos);

namespace IGME20904_AStar_UnitTests
{
    int inputX;
    int inputY;

    int outputX;
    int outputY;

    int inputArrayRows;
    int outputArrayRows;
    int inputArrayColumns;
    int outputArrayColumns;

    int** inputMaze = nullptr;
    int** outputMaze = nullptr;

	bool success;

	TEST_CLASS(AStar_Project_Tests)
	{
	public:
		
        TEST_METHOD_INITIALIZE(init)
        {
            std::cout << " Initializing unit tests for project AStar " << std::endl;
        }

        TEST_METHOD_CLEANUP(cleanup)
        {
            std::cout << " Unit tests complete - Performing Cleanup " << std::endl;
        }

        TEST_METHOD(GetTeam_Test)
        {
            Assert::AreEqual("Adam McAree and Benjamin Kleynhans\n", GetTeam());
        }

        // Test SetStart() and GetStart()
		TEST_METHOD(SetStart_GetStart_Test)
		{
            // Set input values
            inputX = 17;
            inputY = 39;
            
            // Set output values to 0
            outputX = 0;
            outputY = 0;

            // Run functions to set and get values
            SetStart(inputX, inputY);
            GetStart(outputX, outputY);

            // Compare values to ensure they are correct
            Assert::AreEqual(inputX, outputX);
            Assert::AreEqual(inputY, outputY);

            // Change the input values
            inputX = inputX * 2;
            inputY = inputY * 3;

            // Reset the output values
            outputX = 0;
            outputY = 0;

            // Run functions to set and get values
            SetStart(inputX, inputY);
            GetStart(outputX, outputY);

            // Compare values to ensure they are correct
            Assert::AreEqual(inputX, outputX);
            Assert::AreEqual(inputY, outputY);
		}

        // Test SetEnd() and GetEnd()
        TEST_METHOD(SetEnd_GetEnd_Test)
        {
            // Set input values
            inputX = 17;
            inputY = 39;

            // Set output values to 0
            outputX = 0;
            outputY = 0;

            // Run functions to set and get values
            SetEnd(inputX, inputY);
            GetEnd(outputX, outputY);

            // Compare values to ensure they are correct
            Assert::AreEqual(inputX, outputX);
            Assert::AreEqual(inputY, outputY);

            // Change the input values
            inputX = inputX * 2;
            inputY = inputY * 3;

            // Reset the output values
            outputX = 0;
            outputY = 0;

            // Run functions to set and get values
            SetEnd(inputX, inputY);
            GetEnd(outputX, outputY);

            // Compare values to ensure they are correct
            Assert::AreEqual(inputX, outputX);
            Assert::AreEqual(inputY, outputY);
        }

        // Test SetMaze() and GetMaze()
        TEST_METHOD(SetMaze_GetMaze_Test)
        {
			// Define a random seed
			srand((unsigned int)time(NULL));

            // Define array size            
            inputArrayColumns = 17;
            inputArrayRows = 15;

            // Create input and output arrays
            inputMaze = new int*[inputArrayColumns];
            outputMaze = new int*[inputArrayColumns];
            
            for (int i = 0; i < inputArrayColumns; i++)
            {
                inputMaze[i] = new int[inputArrayRows];
                outputMaze[i] = new int[inputArrayRows];
            }

			// Fill array with invalid values
			for (int i = 0; i < inputArrayColumns; i++)
			{
				for (int j = 0; j < inputArrayRows; j++)
				{
					inputMaze[i][j] = rand() % 10;
				}
			}

			// Call SetMaze to test invalid values
			success = SetMaze((const int**)inputMaze, inputArrayColumns, inputArrayRows);

			Assert::IsFalse(success);

			// Call GetMaze to ensure return value is nullptr
			outputMaze = GetMaze(outputArrayColumns, outputArrayRows);

			Assert::IsTrue(outputMaze == nullptr);

			// Fill array with valid values
			for (int i = 0; i < inputArrayColumns; i++)
			{
				for (int j = 0; j < inputArrayRows; j++)
				{
					inputMaze[i][j] = rand() % 2;
				}
			}
            
            // Call SetMaze to test valid values
            success = SetMaze((const int**)inputMaze, inputArrayColumns, inputArrayRows);

			Assert::IsTrue(success);

			// Call GetMaze to compare input and output mazes
            outputMaze = GetMaze(outputArrayColumns, outputArrayRows);
            
            // Compare values to ensure they are correct
            for (int i = 0; i < inputArrayColumns; i++)
            {
                for (int j = 0; j < inputArrayRows; j++)
                {
                    Assert::AreEqual(inputMaze[i][j], outputMaze[i][j]);
                }
            }

            Assert::AreEqual(inputArrayColumns, outputArrayColumns);
            Assert::AreEqual(inputArrayRows, outputArrayRows);
            
            // Delete input and output arrays
            for (int i = 0; i < inputArrayColumns; i++)
            {
                delete[] inputMaze[i];
                delete[] outputMaze[i];
            }
            
            delete inputMaze;
            delete outputMaze;
        }

        // Test GetNextPosition with 10 entries
        TEST_METHOD(Get_Next_Position_Test)
        {
            // Define variables
            int x = 0;
            int y = 0;

            // Create input and output arrays
            for (int i = 0; i < 10; i++)
            {
                GetNextPosition(x, y);

                Assert::AreEqual(x, (i + 1));
                Assert::AreEqual(y, (i + 1));
            }
        }
	};
}