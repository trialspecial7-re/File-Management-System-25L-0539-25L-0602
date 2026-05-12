#pragma once
#include "Folder.h"
#include "Files.h"

class CommandManager {
	Folder* root;//The entry point of the file system
	Folder* currentFolder;//Pointer to the directory user is currently in
public:
	CommandManager();
	~CommandManager();

	void ls();//lists all nodes in current directory
	void cd(string name); //Changes directory or moves up with ".."
	void mkdir(string name);// Creates a new folder node
	void touch(string name, string type); //  for existing node to zip
	void rm(string name); //Removes a node with validation
	void openNode(string name);//opens the node
	void search(string name); // finds ALL matches, not just first
	void rename(string targetName, string newName);  // renames a named node
	void printUI();//Prints the current path for the terminal
};


