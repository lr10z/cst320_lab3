/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				05/16/14
* Last Modification Date:	05/19/14
* Lab Number:				CST 320 Lab 3
* Filename:					main.cpp
*
************************************************************/

#include <fstream>

#include "parser.h"

using  namespace  std;

int main()
{
	
	string filename;

	cout << "Enter text file name: ";
	cin >> filename;
	cout << endl << endl;

	ifstream in(filename);

	
	if (!in)
	{
		cout << "*** Error opening file '"
			<< filename
			<< "' ***"
			<< endl;

		exit(EXIT_FAILURE);
	}

	std::string tableIn((std::istreambuf_iterator<char>(in)),
		(std::istreambuf_iterator<char>()));

	Parser *p = new Parser( tableIn );

	in.close();

	return  EXIT_SUCCESS;
}