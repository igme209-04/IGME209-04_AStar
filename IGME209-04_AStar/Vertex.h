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
	Vertex();
	Vertex(int&, int&);
	Vertex(const Vertex&);
	
	int IncreaseCount();
	int DecreaseCount();
	void SetAddress(int, int);
	void SetAddress(int*);
	int* GetAddress();
	void SetFMetric(float);
	float GetFMetric();
	void SetGMetric(float);
	float GetGMetric();
	void SetHMetric(float);
	float GetHMetric();	
	void SetVisited(bool);
	bool GetVisited();
	void SetFinal(bool);
	bool GetFinal();
	void ResetVertex();
	void ResetVisited();

	void Debug();

	void SetClosestNeighbor(Vertex*);
	Vertex* GetClosestNeighbor();
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
	bool debug = false;
};

int Vertex::count = 0;

// Default constructor
Vertex::Vertex()
{
	if (debug)
	{
		std::cout << "Vertex default constructor called" << std::endl;
	}
	

	this->SetAddress(0, 0);
	this->SetClosestNeighbor(nullptr);

	if (debug)
	{
		std::cout << "Vertex " << this->IncreaseCount() << " created with default constructor with row/column 0,0" << std::endl;
	}
}

// Paramaterized constructor
Vertex::Vertex(int& row, int& column)
{
	if (debug)
	{
		//std::cout << "Vertex parameterized constructor called" << std::endl;
	}	

	this->SetAddress(row, column);

	if (debug)
	{
		std::cout << "\nVertex " << this->IncreaseCount() << " created at : " << row << "," << column << std::endl;
	}
}

// Copy constructor
Vertex::Vertex(const Vertex& other)
{
	if (debug)
	{
		std::cout << "Vertex copy constructor called" << std::endl;
	}
	
		
	/*this->SetAddress(other.GetAddress());
	this->SetGMetric(other.GetGMetric);
	this->SetHMetric(other.GetHMetric);
	this->SetVisited(other.GetVisited);
	this->SetFinal(other.GetFinal);
	this->SetClosestNeighbor(other.GetClosestNeighbor);*/
	
	if (debug)
	{
		std::cout << "Vertex  created as copy of " << this->GetAddress() << std::endl;
	}
}

// Reset all properties of the vertex
void Vertex::Vertex::ResetVertex()
{
	this->SetFinal(false);
	this->SetFMetric((float)INT_MAX);
	this->SetGMetric((float)INT_MAX);
	this->SetHMetric((float)INT_MAX);
	this->SetClosestNeighbor(nullptr);
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

void Vertex::SetAddress(int* address)
{
	this->address[0] = address[0];
	this->address[1] = address[1];
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

	if (debug)
	{
		std::cout << "Vertex " << this->count << " row: " << this->address[0] << " column: " << this->address[1];
		std::cout << " G: " << this->GetGMetric() << " H: " << this->GetHMetric() << " F: " << this->GetFMetric() << std::endl;
	}
}

float Vertex::GetGMetric()
{
	return this->gMetric;
}

void Vertex::SetHMetric(float distanceToDestination)
{
	this->hMetric = distanceToDestination;

	this->SetFMetric(this->GetGMetric() + this->GetHMetric());

	if (debug)
	{
		std::cout << "Vertex " << this->count << " row: " << this->address[0] << " column: " << this->address[1];
		std::cout << " G: " << this->GetGMetric() << " H: " << this->GetHMetric() << " F: " << this->GetFMetric() << std::endl;
	}
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

void Vertex::SetFinal(bool)
{
	this->final = true;
}

bool Vertex::GetFinal()
{
	return this->final;
}

void Vertex::SetClosestNeighbor(Vertex* pVertex)
{
	this->closestNeighbor = pVertex;
}

Vertex* Vertex::GetClosestNeighbor()
{
	return this->closestNeighbor;
}

void Vertex::Debug()
{
	this->debug = !this->debug;
}

Vertex::~Vertex()
{
	if (debug)
	{
		std::cout << "Vertex " << this->DecreaseCount() << " destroyed" << std::endl;
	}
}