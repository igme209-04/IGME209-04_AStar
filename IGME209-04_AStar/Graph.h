/// 
/// IGME-209.04 - Data Structures and Algorithms
/// 
/// Project 1           :  A* algorithm DLL for use in other programs
/// 
/// Class Description   : Some debugging exercises.
/// Created By          : Benjamin Kleynhans - bxk8027@rit.edu
///                       Adam McAree - arm1686@g.rit.edu
/// Date Created        : March 30, 2019
/// Last Modified By    : Benjamin Kleynhans
/// Date Modified       : March 30, 2019
/// Filename            : Graph.h
///

#pragma once
#include <iostream>
#include "PriorityQueue.h"

struct MazeItem
{
public:
	int value;
};

class Graph
{
public:
	Graph(const int**, int&, int&);

	static std::list<Vertex*> VertexList;

	void InstantiateVertex(int*);
	void ResetSearchTree();
	void ResetVisited();
	MazeItem** CalculateShortestPath(int*, int*);
	int Combine(int, int);
	MazeItem** shortestPath = nullptr;
	int CalculateGMetric(int, int);

	void SetColumns(const int);
	int& GetColumns();
	void SetRows(const int);
	int& GetRows();
	void SetOrigin(int*);
	int* GetOrigin();
	void SetDestination(int*);
	int* GetDestination();
	
	std::string ToString();
	void DeleteVertices();
	
	~Graph();
	
private:
	static int rows;
	static int columns;
	static std::list<Vertex*> VisitedList;
	std::list<Vertex*> VisitedVertices;
	const int** adjMatrix;
	static int* origin;
	static int* destination;
	
	void UpdateFinals();
	void GetAdjacentUnvisited(Vertex*);
};

std::list<Vertex*> Graph::VertexList;
std::list<Vertex*> Graph::VisitedList;
int Graph::rows;
int Graph::columns;
int* Graph::origin;
int* Graph::destination;

// Parameterized constructor
Graph::Graph(const int** maze, int& rows, int& columns)
{
	//std::cout << "\nCreating Graph" << std::endl;
	
	VertexList.clear();
	VisitedList.clear();
	this->adjMatrix = maze;
	this->SetRows(rows);
	this->SetColumns(columns);
	this->shortestPath = shortestPath;

	std::cout << "\nGraph created" << std::endl;
}

void Graph::InstantiateVertex(int*)
{

}

// Reset the search tree
void Graph::ResetSearchTree()
{
	for (Vertex* vertex : VertexList)
	{
		vertex->ResetVertex();
	}
}

// Set visited properties to false
void Graph::ResetVisited()
{
	for (Vertex* vertex : VertexList)
	{
		vertex->ResetVisited();
	}
}

// A* - Calculate the shortest path
MazeItem** Graph::CalculateShortestPath(int* origin, int* destination)
{
	this->SetOrigin(origin);
	this->SetDestination(destination);

	PriorityQueue* pPriorityQueue = new PriorityQueue();
	Vertex* pNextVertex = nullptr;
	int* address = nullptr;

	// Add the origin vertex to the priority queue
	pPriorityQueue->Enqueue(new Vertex(origin[0], origin[1]));
	this->VisitedVertices.push_back(pPriorityQueue->Peek());	
	pPriorityQueue->Peek()->SetHMetric(0);
	pPriorityQueue->Peek()->SetGMetric(0);
	pPriorityQueue->Peek()->SetVisited(true);

	bool breakLoop = false;

	// A* loop
	do
	{
		// Get adjacent unvisited
		this->GetAdjacentUnvisited(pPriorityQueue->Peek());

		for (Vertex* vertex : this->VertexList)
		{
			if (!(pPriorityQueue->Contains(vertex)) && !(vertex->GetFinal()))
			{	
				vertex->SetVisited(true);
				pPriorityQueue->Enqueue(vertex);
			}
		}

		pPriorityQueue->Peek()->SetFinal(true);
		VisitedList.push_back(pPriorityQueue->Dequeue());

		//std::cout << VisitedList.back()->GetAddress()[0] <<  "," << VisitedList.back()->GetAddress()[1] << std::endl;

		if (pPriorityQueue->Peek() != nullptr)
		{
			if (((pPriorityQueue->Peek()->GetAddress()[0] == destination[0]) && (pPriorityQueue->Peek()->GetAddress()[1] == destination[1])) ||
				(pPriorityQueue->Peek() == nullptr))
			{
				breakLoop = true;
			}
		}
		else
		{
			breakLoop = true;
		}
		
	} while (!breakLoop);

	if (pPriorityQueue->Peek() != nullptr)
	{
		VisitedList.push_back(pPriorityQueue->Dequeue());

		//std::cout << "\n !!! Goal Reached !!! \n" << std::endl;

		this->UpdateFinals();
	}
	else
	{
		this->shortestPath = nullptr;
	}

	return this->shortestPath;
}

