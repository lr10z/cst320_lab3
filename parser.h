/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				05/16/14
* Last Modification Date:	05/19/14
* Lab Number:				CST 320 Lab 3
* Filename:					parser.h
*
************************************************************/
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <map>
#include <list>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct parserEntry
{
	parserEntry(string value, string type)
	{
		m_value = value;
		m_type = type;
	}

	std::string m_value;
	std::string m_type;
};

class Parser
{
	public :

		Parser( string tableIn );

		void start();

		list<string> getRule(string key1, string key2) { return m_table[make_pair(key1,key2)]; }

		map<pair<string, string>, list<string>>::iterator begin() { return m_table.begin(); }
		map<pair<string, string>, list<string>>::iterator end() { return m_table.end(); }

	private :

		bool temp;
		string prntRule;
		string startSymbl;
		list<string> rule;
		list<string> cStack;
		stack<string> m_stack;
		vector<parserEntry> m_input;
		map< pair<string,string>, list<string>> m_table;

		list<string>::iterator listIt;
		list<string>::reverse_iterator stackIt;
		map<pair<string, string>, list<string>>::iterator mapIt;
};

#endif