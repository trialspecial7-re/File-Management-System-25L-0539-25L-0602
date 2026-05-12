#include "Files.h"
#include <iostream>
#include <fstream>
using namespace std;

//TEXT FILE
void TextFile::open()
{
	ifstream inFile(getDiskPath());

	if (inFile.is_open())
	{
		totalLines = 0;

		while (getline(inFile, lines[totalLines]))
		{
			totalLines++;

			if (totalLines >= 100)
				break;
		}

		inFile.close();
	}
	int currentLine = 0;
	string cmd;

	cout << "\nText Editor: " << name << endl;
	cout << "Commands: " << endl;
	cout << "1. ADD" << endl;
	cout << "2. VIEW" << endl;
	cout << "3. UP" << endl;
	cout << "4. DOWN " << endl;
	cout << "5. EDIT " << endl;
	cout << "6. SAVE " << endl;


	while (true)
	{
		//ensure current line display is always correct
		cout << "(line ";
		if (totalLines == 0)
		{
			cout << "0";
		}
		else
		{
			cout << currentLine + 1;
		}
		cout << "/" << totalLines << ") > ";

		cin >> cmd;

		if (cmd == "6")   // SAVE & EXIT
		{
			///ofstream outFile(name);
			ofstream outFile(getDiskPath());
			if (outFile.is_open())
			{
				for (int i = 0; i < totalLines; i++)
					outFile << lines[i] << "\n";
				outFile.close();
				cout << "File saved to disk successfully." << endl;
			}
			else
			{
				cout << "Warning: Could not save to disk (check folder permissions)." << endl;
			}
			break;
		}
		else if (cmd == "1")   // ADD
		{
			if (totalLines < 100)
			{
				cout << "Enter line text: ";
				cin.ignore();
				getline(cin, lines[totalLines]);
				totalLines++;
				currentLine = totalLines - 1;
			}
			else
			{
				cout << "Error: Maximum capacity reached (100 lines)." << endl;
			}
		}
		else if (cmd == "2")   // VIEW
		{
			if (totalLines == 0)
			{
				cout << "(empty file)" << endl;
			}
			else
			{
				for (int i = 0; i < totalLines; i++)
				{
					cout << (i == currentLine ? "->" : "  ");
					cout << i + 1 << ": " << lines[i] << endl;
				}
			}
		}
		else if (cmd == "3")   // UP
		{
			if (currentLine > 0)//validation to prevent negative index
			{ 
				currentLine--;
			}	
			else
				cout << "Already at top of file." << endl;
		}
		else if (cmd == "4")   // DOWN
		{
			if (currentLine < totalLines - 1)
			{
				currentLine++;
			}
			else
			{
				cout << "Already at bottom of file." << endl;
			}
		}
		else if (cmd == "5")   // EDIT
		{
			if (totalLines > 0)
			{
				cout << "Current: " << lines[currentLine] << endl;
				cout << "New text: ";
				cin.ignore();
				getline(cin, lines[currentLine]);
			}
			else
			{
				cout << "Nothing to edit. Use ADD (1) first." << endl;
			}
		}
		else
		{
			cout << "Unknown command. Use 1-6 ONLY!." << endl;
		}
	}
}

//  PRIVATE FILE
void PrivateFile::open()
{
	if (validateKey())
		cout << "Access granted! Opening: " << name << endl;
	else
		cout << "Access denied! Invalid passkey." << endl;
}

// AUDIO FILE
void AudioFile::open()
{
	string path = getDiskPath();

	ifstream checkFile(path);

	if (!checkFile.is_open())
	{
		cout << "Error: Audio file not found: " << path << endl;
		return;
	}

	checkFile.close();

	cout << "Playing: " << path << endl;

	string playCmd = "start wmplayer \"" + path + "\"";

	system(playCmd.c_str());
}

