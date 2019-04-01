#pragma once
#include "Vertex.h"

class Graph
{
public:
	Graph(int xMaxpar, int yMaxpar);
	~Graph();
	std::vector<Vertex> vertices;
	int xMax;
	int yMax;
	Vertex** matrix;
	bool IsValid(int x, int y);
	std::vector<Vertex> aStar(Vertex start, Vertex dest);

	
	double calculateH(int x, int y)

};

