#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"

/**/
/*
NAME
Class -> Assembler

DESCRIPTION
Container for all the components that make up the assembler.

AUTHOR
Ashmin Bhandari

DATE
05/09/2018
*/
/**/


class Assembler {

public:
	//Constructor 
	Assembler(int argc, char *argv[])
		: m_facc(argc, argv) 
	{}

	// Pass I - establish the locations of the symbols
	void PassI();

	// Pass II - generate a translation
	void PassII();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

	// Run emulator
	void RunEmulator() {};

private:

	FileAccess m_facc;	      // File Access object
	SymbolTable m_symtab;     // Symbol table object
	Instruction m_inst;	    // Instruction object
	emulator m_emul;        // Emulator object

	// Vector that stores the machine code 
	vector<pair<int, string>> m_mcode;
};

