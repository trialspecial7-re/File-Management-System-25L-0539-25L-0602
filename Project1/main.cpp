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
	int typeChoice;

	cout << "---VIRTUAL FILE SYSTEM SHELL---" << endl;
	cout << "Commands:" << endl;
	cout << "  1  ls " << endl;
	cout << "  2  cd <name>  " << endl;
	cout << "  3  mkdir <name>  " << endl;
	cout << "  4  touch <name> <type> " << endl;
	cout << "       Types: 1=Text  2=Audio  3=Private  4=Zip" << endl;
	cout << "  5  rm <name> " << endl;
	cout << "  6  open <name> " << endl;
	cout << "  7  search <name> " << endl;
	cout << "  8  rename <old> <new> " << endl;  
	cout << "  9  exit" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;

	while (true)
	{
		cm.printUI();//displays path

		if (!(cin >> command))
			break;

		if (command == "9")
		{
			cout << "Exiting system..." << endl;
			break;
		}
		else if (command == "1")
		{
			cm.ls();
		}
		else if (command == "2")
		{
			if (cin >> argument)
				cm.cd(argument);
		}
		else if (command == "3")
		{
			if (cin >> argument)
				cm.mkdir(argument);
		}
		else if (command == "4")
		{
			if (cin >> argument)
			{
				if (cin >> typeChoice)
				{
					if (typeChoice >= 1 && typeChoice <= 4)
						cm.touch(argument, typeChoice);
					else
						cout << "Error: Type must be 1-4." << endl;
				}
				else
				{
					cout << "Error: File type must be a number (1-4)." << endl;
					cleanInput();
				}
			}
		}
		else if (command == "5")
		{
			if (cin >> argument)
				cm.rm(argument);
		}
		else if (command == "6")
		{
			if (cin >> argument)
				cm.openNode(argument);
		}
		else if (command == "7")
		{
			if (cin >> argument)
				cm.search(argument);
		}
		else if (command == "8")
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
			cout << "Error: Invalid command. Use 1-9." << endl;
			cleanInput();
		}
	}

	return 0;
}
