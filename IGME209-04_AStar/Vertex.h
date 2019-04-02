#pragma once

class Vertex
{
public:
	Vertex();
	Vertex(int xPos, int yPos);
	//Vertex(Vertex &vertex);
	~Vertex();
	bool operator==(const Vertex &v);
	int x;
	int y;
	int distanceToExit;
	int heuristic;
	int pathCost;
	Vertex* previousPoint;
	bool visited;
	bool completed;
	std::vector<Vertex*> adjacentVertices;
};

