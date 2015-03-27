/***********************************************************
* Author:					Leander Rodriguez
* Date Created:				05/16/14
* Last Modification Date:	05/19/14
* Lab Number:				CST 320 Lab 3
* Filename:					parser.cpp
*
************************************************************/
#include <cctype>
#include <locale>

#include "parser.h"


Parser::Parser(string tableIn)
{
	// local variables
	string	nonTerminal,
			terminal,
			rules;
			//prntRule;

	// string buffer created
	istringstream iss(tableIn);

	// parses string into new lines
	while (getline(iss, tableIn, '\n'))
	{
		// line buffer created
		stringstream ss(tableIn);

		// find and display all comments
		size_t pos = tableIn.rfind("//");

		if (pos != string::npos)
		{
			cout << tableIn << endl;
			continue;
		}

		// inserts keys into table
		ss >> nonTerminal >> terminal;

		string str;

		// inserts rules into table
		while (ss >> rules)
		{
			if (m_table.empty())
			{
				startSymbl = nonTerminal;
			}

			m_table[std::make_pair(nonTerminal, terminal)].push_back(rules);
		}

	}
	
	
	//
	// User enters language string
	//
	cout << endl;

	string value, str;

	if (cin.peek() == '\n')
	{
		cin.ignore();
	}
	
	// splits input into individual tokens and
	// stores both the tokens' values and types
	if (getline(cin, str))
	{
		istringstream iss(str); // break them by spaces

		while (iss >> value)
		{
			if (isalpha(value[0]))
			{
				m_input.push_back(parserEntry(value, "ID"));
			}
			else if (isdigit(value[0]))
			{
				m_input.push_back(parserEntry(value, "Num"));
			}
			else
			{
				m_input.push_back(parserEntry(value, "Symbol"));
			}
		}
	}

	cout << endl;

	// Display current stack and current rule
	cout << endl << "Stack" "\t\t\t" << right << "Rule" << endl;
	cout << "-----" << "\t\t\t" << right << "----" << endl;

	// parse input string
	do
	{

		if (!m_stack.empty() && m_stack.top() == m_input.front().m_type )
		{
			m_stack.pop();
			cStack.pop_back();

			// display stack and rule status
			for (listIt = cStack.begin(); listIt != cStack.end(); ++listIt)
			{
				cout << *listIt << " ";
			}

			cout << "\t\t\t" << right << "pop" << endl;

			// erase first token in input string and shift to the left
			m_input.erase(m_input.begin());
		}
		else if(!m_stack.empty() && m_input.front().m_value == m_stack.top())
		{
			m_stack.pop();
			cStack.pop_back();

			// display stack status
			for (listIt = cStack.begin(); listIt != cStack.end(); ++listIt)
			{
				cout << *listIt << " ";
			}

			cout << "\t\t\t" << right << "pop" << endl;

			// erase first token in input string and shift to the left
			m_input.erase(m_input.begin());
		}
		else
		{
			// clears previously printed rule
			prntRule = " ";

			// rule if found based on associated keys
			// key 1. non-terminal
			// key 2. current input character
			temp = false;

			// if stack is empty, we tell program what start symbol to start with
			if (m_stack.empty())
			{
				start();
			}
			else
			{

				rule = getRule(m_stack.top(), m_input.front().m_value);

				if (!rule.empty())
				{
					nonTerminal = m_stack.top();
					temp = true;
				}
				if (*rule.begin() == "lambda")
				{
					m_stack.pop();
					cStack.pop_back();
				}
				
				if (temp != true)
				{
					for (mapIt = begin(); mapIt != end(); ++mapIt)
					{
						if (mapIt->first.second == m_input.front().m_type)
						{
							rule = getRule(mapIt->first.first, m_input.front().m_type);
							break;
						}
					}
				}

				if (cStack.size() >= 1)
				{
					if (nonTerminal == cStack.back())
					{
						m_stack.pop();
						cStack.pop_back();
					}
				}

				if (*rule.begin() != "lambda")
				{
					for (stackIt = rule.rbegin(); stackIt != rule.rend(); ++stackIt)
					{
						cStack.push_back(*stackIt);
						m_stack.push(*stackIt);
					}
				}

				// displays rule
				for (listIt = rule.begin(); listIt != rule.end(); ++listIt)
				{
					prntRule += *listIt + " ";
				}

				// display stack status
				for (listIt = cStack.begin(); listIt != cStack.end(); ++listIt)
				{
					cout << *listIt << " ";
				}

				cout << "\t\t\t" << nonTerminal << " -> " << prntRule << endl;
			}
		}

		// display for successful parse
		if (m_input.empty() && cStack.empty())
		{
			cout << endl
				<< endl
				<< "User input string parsed successfully."
				<< endl
				<< endl;
		}
		else if (m_input.empty() && cStack.size() > 1 )
		{
			cout << endl
				<< "ERROR: Input string does not match grammar rules."
				<< endl
				<< endl
				<< endl;
			return;
		}
		else if (m_input.empty() && !cStack.empty())
		{
			// handle lambda rule here if stack is not empty
			m_stack.pop();
			cStack.pop_back();
			cout << "\t\t\t" << right << "pop" << endl;

			cout << endl
				<< endl
				<< "User input string parsed successfully."
				<< endl
				<< endl;
		}

	} while (!m_input.empty());
}

void Parser::start()
{
	// iterate through start symbol to find first rule
	for (auto m = m_table.begin(); m != m_table.end(); ++m)
	{
		if (!rule.empty())
		{
			break;
		}

		if (m->first.first == startSymbl)
		{
			for (m; m != m_table.end(); m)
			{
				if (m->first.first != startSymbl)
				{
					break;
				}

				rule = getRule(m->first.first, m_input.front().m_value);

				if (!rule.empty())
				{
					temp = true;
					break;
				}

				++m;
			}
		}
	}

		for (stackIt = rule.rbegin(); stackIt != rule.rend(); ++stackIt)
		{
			cStack.push_back(*stackIt);
			m_stack.push(*stackIt);
		}

		// displays rule
		for (listIt = rule.begin(); listIt != rule.end(); ++listIt)
		{
			prntRule += *listIt + " ";
		}

		// display stack status
		for (listIt = cStack.begin(); listIt != cStack.end(); ++listIt)
		{
			cout << *listIt << " ";
		}

		cout << "\t\t\t" << startSymbl << " -> " << prntRule << endl;
}