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

	string getFullPath() const //Path generation
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
};