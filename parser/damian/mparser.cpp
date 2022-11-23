#include<iostream>
#include<fstream>
#include<string>
#include "scanner.h"

using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  




string tokenName[16] = {"VERB","VERBNEG","VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "WORD1", "WORD2\
   ", "PERIOD", "ERROR", "EOFM"};     

// token types from the scanner
//enum token_type {};
//enum tokenType {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, WORD1, WORD2, PERIOD, ERROR, EOFM };
// global buffer for the token the 
// scanner returned
tokenType saved_token;
string saved_lexeme;
// global flag indicating whether
// we have saved a token to eat up or not
bool token_available;


void syntax_error1(string lexeme , tokenType savedT)
{

  cout << "SYNTAX ERROR: expected " << tokenName[savedT] << " but found " << lexeme << "!" << endl ;
  cout << "Terminate the Program" << endl;
  exit(1);

}
// Type of error: ** swwitch default
// // Done by: ** 
void syntax_error2(string expec, string lexeme )
{
    cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << expec << "!" ;
    cout << "Terminate the Program" << endl;
    exit(1);
}





// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks ahead to see what token comes next from the scanner.
// HOW: checks first to see if the token_available flag is false.
// if so, saved_token gets scanner() result.
// and the flag is set true.
// A token is grabbed but is not eaten up.
// Returns the save_token
// Done by: **

///--------------------------Barath's Function----------------------------
// -----------------------Change 2-----------------------------------
tokenType next_token()
{       
  string saved_lexeme;
  if (!token_available)  // if there is no saved token yet
    {       
      scanner(saved_token, saved_lexeme); // call scanner to grab a new token
      cout << "Scanner called using word: " << saved_lexeme << endl;
      token_available = true;
                
      if (saved_token == ERROR)
	{       
	  syntax_error1(saved_lexeme, saved_token);
	}
    }
  return saved_token; // return the saved token
}

//-----------------------------------------------------------------------------







// Purpose: Checks and eats up the expected token
// HOW: check to see if expected is different from next_token()
// and if so, generates a syntax error and handles the error
// else token_available become false (eat up) and return true.
// Done by: **
bool match(tokenType expected) 
{

	if (next_token() != expected) // mismatch has occurred with the next token
	{
		// calls a syntax error function here to generate 
		// a syntax error message here and do recovery
		syntax_error1(saved_lexeme, expected);
	}
	else // match has occurred
	{
		cout << "Matched " << tokenName[expected] << " <<<<" << endl;
		token_available = false; // eat up the token
		return true;		 // say there was a match
	}

	return 0;
}




// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: **
// VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
	cout << "Processing (tense)" << endl;
	switch(next_token())
	{
		case VERBPAST:
			match(VERBPAST);
			break;
		case VERBPASTNEG:
			match(VERBPASTNEG);
			break;
		case VERB:
			match(VERB);
			break;
		case VERBNEG:
			match(VERBNEG);
			break;
		default:
			syntax_error2("tense", saved_lexeme);
			break;

	}

}

// IS | WAS
void be()
{
	cout << "Processing (be)" << endl;
	switch(next_token())
	{
		case IS:
			match(IS);
			break;
		case WAS:
			match(WAS);
			break;
		default:
			syntax_error2("be", saved_lexeme);
			break;
	}
}

// WORD2
void verb()
{
	cout << "Processing (verb)" << endl;
	match(WORD2);	
}

// WORD1 | PRONOUN
void noun()
{
	cout << "Processing (noun)" << endl;
	switch(next_token())
	{
		case WORD1:
			match(WORD1);
			break;
		case PRONOUN:
			match(PRONOUN);
			break;
		default:
			syntax_error2("noun", saved_lexeme);
			break;

	}

}

// <tense> PERIOD
void after_verb()
{
	cout << "Processing (after_verb)" << endl;
	tense();
	//gen("TENSE");
	match(PERIOD);
}

// <verb> <after verb> PERIOD
void after_destination()
{

	cout << "Processing (after_destination)" << endl;
	verb();
	//getEword();
	//gen("ACTION");
	after_verb();
}

// <verb> <after verb> | <noun> DESTINATION <after destination>
void after_object()
{
	cout << "Processing (after_object)" << endl;
	switch (next_token())
	{
		case WORD2:
			match(WORD2);
			// getEword();
			// gen("ACTION");
			after_verb();
			break;
		case WORD1:
			match(WORD1);
			// getEword();
			match(DESTINATION);
			// gen("TO");
			after_destination();
			break;
		case PRONOUN:
			match(PRONOUN);
			// getEword();
			match(DESTINATION);
			// gen("TO");
			after_destination();
			break;
		default:
			syntax_error2("after_object", saved_lexeme);
			break;
	}
}


// <be> PERIOD | DESTINATION <after destination> | OBJECT <after object>
void after_noun()
{
	cout << "Processing (after_noun) " << endl;
	switch(next_token())
	{
		case IS:
			match(IS);
			// gen("DESCRIPTION");
			// gen("TENSE");
			match(PERIOD);
			break;
		case WAS:
			match(WAS);
			// gen("DESCRIPTION");
			// gen("TENSE");
			match(PERIOD);
			break;
		case DESTINATION:
			match(DESTINATION);
			// gen("TO");
			after_destination();
			break;
		case OBJECT:
			match(OBJECT);
			// gen("OBJECT");
			after_object();
			break;
		default:
			syntax_error2("after_noun", saved_lexeme);
			break;
	}
}

// <verb> <tense> PERIOD | <noun> <after noun>
void after_subject()
{
	cout << "Processing (after_subject)" << endl;
	switch (next_token())
	{
		case WORD2:
			match(WORD2);
			// getEword();
			// gen("ACTION");
			tense();
			//gen("TENSE");	
			match(PERIOD);
			break;
		case WORD1:
			match(WORD1);
			// getEword();
			after_noun();
			break;
		case PRONOUN:
			match(PRONOUN);
			// getEword();
			after_noun();
			break;
		default:
			syntax_error2("after_subject", saved_lexeme);
			break;
	}
}

// [Connector] <noun> SUBJECT <after subject>
void sentenceS()
{

	cout << "Processing (S)" << endl;
	if (next_token() == CONNECTOR)
	{
		match(CONNECTOR);
		// getEword();
		// gen("CONNECTOR");
	}

	noun();
	// getEWord();
	match(SUBJECT);
	// gen("ACTOR");
	after_subject();
}

/*
string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
 // call the reserved words from the scanner
 // create a void init() in the parser code or scanner code
  init();
  // read the file
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  
  int countSentences = 0;
  while (true)
  {
	cout << "------------------------------------" << endl;
	cout << "       Reading Sentence: " << countSentences << endl;
	cout << "------------------------------------" << endl;
	sentenceS();
	// count the number of sentences
	countSentences++;
  }

  // calls the <story> to start parsing
  // closes the input file 
  cout << "End of file is encountered." << endl;
  fin.close();
  // end of the file

}// end
// require no other input files!
// syntax error EC requires producing errors.txt of error messages
// tracing On/Off EC requires sending a flag to trace message output functions
*/
