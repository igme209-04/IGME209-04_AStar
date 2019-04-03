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
/// Filename            : PriorityQueue.h
///

#include "stdafx.h"
#pragma once
#include "Vertex.h"
#include <list>
#include <string>

class PriorityQueue
{
public:
	PriorityQueue();

	void Enqueue(Vertex*);
	Vertex* Dequeue();
	Vertex* Peek();
	bool Contains(Vertex*);
	int GetCount();
	std::string ToString();
	void Debug();
	
	~PriorityQueue();

private:
	int count;
	std::list<Vertex*> ObjectList;
	bool debug = false;

	void UpdatePriority();
};

// Default constructor
PriorityQueue::PriorityQueue()
{
	this->ObjectList.clear();

	if (debug)
	{
		std::cout << "Vertex created" << std::endl;
	}
}

void PriorityQueue::Enqueue(Vertex* pObject)
{
	this->ObjectList.push_back(pObject);
}

Vertex* PriorityQueue::Dequeue()
{
	Vertex* returnValue = nullptr;

	if (this->ObjectList.size() > 0)
	{
		returnValue = this->ObjectList.front();
		this->ObjectList.pop_front();

		this->UpdatePriority();
	}

	return returnValue;
}

Vertex* PriorityQueue::Peek()
{
	if (this->ObjectList.size() > 0)
	{
		return this->ObjectList.front();
	}
	else
	{
		return nullptr;
	}
}

bool PriorityQueue::Contains(Vertex* object)
{
	return (std::find(this->ObjectList.begin(), this->ObjectList.end(), object) != ObjectList.end());
}

void PriorityQueue::UpdatePriority()
{
	if (this->ObjectList.size() > 0)
	{
		Vertex* smallestVertex = this->ObjectList.front();

		for (Vertex* listObject : ObjectList)
		{
			if (listObject->GetFMetric() < smallestVertex->GetFMetric())
			{
				smallestVertex = listObject;
			}
		}

		this->ObjectList.remove(smallestVertex);
		this->ObjectList.push_front(smallestVertex);
	}
}

int PriorityQueue::GetCount()
{
	return this->count;
}

void PriorityQueue::Debug()
{
	this->debug = !this->debug;
}

PriorityQueue::~PriorityQueue()
{
	if (debug)
	{
		std::cout << "Queue destroyed" << std::endl;
	}
}