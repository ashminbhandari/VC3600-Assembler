/**/
/*
	NAME
		Assem - The entry point for the program

	SYNOPSIS
		Runs the Assembler and Emulator

	DESCRIPTION
		Compiles and executes the fed assembly code. 

		Initializes an instance of the Assembler class. Parses the code, creates a symbol table, 
		and performs calculations and insertions of instructions into the memory.

		Prints error messages if there are any. Runs the emulator if there are no errors. 
		
	RETURNS 
		0
		
	AUTHOR
		Ashmin Bhandari

	DATE
		05/08/2018
*/
/**/

#include "stdafx.h"     
#include "Assembler.h"

int main(int argc, char *argv[])
{
	//Initialize an instance of the Assembler class
	Assembler assem(argc, argv);

	// Establish the location of the labels:
	assem.PassI();

	// Display the symbol table.
	assem.DisplaySymbolTable();

	// Output the translation of the assembly code.
	assem.PassII();

	return 0;
}