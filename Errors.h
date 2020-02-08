#ifndef _ERRORS_H
#define _ERRORS_H

/**/
/*
NAME
	Errors - Handles errors (holds and displays)

DESCRIPTION
	Class that holds and displays the errors. 
	
	Note: Members are static so they can be accessed anywhere.


AUTHOR
	Ashmin Bhandari

DATE
	05/09/2018
*/
/**/


#include <string>
#include <vector>

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	// Check if the error list is empty.
	static bool Empty();

private:
	

};
#endif