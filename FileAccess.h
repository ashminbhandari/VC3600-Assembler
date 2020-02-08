#pragma once

/**/
/*
	NAME
		Class -> FileAccess - Handles file accessing 

	DESCRIPTION
		Opens and reads the source code file provided as a command line argument.

	AUTHOR
		Ashmin Bhandari
	
	DATE
		05/09/2018
*/
/**/

//Include files
#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

	// Opens the file.
	FileAccess(int argc, char *argv[]);

	// Get the next line from the source file.
	bool GetNextLine(string &a_buff);

	// Put the file pointer back to the beginning of the file.
	void rewind();

private:

	ifstream m_sfile;		// Source file object.
};
