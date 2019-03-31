#pragma once
class Vertex
{
public:
	Vertex(int x, int y);
	~Vertex();
	int xPos;
	int yPos;
	int heuristic;
	int lowestCost;
	bool Visited;
};

