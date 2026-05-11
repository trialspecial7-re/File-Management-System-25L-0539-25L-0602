#include "CommandManager.h"

CommandManager::CommandManager()
{
	root = new Folder("root", nullptr);
	currentFolder = root;//Sets the starting directory to root
}

CommandManager::~CommandManager()
{
	delete root;
}

//ls: lists all contents of the current directory
void CommandManager::ls()
{
	currentFolder->listNodes();
}

//cd: navigates the file system
void CommandManager::cd(string name)
{
	if (name == "..")
	{
		if (currentFolder->getParent() != nullptr)
		{
			Folder* parentFolder = dynamic_cast<Folder*>(currentFolder->getParent());//updating the pointer
			if (parentFolder)
				currentFolder = parentFolder;
		}
		else
		{
			cout << "Already at root folder." << endl;
		}
	}
	else
	{
		Node* target = currentFolder->getChild(name);//search for the target in current array
		if (target == nullptr)
		{
			cout << "Error: '" << name << "' not found." << endl;
		}
		else if (target->getType() == "Folder")
		{
			Folder* f = dynamic_cast<Folder*>(target);
			if (f) currentFolder = f;
		}
		else
		{
			cout << "Error: '" << name << "' is a file, not a folder." << endl;
		}
	}
}

//mkdir: creates a new folder
void CommandManager::mkdir(string name)
{
	if (name.empty())//valid input name
	{
		cout << "Error: Folder name cannot be empty." << endl;
		return;
	}
	currentFolder->addNode(new Folder(name, currentFolder));
	cout << "Folder '" << name << "' created." << endl;
}

//touch: creates one of the four file types
void CommandManager::touch(string name, string type)
{
	if (name.empty())
	{
		cout << "Error: File name cannot be empty." << endl;
		return;
	}

	if (type == "text")
	{
		currentFolder->addNode(new TextFile(name, currentFolder));
	}
	else if (type == "audio")
	{
		currentFolder->addNode(new AudioFile(name, currentFolder));
	}
	else if (type == "private")
	{
		string key;
		cout << "Enter passkey for new private file: ";
		cin >> key;
		currentFolder->addNode(new PrivateFile(name, key, currentFolder));
	}
	else if (type == "zip")
	{
		
		cout << "Enter name of existing node to zip: ";
		string targetName;
		cin >> targetName;

		Node* target = currentFolder->getChild(targetName);
		if (target == nullptr)
		{
			cout << "Error: '" << targetName << "' not found in current folder." << endl;
			return;
		}
		if (target->getType() == "Zip File")
		{
			cout << "Error: Cannot zip a file that is already zipped." << endl;
			return;
		}

		// The zip node is named "<original>-zip.zip" automatically by ZipFile constructor
		currentFolder->addNode(new ZipFile(targetName, currentFolder));
		cout << "'" << targetName << "' zipped successfully as '"
			<< targetName << "-zip.zip'." << endl;
	}
	else
	{
		cout << "Error: Invalid file type." << endl;
	}
}

//rm: removes a node with validation for private files
void CommandManager::rm(string name)
{
	Node* target = currentFolder->getChild(name);//search for the node
	if (target == nullptr)//existence validation
	{
		cout << "Error: '" << name << "' not found." << endl;
		return;
	}
	// Extra validation for private files
	if (target->getType() == "Private File")
	{
		PrivateFile* pf = dynamic_cast<PrivateFile*>(target);
		if (pf && !pf->validateKey())//request passkey
		{
			cout << "Incorrect passkey. Deletion aborted." << endl;
			return;
		}
		string confirm;
		cout << "Are you sure you want to permanently delete '" << name << "'? (Y/N): ";
		cin >> confirm;
		if (confirm != "Y" && confirm != "y")
		{
			cout << "Deletion cancelled." << endl;
			return;
		}
	}

	if (currentFolder->removeNode(name))
		cout << "'" << name << "' deleted successfully." << endl;
	else
		cout << "Error: Could not remove '" << name << "'." << endl;
}

// openNode: validation and execution of file-specific logic
void CommandManager::openNode(string name)
{
	Node* target = currentFolder->getChild(name);// Search for the file
	if (target == nullptr)
	{
		cout << "Error: '" << name << "' not found." << endl;
		return;
	}
	// Folders are navigated with 'cd', not 'open'
	if (target->getType() == "Folder")
	{
		cout << "Error: '" << name << "' is a folder. Use 'cd " << name << "' to enter it." << endl;
		return;
	}
	target->open();
}

//search: deep search using an iterative stack
void CommandManager::search(string name)
{
	Node* stack[200];
	int top = -1;
	bool found = false;
	stack[++top] = root;

	while (top >= 0) //stack is not empty
	{
		Node* curr = stack[top--];//pop top node

		if (curr->getName() == name)//checks for match
		{
			cout << "Found: " << curr->getFullPath() << endl; //prints complete path
			found = true;
			// Do NOT return to keep searching for more matches
		}

		if (curr->getType() == "Folder")//if it is folder a push children to stack
		{
		
			Folder* f = dynamic_cast<Folder*>(curr);
			if (f)
			{
				for (int i = 0; i < f->getCount(); i++)
				{
					if (top < 199)
						stack[++top] = f->getChildAt(i);
				}
			}
		}
	}

	if (!found)
		cout << name << " not found." << endl;
}

//rename: renames the currently opened folder
void CommandManager::rename(string targetName, string newName)
{
	if (targetName.empty() || newName.empty())
	{
		cout << "Error: Names cannot be empty." << endl;
		return;
	}

	Node* target = currentFolder->getChild(targetName);
	if (target == nullptr)
	{
		cout << "Error: '" << targetName << "' not found in current folder." << endl;
		return;
	}

	// Prevent duplicate names
	if (currentFolder->doesNameExist(newName))
	{
		cout << "Error: A node named '" << newName << "' already exists in this folder." << endl;
		return;
	}

	target->setName(newName);
	cout << "'" << targetName << "' renamed to '" << newName << "' successfully." << endl;
}

//printUI: displays the command prompt path
void CommandManager::printUI()
{
	cout << "\n";
	cout << currentFolder->getFullPath();
	cout << ">";
}
