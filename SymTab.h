#pragma once

/**/
/*
		NAME
			SymbolTable - maintains a table of symbols and their addresses

		DESCRIPTION
			Maintains a table of symbols and their addresses. 

		AUTHOR
			Ashmin Bhandari

		DATE
			05-09-2018
*/
/**/


class SymbolTable {

public:
	// Get rid of constructor and destructor if you don't need them.
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	static bool LookupSymbol(const string &a_symbol, int &a_loc);

private:
	
};