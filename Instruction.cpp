#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
#include "SymTab.h"


/**/
/*
	Instruction::ParseInstruction(string & a_buff)

	NAME
		Instruction::ParseInstruction - instruction parser

	SYNOPSIS
		Instruction::InstructionType Instruction::ParseInstruction(string & a_buff);
		a_buff -> the instruction to be parsed

	DESCRIPTION
		Runs through the instruction and identifies what the label, opcode and operand is.
		Finds out the numberical value of the opcode and the operand.
 
	RETURNS
		The datatype: 'Instruction::InstructionType' 

	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-18
*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string & a_buff)
{
	//Initializing elements required for parsing
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = a_buff;

	m_parsedInstruction.clear();
	m_parsedInstruction.resize(0);

	// Finds the place where the comment starts
	size_t strt = m_instruction.find(';');

	// Deletes the comment
	if (strt != string::npos)
		m_instruction = m_instruction.substr(0, strt);

	stringstream ss(m_instruction);
	string tmp;
	while (ss >> tmp)
		m_parsedInstruction.push_back(tmp);

	// If an empty line or a line with a comment
	if (m_parsedInstruction.empty())
		m_type = InstructionType(2); //Comment or an empty line

	// Terminate machine code execution
	else if (to_lower(m_parsedInstruction[0]) == "halt")
		m_type = InstructionType(0); //Assembly instruction

	// Origin location 
	else if (to_lower(m_parsedInstruction[0]) == "org")
		m_type = InstructionType(1); //Assembler instruction

	// End the assembly language program
	else if (to_lower(m_parsedInstruction[0]) == "end")
		m_type = InstructionType(3); //end instruction

	 //Instructions with two fields (opcode and operand)
	else if (m_parsedInstruction.size() == 2)
		m_type = InstructionType(0); //Assembly instruction

	else {
		m_Label = m_parsedInstruction[0];

		if (m_parsedInstruction[1] == "dc" || m_parsedInstruction[1] == "DC" || m_parsedInstruction[1] == "ds" || m_parsedInstruction[1] == "DS")
			m_type = InstructionType(1); //Assembler instruction
		else
			m_type = InstructionType(0); //Assembly language instruction
	}

	return m_type;
} 
/**/
/*
	Instruction::TranslateInstruction(string & a_buff, int a_loc)
	
	NAME
		Instruction::TranslateInstruction - translates the instructions from the source code
  
    SYNOPSIS
		pair<int, string> Instruction::TranslateInstruction(string & a_buff, int a_loc);
		a_buff -> Line from the source code to be translated.
		a_loc  -> Location of the instruction of the translated code.
  
	DESCRIPTION
		Translates instructions from the fed source code into machine code. Reports errors if found. 
  
	RETURNS
		pair<int,string>
		First element of the pair is the location of the instruction being translated, and
		Second element of the pair is 6 digit op-code + operand combination.

		returns (0,"end") pair that indicates an end statement in the code
		returns (0,"n/a") pair that indicates the instruction is not for emulator
		
	AUTHOR
		 Ashmin Bhandari
	
	DATE
		05-09-2018
  */
  /**/

pair<int, string> Instruction::TranslateInstruction(string & a_buff, int a_loc)
{
	//Get the instruction type by parsing the lien
	Instruction::InstructionType st = ParseInstruction(a_buff);

	// Instruction with more than 3 words means an error 
	if (m_parsedInstruction.size() > 3) {
		string error = "@Location: " + to_string(a_loc) + " -> More than three field";
		Errors::RecordError(error);
	}

	// If it is InstructionType(0) (assembly language instruction)...returns the machine code equivalent 
	if (st == InstructionType(0)) {
		string asmCode = ""; // Assembly code 
		int loc = 0; // Location


		switch (m_parsedInstruction.size()) {
		case (1):
			m_OpCode = to_lower(m_parsedInstruction[0]);

			//If word has an operation code 
			if (opcode(m_OpCode) != -1) {
				if (m_OpCode == "halt")
					asmCode = "130000";
	
				//"halt" is the only opcode without an operand. 
				else {
					string error = "@Location:" + to_string(a_loc) + " -> Missing operand";
					Errors::RecordError(error);
					asmCode = to_string(opcode(m_OpCode)) + "????";
					pad(asmCode, 6);
				}
			}


			//Otherwise, report an error 
			else {
				string error = "@Location: " + to_string(a_loc) + " -> Bad Operation Command";
				Errors::RecordError(error);
				asmCode = "??????";
			}
			break;

		case(2):
			m_OpCode = m_parsedInstruction[0];
			m_Operand = m_parsedInstruction[1];
			if (opcode(m_OpCode) != -1) {
				asmCode = to_string(opcode(m_OpCode));
				pad(asmCode, 2);

				if (SymbolTable::LookupSymbol(m_Operand, loc)) {
					asmCode += pad(to_string(loc), 4);
				}
				else {
					string error = "@Location " + to_string(a_loc) + " -> Operand/Label undefined!";
					Errors::RecordError(error);
					asmCode += "????";
				}
			}
			else {
				string error = "@Location: " + to_string(a_loc) + " -> Bad Operation Command! ";
				Errors::RecordError(error);
				asmCode = "??????";
			}
			break;
		case(3):
			m_Label = m_parsedInstruction[0];
			m_OpCode = m_parsedInstruction[1];
			m_Operand = m_parsedInstruction[2];

			if (opcode(m_OpCode) != -1) {
				asmCode = to_string(opcode(m_OpCode));
				pad(asmCode, 2);

				if (SymbolTable::LookupSymbol(m_Operand, loc)) {
					asmCode += pad(to_string(loc), 4);
				}
				else {
					string error = "@Location: " + to_string(a_loc) + " -> Operand/Label undefined!";
					Errors::RecordError(error);
					asmCode += "????";
				}
			}
			else {
				string error = "@Location: " + to_string(a_loc) + " -> Bad Operation Command!";
				Errors::RecordError(error);
				asmCode = "??????";
			}
			break;
		default:
			asmCode = "??????";
			break;
		}
		cout << setw(12) << left << a_loc << setw(12) << left << asmCode << a_buff << endl;
		return pair<int, string>(a_loc, asmCode);
	}


	if (st == InstructionType(1) && m_parsedInstruction.size() >= 3 && (m_parsedInstruction[1] == "dc" || m_parsedInstruction[1] == "DC"))
		cout << setw(12) << left << a_loc << setw(12) << left << pad(m_parsedInstruction[2], 6) << a_buff << endl;
	//InstructionType(1), Assembler instruction
	else if (st == InstructionType(1))
		cout << setw(12) << left << a_loc << setw(12) << left << "" << a_buff << endl;
	//InstructionType(2), Comment or blank line, and InstructionType(3), end.
	else
		cout << setw(24) << " " << a_buff << endl;
	// End statement
	if (st == InstructionType(3))
		return pair<int, string>(0, "end");

	return pair<int, string>(0, "n/a");
} 


  /**/
  /*
	 Instruction::LocationNextInstruction(int a_loc)
	
	NAME
		Instruction::LocationNextInstruction - finds the location of the next line in the code
  
	SYNOPSIS
		int Instruction::LocationNextInstruction(int a_loc);
		a_loc: The location of the current instruction.
  
	DESCRIPTION
		Finds the location for the next line of the code.
	
	RETURNS
		Location in int form of the next instruction.
  
	AUTHOR
		Ashmin Bhandari
  
	DATE
		05-09-2018
  */
  /**/
