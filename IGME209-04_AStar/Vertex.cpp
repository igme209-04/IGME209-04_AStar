#include "stdafx.h"
#include "Vertex.h"
#include <vector>
int x;
int y;
int distanceToExit;
int heuristic;
int pathCost;
Vertex* previousPoint;
bool completed;
bool visited;
std::vector<Vertex*> adjacentVertices;
Vertex::Vertex()
{
}

Vertex::Vertex(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	completed = false;
	visited = false;
	previousPoint = nullptr;
	distanceToExit = -1;
	heuristic = -1;
	pathCost = -1;
}

/*Vertex::Vertex(Vertex & vertex)
{
	
}*/


Vertex::~Vertex()
{

}

bool Vertex::operator==(const Vertex & v)
{
	return (this->y == v.y && this->x == v.x);
}
