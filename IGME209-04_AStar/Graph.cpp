#include "stdafx.h"
#include "Graph.h"
#include <vector>

using namespace std;

vector<Vertex *> vertices;
Graph::Graph()
{

}


Graph::~Graph()
{
	for (vector<Vertex *>::iterator i = vertices.begin(); i != vertices.end(); i++)
		delete *i;
}

