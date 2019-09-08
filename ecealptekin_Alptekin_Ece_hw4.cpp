#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"DynIntStack.h"

using namespace std;

//Ece Alptekin
//24156
//Homework 4 – Python Program File Indentation Check with Stacks

void Empty(DynIntStack & Stack)
{ //deletes all elements of the stack
	int t;
	while(!Stack.isEmpty())
	{
		Stack.pop(t);
	}
}

bool CheckKeyword(string line, string &key)
{ //check if the line contains a keyword 
  //if true, then assign the keyword to the key
	char letter;
	string keyword;
	int i=0;

	while(line[i] == ' ')
	{
		i++;
	}

	for(i;i<line.length(); i++)
	{
		keyword = keyword + line[i];
	}

	if(keyword.substr(0,5) == "while")
	{
		key = keyword.substr(0,5);
		return true;
	}

	else if(keyword.substr(0,4) == "else" || keyword.substr(0,4) == "elif")
	{
		key = keyword.substr(0,4);
		return true;
	}

	else if(keyword.substr(0,3) == "for")
	{
		key = keyword.substr(0,3);
		return true;
	}

	else if(keyword.substr(0,2) == "if")
	{
		key = keyword.substr(0,2);
		return true;
	}

	return false;
}

int CountSpace(string line)
{ //counts the number of spaces at the beginning of the line
	char space = ' ';
	int num = 0;

	for(int i=0; i<line.length(); i++)
	{
		if(line[i] != space)
		{
			return num;
		}
		else if(line[i] == space)
		{
			num++;
		}
	}
}

int main()
{
	DynIntStack Stack;
	ifstream in;
	string filename;

	cout << "Please enter the file name that is going to be analyzed." << endl;
	cin >> filename;
	in.open(filename);

	while(!in.is_open())
	{
		cout << "Unable to open file please enter a different file name." << endl;
		cin >> filename;
		in.open(filename);
	}
	cout << "Starting file analysis..." << endl;
	cout << "Initial indentation level is pushed to the stack as 0." << "\n\n";
	Stack.push(0); //push the initial indentation level

	string line;
	int current = 0;
	int linecount = 1;
	int space;
	bool keyword;
	int space1;
	string key;
	bool keyword1;
	bool flag = true;

	while(getline(in,line) && flag == true)
	{
		space = CountSpace(line);
		keyword = CheckKeyword(line,key);

		cout << "Line number: " << linecount << endl;
		cout << "Line: " << line << endl;
		cout << space << " number of spaces observed before the start of the line." << endl;

		if(linecount == 1) //for first line
		{
			keyword1=false;
			space1=0;
		}

		if(keyword1 == true) //if the previous line has a keyword
		{
			cout << "This line proceeds a keyword containing line." << endl;

			if(current < space)
			{
				cout << "Current Level = " << current << " This Line = " << space << endl;
				cout << "Line correct. Depth " << space << " added to the stack." << endl;
				Stack.push(space);
				current = space;

				if(keyword == true)
				{
					cout << "Keyword " << key << " found on this line." << "\n\n";
				}

				else
				{
					cout << "\n";
				}
			}

			else if(current == space || current > space) //error case
			{
				cout << "Current Level = " << current << " This Line = " << space << endl;
				cout << "Incorrect file structure." << endl;
				cout << "Current line must be greater than the Current indentation level." << endl;
				cout << "Stopping file analysis..." << endl;
				flag = false;
			}
			space1 = space;
			keyword1 = keyword;
		}

		else if(keyword1 == false) //if the previous line does not contain a keyword
		{
			if(current == space && keyword == true)
			{
				cout << "Current Level = " << current << " This Line = " << space << endl;
				cout << "Line belongs to current block." << endl;
				cout << "Keyword " << key << " found on this line." << "\n\n";
			}

			else if(current == space && keyword == false)
			{
				cout << "Current Level = " << current << " This Line = " << space << endl;
				cout << "Line belongs to current block." << "\n\n";
			}

			else if(current > space)
			{
				Stack.pop(current);
				while(current > space && !Stack.isEmpty() && current != 0) 
				{
					cout << "Current Level = " << current << " This Line = " << space << endl;
					cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." <<endl;
					Stack.pop(current);
				}

				if(current == 0 && space != 0) //error case
				{
					cout << "Current Level = " << current << " This Line = " << space << endl;
					cout << "Incorrect file structure." << endl;
					cout << "An indentation level same as the Current line is not found in outer blocks." << endl;
					cout << "Stopping file analysis...";
					flag = false;
				}

				else if(current == 0 && space == 0) //current and the space of the line equals to the indentation level
				{
					cout << "Current Level = " << current << " This Line = " << space << endl;
					cout << "Line belongs to outer block." << endl;
					Stack.push(0);

					if(keyword == true)
					{
						cout << "Keyword " << key << " found on this line." << "\n\n";
					}

					else
					{
						cout << "\n";
					}
				}

				else if(current == space && keyword == true)
				{
					cout << "Current Level = " << current << " This Line = " << space << endl;
					Stack.push(current); //the current will be push to the stack again
					cout << "Line belongs to outer block." << endl;
					cout << "Keyword " << key << " found on this line." << "\n\n";
				}

				else if(current == space && keyword == false)
				{
					cout << "Line belongs to current block." << "\n";
				}
			}

			else if(current < space) //error case
			{
				cout << "Current Level = " << current << " This Line = " << space << endl;
				cout << "Incorrect file structure." << endl;
				cout << "Current line cannot be greater than the Current indentation level." << endl;
				cout << "Stopping file analysis..." << endl;
				flag = false;
			}

			space1 = space;
			keyword1 = keyword;

		}
		linecount++;
	}


	if(flag == true) 
	{
		cout << "\n";
		cout << "Finished file analysis. File structure is correct!" << endl;
		cout << "Stack emptied and program ending." << endl;
	}

	else if(flag == false) //the program did not finish properly
	{
		cout << "\n\n";
		cout << "Stack emptied and program ending." << endl;
	}

	Empty(Stack); //dynamic memory allocation

	cin.get();
	cin.ignore();
	return 0;
}