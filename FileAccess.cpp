#include "stdafx.h"
#include "FileAccess.h"


/**/
/*
	FileAccess::FileAccess( int argc, char *argv[] )

	NAME
		FileAccess Constructor - FileAccess class initializer

	SYNOPSIS
		FileAccess( int argc, char *argv[] );
		argc ->		argument count
		*argv[] ->	command line arguments

	DESCRIPTION
		Opens the file passed in as a command line argument. 
		If file isn't found an error is reported.

	RETURNS
		Not-a-thing.

	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-2018
*/
/**/

FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
} 





  /**/
  /*
	FileAccess::GetNextLine(string &a_buff)

	NAME
		FileAccess::GetNextLine - Gets the next line in the source code.

	SYNOPSIS
		bool FileAccess::GetNextLine(string &a_buff);

		a_buff ->	string to which the next line will be stored.

	DESCRIPTION
		Get the next line from the file and store it into the argument that was passed.

	RETURNS
		'false': if end-of-file reached,
		'true': or else.

	AUTHOR
		Ashmin Bhandari

	DATE
		12/05/2017
  */
  /**/


bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {

		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
} 


  /**/
  /*
	FileAccess::rewind( )
	
	NAME
		 FileAccess::rewind - rewinds the file to the beginning.

	SYNOPSIS
		void FileAccess::rewind( );
  
	DESCRIPTION
		Resets the end-of-file flag. Moves file access pointer to the beginning of the file for a re-read.
 
	 RETURNS
		Not-a-thing. 

	AUTHOR
		Ashmin Bhandari
  
	DATE
		 05-09-2018
  */
  /**/

void FileAccess::rewind()
{
	// Clean all file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
} 