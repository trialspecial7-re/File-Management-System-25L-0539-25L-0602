#pragma once

#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

class Folder : public Node {
	Node** children;
	int capacity;
	int count;
public:
	Folder(string n, Node* p = nullptr) : Node(n, p)//  Constructor
	{
		capacity = 5;
		count = 0;
		children = new Node * [capacity];
	}

	~Folder()//Destructor
	{
		for (int i = 0; i < count; i++)
		{
			delete children[i];
		}
		delete[] children;
	}

	string getType() override
	{
		return "Folder";
	}

	void grow()//Increases the capacity if the capacity is utilised
	{
		capacity = capacity * 2;
		Node** newArray = new Node * [capacity];
		for (int i = 0; i < count; i++)
		{
			newArray[i] = children[i];
		}
		delete[] children;
		children = newArray;
	}

	void open() override //open() function 
	{
		cout << "Folder opened: " << getFullPath() << endl;
	}

	bool doesNameExist(string n) const
	{
		for (int i = 0; i < count; i++)
		{
			if (children[i]->getName() == n)
			{
				return true;
			}
		}
		return false;
	}

	void addNode(Node* newNode)
	{
		if (newNode == nullptr)//To ensure we are working with data that exists
		{
			return;
		}
		if (doesNameExist(newNode->getName()))
		{
			cout << "Error: A node with name \"" << newNode->getName() << "\" already exists in this folder!" << endl;
			delete newNode; //cleans up memory to avoid leaks
			return;
		}
		if (count == capacity)
		{
			grow();
		}
		children[count++] = newNode;
	}

	void listNodes() const//Lists all nodes (ls command logic)
	{
		if (count == 0)
		{
			cout << "Empty folder!" << endl;
			return;
		}
		for (int i = 0; i < count; i++)
		{
			cout << "[" << children[i]->getType() << "] " << children[i]->getName() << endl;
		}
	}

	Node* getChild(string n) const//Finds node by name
	{
		for (int i = 0; i < count; i++)
		{
			if (children[i]->getName() == n)
			{
				return children[i]; //returns the address of that node in memory
			}
		}
		return nullptr;
	}

	bool removeNode(string n) //Removes a node by name
	{
		for (int i = 0; i < count; i++)
		{
			if (children[i]->getName() == n)
			{
				delete children[i];

				//Shifting remaining elements to the left
				for (int j = i; j < count - 1; j++)
				{
					children[j] = children[j + 1];
				}
				count--;
				return true;
			}
		}
		return false;
	}

	int getCount() const
	{
		return count;
	}

	Node* getChildAt(int index) const
	{
		if (index >= 0 && index < count)
			return children[index];
		return nullptr;
	}
};

