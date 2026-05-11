#include "CommandManager.h"
#include <iostream>
#include <string>

using namespace std;

void cleanInput()
{
	if (cin.fail())
		cin.clear();
	while (cin.get() != '\n');
}

int main()
{
	CommandManager cm;
	string command;
	string argument;
	string argument2;   //second argument needed for rename
	string typeChoice;

	cout << "---VIRTUAL FILE SYSTEM SHELL---" << endl;
	cout << "Commands:" << endl;
	cout << "  ls " << endl;
	cout << "  cd <name>  " << endl;
	cout << "  mkdir <name>  " << endl;
	cout << "  touch <name> <type> " << endl;
	cout << "     Types: 1=Text  2=Audio  3=Private  4=Zip" << endl;
	cout << "  rm <name> " << endl;
	cout << "  open <name> " << endl;
	cout << "  search <name> " << endl;
	cout << "  rename <old> <new> " << endl;  
	cout << "  exit" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;

	while (true)
	{
		cm.printUI();//displays path

		if (!(cin >> command))
			break;

		if (command == "exit")
		{
			cout << "Exiting system..." << endl;
			break;
		}
		else if (command == "ls")
		{
			cm.ls();
		}
		else if (command == "cd")
		{
			if (cin >> argument)
				cm.cd(argument);
		}
		else if (command == "mkdir")
		{
			if (cin >> argument)
				cm.mkdir(argument);
		}
		else if (command == "touch")
		{
			if (cin >> argument)
			{
				if (cin >> typeChoice)
				{
					/*if (typeChoice != "text" || typeChoice != "audio" || typeChoice != "private" || typeChoice != "zip")
						cm.touch(argument, typeChoice);
					else
						cout << "Error: Type must be 1-4." << endl;*/
					if (typeChoice == "text" ||
						typeChoice == "audio" ||
						typeChoice == "private" ||
						typeChoice == "zip")
					{
						cm.touch(argument, typeChoice);
					}
					else
					{
						cout << "Error: Invalid type." << endl;
					}
				}
				else
				{
					cout << "Error: File type must be a number (1-4)." << endl;
					cleanInput();
				}
			}
		}
		else if (command == "rm")
		{
			if (cin >> argument)
				cm.rm(argument);
		}
		else if (command == "open")
		{
			if (cin >> argument)
				cm.openNode(argument);
		}
		else if (command == "search")
		{
			if (cin >> argument)
				cm.search(argument);
		}
		else if (command == "rename")
		{
			
			if (cin >> argument >> argument2)
				cm.rename(argument, argument2);
			else
			{
				cout << "Usage: 8 <currentName> <newName>" << endl;
				cleanInput();
			}
		}
		else
		{
			cout << "Error: Invalid command." << endl;
			cleanInput();
		}
	}

	return 0;
}

