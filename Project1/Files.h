#pragma once
#ifndef FILES_H
#define FILES_H

#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// TEXT FILE
class TextFile : public Node {
	string lines[100];
	int totalLines;          
public:
	TextFile(string n, Node* p = nullptr): Node(n + ".txt", p), totalLines(0)  
	{

	}

	string getType() override //Used by ls and search
	{
		return "Text File"; 
	}
	void open() override;
	/*{
		cout << "Text File: " << name << endl;
		cout << "Commands: add, edit, view, exit" << endl;
	}*/
};

//  AUDIO FILE
class AudioFile : public Node {
public:
	
	AudioFile(string n, Node* p = nullptr) : Node(n + ".mpg", p)
	{
		cout << "Recording audio for 5 seconds..." << endl;
		string recordCmd = "ffmpeg -f dshow -i audio=\"Microphone\" -t 5 \""
			+ name + "\" -loglevel quiet";
		int result = system(recordCmd.c_str());
		if (result == 0)
			cout << "Recording complete! File saved as: " << name << endl;
		else
			cout << "Warning: ffmpeg not found. Audio node created without recording." << endl;
	}

	string getType() override 
	{ 
		return "Audio File";
	}
	void open() override;
	/*{
	cout << "Playing audio: " << name << "..." << endl;
	string cmd = "start " + name;
	system(cmd.c_str());
}*/
};

// PRIVATE FILE 
class PrivateFile : public Node {
	string passkey;
public:
	PrivateFile(string n, string key, Node* p = nullptr): Node(n + ".priv", p), passkey(key) 
	{

	}

	string getType() override 
	{
		return "Private File";
	}
	//Valid logic used by both open() and rm commands
	bool validateKey()
	{
		string input;
		cout << "Enter passkey for [" << name << "]: ";
		cin >> input;
		if (input == passkey)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void open() override;
	/*{
		if (validateKey())
		{
			cout << "Access granted: " << name << endl;
		}
		else
		{
			cout << "Access denied: Invalid passkey!" << endl;
		}
	}*/
	string getPasskey() const 
	{
		return passkey; 
	}
};

// ZIP FILE
class ZipFile : public Node {
	string zippedNodeName;   
public:
	ZipFile(string originalNodeName, Node* p = nullptr): Node(originalNodeName + "-zip.zip", p),zippedNodeName(originalNodeName)
	{

	}

	string getType() override 
	{
		return "Zip File";
	}

	string getZippedNodeName() const 
	{
		return zippedNodeName;
	}

	
	void open() override
	{
		cout << "Error: Zipped files cannot be opened. Unzip first!" << endl;
	}
};

#endif