int Instruction::LocationNextInstruction(int a_loc)
{
	// If the instruction type is a blank line, a comment or a end statement then do not increase the location
	if (m_type == InstructionType(2) || m_type == InstructionType(3))
		return a_loc;

	// Is the current statement the origin statement
	else if (m_type == InstructionType(1)) {
		stringstream ss(m_instruction);
		string a, b, c;
		ss >> a >> b >> c;

		//Returns the origin location
		if (a == "org" || a == "ORG")
			return stoi(b);
		//Set apart storage if it is a define storage statement
		else if (b == "ds" || b == "DS")
			return a_loc + stoi(c);
	}

	//Current location + 1 is returned to move forward onto the next instruction
	return a_loc + 1;
}


  /**/
  /*
	Instruction::to_lower(string &a_buff)
	
	NAME
		Instruction::to_lower - convert input into lowercase

	SYNOPSIS
		 string Instruction::to_lower(string &a_buff);
		 a_buff: the string to be changed to lowercase

	 DESCRIPTION
		Converts the input into lowercase and returns it. 
	
	RETURNS
		Lowercase version of the string inp7ut
  
	AUTHOR
		Ashmin Bhandari

	DATE
		05-09-2018
  */
  /**/

string Instruction::to_lower(string &a_buff)
{
	for (int i = 0; i < a_buff.size(); i++)
		a_buff[i] = tolower(a_buff[i]);
	return a_buff;
} 


  /**/
  /*
	Instruction::opcode(string &a_buff)
	
	NAME
		Instruction::opcode - Gets the opcode of an operation.
  
	SYNOPSIS
		int Instruction::opcode(string &a_buff);
		a_buff: the operation command
  
	DESCRIPTION
		Returns the opcode of the operation
  
	RETURNS
		An integer (1-13) which represent the opcode
		* -1 will be reutnred if operation is not defined. 
  
	AUTHOR
		Ashmin Bhandari
  
	DATE
		05-09-2018
  */
  /**/
int Instruction::opcode(string &a_buff)
{
	//Opcodes with their respective integers
	map<string, int> OpCode{
		{ "add", 1 },{ "sub", 2 },{ "mult", 3 },{ "div", 4 },{ "load", 5 },
		{ "store", 6 },{ "read", 7 },{ "write", 8 },{ "b", 9 },{ "bm", 10 },
		{ "bz", 11 },{ "bp", 12 },{ "halt", 13 }
	};

	if (OpCode[a_buff] <= 13 && OpCode[a_buff] >= 1)
		return OpCode[a_buff];

	return -1;
} 


  /**/
  /*
	Instruction::pad(string &a_buff, int a_size)
	
	NAME
		pad - pads the input string to a specific size. 
	SYNOPSIS
		string Instruction::pad(string &a_buff, int a_size);
  
		a_buff: String to be padded.
		a_size: The size to which the string will grow.
  
	DESCRIPTION
		Adds "0" 's until desired size is reached.
  
	RETURNS
		Padded version of the string passed in as argument
	
	AUTHOR
		Ashmin Bhandari
  
	DATE
		05-09-2018
  */
  /**/
string Instruction::pad(string &a_buff, int a_size)
{
	if (a_buff.size() == a_size) return a_buff;

	for (int i = a_buff.size(); i < a_size; i++)
		a_buff.insert(0, "0");
	return a_buff;
} 