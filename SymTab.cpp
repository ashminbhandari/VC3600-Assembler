#include "stdafx.h"
#include "SymTab.h"

//The symbol table. 
static map<string, int> m_symbolTable; 


/**/
/*
	SymbolTable::AddSymbol(string &a_symbol, int a_loc)
	
	NAME
		SymbolTable::AddSymbol - Adds symbol to the symbol table

	SYNOPSIS
		void SymbolTable::AddSymbol(string &a_symbol, int a_loc);
		a_symbol: Symbol that is to be added to the table
		a_loc: Location of the symbol to be added to the table

	DESCRIPTION
		The symbol and its location will be put into the table

	RETURNS
		Not-a-thing.

	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-2018
*/
/**/

void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
} 


  /**/
  /*
	SymbolTable::DisplaySymbolTable()
	
	NAME
		SymbolTable::DisplaySymbolTable - Prints the symbol table.
  
	SYNOPSIS
		void SymbolTable::DisplaySymbolTable();
  
	DESCRIPTION
		Prints the symbol table.

	RETURNS
		Not-a-thing.

	AUTHOR
		Ashmin Bhandari
  
	DATE
		05-09-2018
  */
  /**/

void SymbolTable::DisplaySymbolTable()
{
	cout << setw(12) << left << "Symbol no." << setw(24) << left << "Symbol" << left << "Address" << endl;
	int count = 0;
	for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
		cout << setw(12) << left << count++ << setw(24) << left << it->first << left << it->second << endl;
	}
	cout << endl;
} 


  /**/
  /*
	SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
  
	NAME
		SymbolTable::LookupSymbol - Looks up a symbol in the table.
  
	SYNOPSIS
		bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc);
		a_symbol : Symbol to be look up.
		a_loc  : Location of the symbol.
  
	DESCRIPTION
		Looks up and if found stores the location of a symbol.
  
	RETURNS
		'true' : if symbol was found in the table
		'false' otherwise.
  
	AUTHOR
		Ashmin Bhandari
  
	DATE
		05-09-2018
  */
  /**/

bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)
{
	map<string, int>::iterator it = m_symbolTable.find(a_symbol);
	if (it != m_symbolTable.end()) {
		a_loc = it->second;
		return true;
	}
	return false;
} 
