//Parenthesis Checker: checks if all opening and ending parenthesis, brackets, or braces have a corresponding opening and ending brace
//Navie Vurdien
//CPSC 131
#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <string>
#include <map>
using namespace std;
struct Bracket {
	char type;
	int line;
	size_t col;
};
class Brackets
{
public:
	Brackets() {}//constructor
	~Brackets() {}//destructor

				  //adds line to the lines array
	void Brackets::add_line(string line)
	{
		lines[line_num] = line;//adds line
		line_num++;//increments number of lines
	}

	//checks if brackets have a pair
	void Brackets::check_bracket()
	{
		Bracket temp;//instantiates new struct
		for (int a = 0; a < line_num; a++)//loops through every line
		{
			for (size_t c = 0; c < lines[a].length(); c++)//loops through every char in string
			{
				while (lines[a].find("//") != -1) a++;//checks if there is a comment
				if (lines[a][c] == '"')//checks if there is a quote to indicate a string
				{
					c++;
					while (lines[a][c] != '"') c++;//increments c while char is not a quote
				}
				if (lines[a][c] == '(')//checks if char is a round brace
				{
					temp = { ')', a, c };//creates new bracket
					bracket.push(temp);//pushs the brace in
				}
				if (lines[a][c] == '[')//checks if char is square brace
				{
					temp = { ']', a, c };//creates new bracket
					bracket.push(temp);//pushs the brace in
				}
				if (lines[a][c] == '{')//checks if the brace is a curly brace
				{
					temp = { '}', a, c };//creates new bracket
					bracket.push(temp);//pushs the brace in
				}
				if (lines[a][c] == ')' || lines[a][c] == ']' || lines[a][c] == '}')//checks if the brace is a close brace
				{
					if (bracket.empty())
					{//if empty then tells user the bracket does not match any open parenthesis
						cout << "closed parenthesis " << lines[a][c] << " does not match any open parenthesis.";
						return;
					}
					//else if the brackets do match an open brace then it pops it out
					else if ((lines[a][c] == bracket.top().type) || (lines[a][c] == bracket.top().type) || (lines[a][c] == bracket.top().type))
					{
						bracket.pop();
					}//if brace does not match top open brace on stack
					else
					{
						cout << "Line " << a + 1 << ":" << " error at column " << c + 1 << ":" << endl;
						cout << lines[a] << endl;
						for (size_t o = 0; o < c; o++)
							cout << " ";
						cout << "^" << endl;
						cout << "closed parenthesis " << lines[a][c] << " does not match open parenthesis " <<
							lines[bracket.top().line][bracket.top().col] << " from row " << bracket.top().line + 1 << " and column " << bracket.top().col + 1;
						return;
					}
				}
			}
		}
		if (!bracket.empty())//if bracket still contains something in the stack then it informs user
		{
			cout << "Error: Unmatched open parenthesis " << lines[bracket.top().line][bracket.top().col] <<
				" at row " << bracket.top().line + 1 << " and column " << bracket.top().col + 1 << endl;
			cout << lines[bracket.top().line] << endl;
			for (size_t o = 0; o < bracket.top().col; o++)
				cout << " ";
			cout << "^" << endl;
		}
		else
			cout << "No parenthesization errors." << endl;//otherwise no parenthesis errors
	}
	void Brackets::clear()
	{
		for (string chk : lines) chk.clear();//contains code lines
		line_num = 0;//number of lines
		while (!bracket.empty()) bracket.pop();//brackets
		cout << endl;
	}
private:
	string lines[1000];//contains code lines
	int line_num = 0;//number of lines
	stack<Bracket> bracket;//brackets
};

int main(int argc, char *argv[]) {
	string filename;
	Brackets check;
	char again = 'y';
	while (again == 'y' || again == 'Y')
	{
		if (argc >= 2) {
			filename = argv[1]; // command line arguments are given. The first argument is the filename
		}
		else {
			cout << "Enter name of file to check: ";
			cin >> filename;
		}
		cout << "File to check:" << filename << endl;

		ifstream infile(filename);
		if (!infile) {
			cout << "That file does not exist" << endl;
			return (-1); // end the program
		}

		string line;
		while (getline(infile, line)) {
			check.add_line(line);
		}
		infile.close();

		check.check_bracket();
		check.clear();
		cout << "Another file? [Y/N]";
		cin >> again;
		cout << endl;
	}
	system("pause");
	return(0);
}
