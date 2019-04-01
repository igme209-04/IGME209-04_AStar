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

class Graph
{
public:
	Graph(const int**, int&, int&);

	static std::list<Vertex*> VertexList;

	//void InstantiateVertices();
	void InstantiateVertex(int*);
	void ResetSearchTree();
	void ResetVisited();
	void ShortestPath(int*, int*);	
	void FindPath(int*, int*);

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
	const int** adjMatrix;
	static int* origin;
	static int* destination;

	void UpdateFinals(std::list<Vertex*>);
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
	std::cout << "\nCreating Graph\n" << std::endl;
	VertexList.clear();
	VisitedList.clear();
	this->adjMatrix = maze;
	this->SetRows(rows);
	this->SetColumns(columns);	

	//this->InstantiateVertices();

	std::cout << "\nGraph created" << std::endl;
}

void Graph::InstantiateVertex(int*)
{

}

//void Graph::InstantiateVertices()
//{
//	for (int row = 0; row < this->GetRows(); row++)
//	{
//		for (int column = 0; column < this->GetColumns(); column++)
//		{
//			if (this->adjMatrix[row][column] == 0)
//			{
//				VertexList.push_back(new Vertex(row, column));
//			}
//		}
//	}
//}

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
void Graph::ShortestPath(int* origin, int* destination)
{
	this->SetOrigin(origin);
	this->SetDestination(destination);

	PriorityQueue* pPriorityQueue = new PriorityQueue();
	Vertex* pNextVertex = nullptr;
	int* address = nullptr;

	// Add the origin vertex to the priority queue
	pPriorityQueue->Enqueue(new Vertex(origin[0], origin[1]));
	pPriorityQueue->Peek()->SetHMetric(0);
	pPriorityQueue->Peek()->SetGMetric(0);
	pPriorityQueue->Peek()->Setfinal(true);
	pPriorityQueue->Peek()->SetVisited(true);

	// A* loop
	do
	{
		// Get adjacent unvisited
		this->GetAdjacentUnvisited(pPriorityQueue->Peek());

		pPriorityQueue->Peek()->SetVisited(true);
		this->VisitedList.push_back(pPriorityQueue->Dequeue());

	} while (0 != 0);// ((pPriorityQueue->Peek()->GetAddress[0] != destination[0]) && (pPriorityQueue->Peek()->GetAddress[1] != destination[1]));

	std::cout << std::endl;
}

void Graph::GetAdjacentUnvisited(Vertex* currentVertex)
{
	int addressModifiers[3] = { -1, 0, 1 };
	int* pCurrentAddress = currentVertex->GetAddress();

	int tmpColumns = 0;
	int tmpRows = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			 tmpRows = pCurrentAddress[0] + addressModifiers[i];
			 tmpColumns = pCurrentAddress[1] + addressModifiers[j];

			if (!(tmpRows < 0) && !(tmpColumns < 0) &&
				!(tmpRows > this->GetRows()) && !(tmpColumns > this->GetColumns()) &&
				!((tmpRows == pCurrentAddress[0]) && (tmpColumns == pCurrentAddress[1])))
			{
				if (this->adjMatrix[tmpRows][tmpColumns] != 1)
				{
					this->VertexList.push_back(new Vertex(tmpRows, tmpColumns));

					// Set G Metric using both straight and diagonal movement
					if ((i == 0) || (j == 0))
					{
						this->VertexList.back()->SetGMetric(currentVertex->GetGMetric() + 10);
					}
					else
					{
						this->VertexList.back()->SetGMetric(currentVertex->GetGMetric() + 14);
					}

					// Set H Metric using Pythagorean theorum squared (no sqrt)
					this->VertexList.back()->SetHMetric((float)(pow(this->GetDestination()[1] - tmpRows, 2) + pow(this->GetDestination()[0] - tmpColumns, 2)));
					this->VertexList.back()->SetNeighbor(currentVertex);
				}
			}
		}
	}
}

void Graph::UpdateFinals(std::list<Vertex*> vertex)
{

}

void Graph::FindPath(int* origin, int* destination)
{

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
	std::cout << "\nDeleting Vertices\n" << std::endl;

	for (Vertex* vertex : VertexList)
	{
		delete(vertex);
	}

	VertexList.clear();

	std::cout << "\nVertices Deleted\n" << std::endl;
}

Graph::~Graph()
{
	DeleteVertices();

	std::cout << "\nGraph destroyed\n" << std::endl;
}