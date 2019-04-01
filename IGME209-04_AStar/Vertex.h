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
/// Filename            : Vertex.h
///

#include "stdafx.h"
#pragma once
#include <string>
#include <iostream>

class Vertex
{
public:
	Vertex(int&, int&);
	
	int IncreaseCount();
	int DecreaseCount();
	void SetAddress(int, int);
	int* GetAddress();
	void SetFMetric(float);
	float GetFMetric();
	void SetGMetric(float);
	float GetGMetric();
	void SetHMetric(float);
	float GetHMetric();	
	void SetVisited(bool);
	bool GetVisited();
	void Setfinal(bool);
	bool GetFinal();
	void ResetVertex();
	void ResetVisited();

	void SetNeighbor(Vertex*);
	Vertex* GetNeighbor();
	std::string ToString();

	~Vertex();

private:
	Vertex* closestNeighbor;

	int address[2];	
	static int count;
	
	float fMetric;				// Total distance including heuristic
	float gMetric;				// Metric to origin
	float hMetric;				// Metric to destination	

	bool visited;
	bool final;
};

int Vertex::count = 0;

// Paramaterized constructor
Vertex::Vertex(int& row, int& column)
{
	this->SetAddress(row, column);

	std::cout << "Vertex " << this->IncreaseCount() << " created with coordinates " << row << "," << column << " created" << std::endl;
}

// Reset all properties of the vertex
void Vertex::Vertex::ResetVertex()
{
	this->Setfinal(false);
	this->SetFMetric((float)INT_MAX);
	this->SetGMetric((float)INT_MAX);
	this->SetHMetric((float)INT_MAX);
	this->SetNeighbor(nullptr);
}

int Vertex::IncreaseCount()
{
	count++;

	return (count - 1);
}

int Vertex::DecreaseCount()
{
	count--;

	return count;
}

// Reset the visited property of the vertex
void Vertex::Vertex::ResetVisited()
{
	this->SetVisited(false);
}

// All the getters and setters
void Vertex::SetAddress(int row, int column)
{
	this->address[0] = row;
	this->address[1] = column;	
}

int* Vertex::GetAddress()
{
	return this->address;
}

void Vertex::SetFMetric(float totalMetric)
{
	this->fMetric = totalMetric;
}

float Vertex::GetFMetric()
{
	return this->fMetric;
}

void Vertex::SetGMetric(float distanceToOrigin)
{
	this->gMetric = distanceToOrigin;
	
	this->SetFMetric(this->GetGMetric() + this->GetHMetric());
}

float Vertex::GetGMetric()
{
	return this->gMetric;
}

void Vertex::SetHMetric(float distanceToDestination)
{
	this->hMetric = distanceToDestination;

	this->SetFMetric(this->GetGMetric() + this->GetHMetric());
}

float Vertex::GetHMetric()
{
	return this->hMetric;
}

void Vertex::SetVisited(bool)
{
	this->visited = true;
}

bool Vertex::GetVisited()
{
	return this->visited;
}

void Vertex::Setfinal(bool)
{
	this->final = true;
}

bool Vertex::GetFinal()
{
	return this->final;
}

void Vertex::SetNeighbor(Vertex* pVertex)
{
	this->closestNeighbor = pVertex;
}

Vertex* Vertex::GetNeighbor()
{
	return this->closestNeighbor;
}

Vertex::~Vertex()
{
	std::cout << "Vertex " << this->DecreaseCount() << " destroyed" << std::endl;
}