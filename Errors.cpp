#include "stdafx.h"
#include "Errors.h"

//he static vector that stores errors
static vector<string> m_ErrorMsgs;

/**/
/*
	Errors::InitErrorReporting()

	NAME
		Errors::InitErrorReporting - class initializer

	SYNOPSIS
		void Errors::InitErrorReporting();

	DESCRIPTION
		Class initializer that clears the vector that store error messages.

	RETURNS
		Not-a-thing.

	AUTHOR
		Ashmin Bhandari
	DATE
		05/09/2018
*/
/**/

void Errors::InitErrorReporting()
{
	m_ErrorMsgs.clear();
} 


  /**/
  /*
    Errors::RecordError(string & a_emsg)
  
	NAME
		Errors::RecordError - Records the error 

	SYNOPSIS
		void Errors::RecordError(string & a_emsg);

	    a_emsg -> Error stored as string  
	
	DESCRIPTION
		Keeps a log of the errors encountered by storing it in a vector. 

	RETURNS
		Not-a-thing.
  
	AUTHOR
		Ashmin Bhandari
	
	DATE
		05/09/2018
  */
  /**/

void Errors::RecordError(string & a_emsg)
{
	m_ErrorMsgs.push_back(a_emsg);
} 


  /**/
  /*
	Errors::DisplayErrors()
	NAME
		 Errors::DisplayErrors - Displays the recorded errors

	SYNOPSIS
		void Errors::DisplayErrors();

	DESCRIPTION
		Displays all the recorded errors.

	RETURNS
		Not-a-thing.

	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-2018
  */
  /**/

void Errors::DisplayErrors()
{
	int count = 0;
	for (vector<string>::iterator it = m_ErrorMsgs.begin(); it != m_ErrorMsgs.end(); ++it) {
		cout << "ERROR:(" << setw(2) << count++ <<  ") " << *it << endl;
	}
} 


  /**/
  /*
	bool Errors::Empty()
	NAME
		Errors::Empty - Checks if the error log is empty or not

	SYNOPSIS
		bool Errors::Empty();

	DESCRIPTION
		Checks the size of the vector that stores the error messages to check whether or not it is empty. 

	RETURNS
		'true': If there are no errors.
		'false': If there are errors.

	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-2018
  */
  /**/
bool Errors::Empty()
{	
	if (m_ErrorMsgs.size() == 0) return true;
	return false;
} 