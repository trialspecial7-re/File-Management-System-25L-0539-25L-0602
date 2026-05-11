#pragma once
#include <iostream>
#include <string>

using namespace std;

class Node {
protected:
	string name;
	Node* parent;
public:
	Node(string n, Node* p = nullptr) : parent(p)//Constructor
	{
		this->name = n;
	}

	virtual ~Node() {}
	virtual void open() = 0;
	virtual string getType() = 0;

	string getName() const
	{
		return name;
	}
	Node* getParent() const
	{
		return parent;
	}
	void setName(string n)
	{
		name = n;
	}
	void setParent(Node* p)
	{
		parent = p;
	}

	string getFullPath() const //Path generation on virtual system
	{
		string path = name;
		Node* current = parent;
		while (current != nullptr)
		{
			path = current->getName() + "/" + path;
			current = current->getParent();
		}
		return path;
	}

	string getDiskPath() const  //Here we get path for the actual physical storage on disk
	{
		string path = name;
		Node* current = parent;

		while (current != nullptr)
		{
			if (current->getParent() == nullptr)
				break;

			path = current->getName() + "\\" + path;
			current = current->getParent();
		}

		return "ROOT_STORAGE\\" + path;
	}
};