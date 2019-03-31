#pragma once
#include "Vertex.h"

class Graph
{
public:
	Graph();
	~Graph();
	std::vector<Vertex> vertices;
	int** matrix;
};