void Graph::GetAdjacentUnvisited(Vertex* currentVertex)
{
	Vertex* tempVertex = nullptr;
	int addressModifiers[3] = { -1, 0, 1 };
	int* pCurrentAddress = currentVertex->GetAddress();

	int tmpColumns = 0;
	int tmpRows = 0;

	bool alreadyAdded = false;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			alreadyAdded = false;

			 tmpRows = pCurrentAddress[0] + addressModifiers[i];
			 tmpColumns = pCurrentAddress[1] + addressModifiers[j];

			 for (Vertex* vertex : this->VisitedVertices)
			 {
				 if ((vertex->GetAddress()[0] == tmpRows) && (vertex->GetAddress()[1] == tmpColumns))
				 {
					 alreadyAdded = true;
					 tempVertex = vertex;
					 break;
				 }
			 }

			if (!(tmpRows < 0) && !(tmpColumns < 0) &&
				!(tmpRows > (this->GetRows() - 1)) && !(tmpColumns > (this->GetColumns() - 1)) &&
				!((tmpRows == pCurrentAddress[0]) && (tmpColumns == pCurrentAddress[1])))
			{
				if (alreadyAdded)
				{
					if (currentVertex->GetGMetric() > (tempVertex->GetGMetric() + CalculateGMetric(addressModifiers[i], addressModifiers[j])))
					{
						currentVertex->SetClosestNeighbor(tempVertex);
						currentVertex->SetGMetric(tempVertex->GetGMetric() + CalculateGMetric(addressModifiers[i], addressModifiers[j]));
					}
					else if ((currentVertex->GetGMetric() + CalculateGMetric(addressModifiers[i], addressModifiers[j])) < (tempVertex->GetGMetric()))
					{
						tempVertex->SetClosestNeighbor(currentVertex);
						tempVertex->SetGMetric(currentVertex->GetGMetric() + CalculateGMetric(addressModifiers[i], addressModifiers[j]));
					}

					tempVertex = nullptr;
				}
				else
				{
					if (this->adjMatrix[tmpRows][tmpColumns] != 1)
					{
						this->VertexList.push_back(new Vertex(tmpRows, tmpColumns));
						this->VisitedVertices.push_back(this->VertexList.back());

						// Set G Metric using both straight and diagonal movement

						this->VertexList.back()->SetGMetric(currentVertex->GetGMetric() + CalculateGMetric(addressModifiers[i], addressModifiers[j]));

						// Set H Metric using Pythagorean theorum squared (no sqrt)
						this->VertexList.back()->SetHMetric((float)(pow((this->GetDestination()[0] - tmpRows) * 10, 2) + pow((this->GetDestination()[1] - tmpColumns) * 10, 2)));
						this->VertexList.back()->SetClosestNeighbor(currentVertex);
					}
				}
			}
		}
	}
}

void Graph::UpdateFinals()
{	
	std::list<Vertex*> closestVertices;
	Vertex* currentVertex = nullptr;
	int* neighbor = nullptr;

	currentVertex = VisitedList.back();
	closestVertices.push_front(currentVertex);

	while (currentVertex->GetClosestNeighbor() != nullptr)
	{
		currentVertex = currentVertex->GetClosestNeighbor();
		closestVertices.push_front(currentVertex);
	}

	// Create, set and get auto maze
	this->shortestPath = new MazeItem*[closestVertices.size()];

	for (size_t i = 0; i < closestVertices.size(); i++)
	{
		this->shortestPath[i] = new MazeItem[2];
	}

	const int listSize = closestVertices.size();
	
	int counter = 0;

	for (Vertex* vertex : closestVertices)
	{
		this->shortestPath[counter][0].value = vertex->GetAddress()[0];
		this->shortestPath[counter][1].value = vertex->GetAddress()[1];

		counter++;
	}
}

int Graph::CalculateGMetric(int i, int j)
{
	int gMetric = 0;

	// Set G Metric using both straight and diagonal movement
	if ((i == 0) || (j == 0))
	{
		gMetric = 10;
	}
	else
	{
		gMetric = 14;
	}

	return gMetric;
}

int Graph::Combine(int a, int b)
{
	int times = 1;

	do
	{
		times *= 10;
	} while (times <= b);

	return (a * times + b);
}

void Graph::SetColumns(const int columns)
{
	this->columns = columns;
}

int& Graph::GetColumns()
{
	return this->columns;
}

void Graph::SetRows(const int rows)
{
	this->rows = rows;
}

int& Graph::GetRows()
{
	return this->rows;
}

void Graph::SetOrigin(int* origin)
{
	this->origin = origin;
}

int* Graph::GetOrigin()
{
	return this->origin;
}

void Graph::SetDestination(int* destination)
{
	this->destination = destination;
}

int* Graph::GetDestination()
{
	return this->destination;
}

std::string Graph::ToString()
{
	std::string returnValue = "";

	for (int i = 0; i < this->columns; i++)
	{
		for (int j = 0; j < this->rows; j++)
		{
			returnValue += std::to_string(this->adjMatrix[i][j]) + " ";			
		}

		returnValue += '\n';
	}

	std::cout << "\nToString output of Graph\n\n" << returnValue << std::endl;

	return returnValue;
}

void Graph::DeleteVertices()
{
	//std::cout << "\nDeleting Vertices\n" << std::endl;

	for (Vertex* vertex : VertexList)
	{
		delete(vertex);
	}

	VertexList.clear();

	//std::cout << "\nVertices Deleted\n" << std::endl;
}

Graph::~Graph()
{
	DeleteVertices();

	std::cout << "\nGraph destroyed\n" << std::endl;
}