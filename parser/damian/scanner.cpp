#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scanner.h"
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 27 
//=====================================================

// --------- Two DFAs ---------------------------------

// vowel function to reduce the amount of if statement syntax
// it will loop through the character arrays and determine if it is a 
// vowel
bool vowel (char s1)
{
	char vowelChar[] = {'A','a','E','e','I','i','O','o','U','u','n'};
	for (unsigned int i = 0; i <= strlen(vowelChar); i++)
	{
		if (s1 == vowelChar[i]) 
		{
			return true;
		}
	}
	return false;
}



// singleConsonant function loops through the character array and determine
// if it is a single consonant character.
bool singleConsonant(char s1)
{
	char sconsonant[] = {'d','j','w','y','z'};

	for (unsigned int i = 0; i <= strlen(sconsonant); i++)
        {
                 if (s1 == sconsonant[i])
                 {
                         return true;
                  }
         }
         return false;
}



// pairConsonant function loops through the character array and determines
// whether it is a consonant.
bool pairConsonant(char s1)
{
	char psconsonant[] = {'b','m','n','k','h','p','r','g'};

	for (unsigned int i = 0; i <= strlen(psconsonant); i++)
         {
                  if (s1 == psconsonant[i])
                  {
                          return true;
                   }
          }
          return false;
}


// WORD DFA 
// Done by: Ezer, Barath, and, Damian
// RE:   **
bool word(string s)
{

  string state = "q0";
  int charpos = 0;
//   replace the following todo the word dfa  **
  while (s[charpos] != '\0') 
  {
      // Would go over each stage
      // Good
      if (state == "q0" && vowel(s[charpos]))
      {state = "q0q1";}
      else if (state == "q0" && (s[charpos] == 'c' ) )
      {state = "qc";}
      else if (state == "q0" && ( s[charpos] == 's' ) )
      {state = "qs";}
      else if (state == "q0" && ( s[charpos] == 't' ) )
      {state = "qt";}
      else if (((state == "q0") &&  pairConsonant(s[charpos]))  )
      {state = "qy";}
      else if (((state == "q0") && singleConsonant(s[charpos])) )
      {state = "qsa";}
      else if ((state == "q1") && ( s[charpos] == 'n' ) )
      {state = "q0";}
      else if ((state == "qc") && (s[charpos] == 'h' ) )
      {state = "qsa";}
      else if (((state == "q0q1") && vowel(s[charpos])))
      {state = "q0q1";}
      // Good
      else if ((state == "q0q1") && ( s[charpos] == 'c' ) )      
      {state = "qc";}	
      else if ((state == "q0q1") && ( s[charpos] == 's' ) ) 
      {state = "qs";}
      else if ((state == "q0q1") && ( s[charpos] == 't' ) )
      {state = "qt";}
      else if (((state == "q0q1") && pairConsonant(s[charpos])) )
      {state = "qy";}
      else if ((state == "q0q1") && ( s[charpos] == 'n' ) )
      {state = "q0qy"; }
      else if (((state == "q0q1") && singleConsonant(s[charpos])) )
      {state = "qsa";}
      else if (((state == "q0q1") && vowel(s[charpos]))  )
      {state = "q0q1"; }
      // Good
      else if (((state == "qs") &&  vowel(s[charpos]))  )
      {state = "q0q1";}
      else if ((state == "qs") && ( s[charpos] == 'h' ) )
      {state = "qsa";}
      else if (((state == "qt") && vowel(s[charpos])) )
      {state = "q0q1";}
      else if ((state == "qt") &&  ( s[charpos] == 's' ) )
      {state = "qsa";}
      else if (((state == "qy") && vowel(s[charpos])) )
      {state = "q0q1";}
      else if ((state == "qy") && ( s[charpos] == 'y' ) )
      {state = "qsa";}
      else if (((state == "qsa") && vowel(s[charpos])) )
      {state = "q0q1";}
      // Good
      else if ((state == "q0qy") && ( s[charpos] == 'c'  ))
      {state = "qc";}
      else if ((state == "q0qy")  && ( s[charpos] == 's'  ) )
      {state = "qs";}
      else if ((state == "q0qy") &&  ( s[charpos] == 't' ))
      {state = "qt";}
      else if (((state == "q0qy") && pairConsonant(s[charpos])) )
      {state = "qy";}
      else if ((state == "q0qy") && (s[charpos] == 'n'  ))
      {state = "qy";}
      else if (((state == "q0qy") && singleConsonant(s[charpos])) )
      {state = "qsa";}
      else if (((state == "q0qy") && vowel(s[charpos])) )
      {state = "q0q1";}
      charpos++;
 }//end of while
    // whether if is the final stage
    if ( state == "q0q1" or state == "q0qy")
    {
	    return true;
    } else {
	    return false;
    }


} // end of function


// PERIOD DFA 
// Done by: Damian
bool period(string s)
{ 
  int state=0;
  int charpos = 0;
  while (s[charpos] != '\0')
  {

      if(state == 0 && s[charpos] == '.')
        {
          state = 1;
        }
      charpos++;
  }

  if (state == 1)
  { return true;}
  else 
  {return false;}
} // end of function

// ------ Three  Tables -------------------------------------
// TABLES Done by: Ezer & Damian

//enum tokenType {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, WORD1, WORD2, PERIOD, ERROR, EOFM };
void scanner(tokenType&, string&); // to be called by main
ifstream fin;  // global stream for reading from the input file


struct tokenList
{
        string WORD;
        tokenType TYPE;
};

vector <tokenList> tokenNameList;

// PURPOSE: To assigned the correct word for the tokenType
// PARAMETERS: index number and tokenType
void init()
{
	tokenType the_type;
	tokenList r;
	string reservedWord[18] = {"masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o","wa", "ni","watashi", "anata", "kare","kanojo","sore","mata","soshite","shikashi","dakara"};
	for (int i = 0; i < 18; i++)
	{
			switch(i)
			{
				case 0:
					//cout << "passing by verb" << endl;
					the_type = VERB;
					r.WORD = reservedWord[i];
                        		r.TYPE = the_type;
                        		tokenNameList.push_back(r);
					break;
				case 1:
					//cout << "passing by verbneg" << endl;
					the_type = VERBNEG;
					r.WORD = reservedWord[i];
                        		r.TYPE = the_type;
                        		tokenNameList.push_back(r);
					break;
				case 2:
					//cout << "passing by verbpast" << endl;
					the_type = VERBPAST;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 3:
					//cout << "passing by verbpastneg" << endl;
					the_type = VERBPASTNEG;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 4:
					//cout << "passing by is" << endl;
					the_type = IS;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 5:
					//cout << "passing by was" << endl;
					the_type = WAS;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 6:
					//cout << "passing by object" << endl;
					the_type = OBJECT;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 7:
					//cout << "passing by subject" << endl;
					the_type = SUBJECT;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 8:
					//cout << "passing by destination" << endl;
					the_type = DESTINATION;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 9:
					//cout << "passing by pronoun" << endl;
					the_type = PRONOUN;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 10:
					//cout << "passing by pronoun" << endl;
					the_type = PRONOUN;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 11:
					//cout << "passing by pronoun" << endl;
					the_type = PRONOUN;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 12:
					//cout << "passing by pronoun" << endl;
					the_type = PRONOUN;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 13:
					//cout << "passing by pronoun" << endl;
					the_type = PRONOUN;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 14:
					//cout << "passing by connector" << endl;
					the_type = CONNECTOR;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 15:
					//cout << "passing by connector" << endl;
					the_type = CONNECTOR;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 16:
					//cout << "passing by connector" << endl;
					the_type = CONNECTOR;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);
					break;
				case 17:
					//cout << "passing by connector" << endl;
					the_type = CONNECTOR;
					r.WORD = reservedWord[i];
                                        r.TYPE = the_type;
                                        tokenNameList.push_back(r);	
					break;
			}
	}
}
// PURPOSE: reservedWords would loop over the tokenName and identify the index
// number and input into the printReservedWord
// PARAMETER: main word string, vector where all the reserved words are located,
// and tokenType enum whether is Word, Period, or reserved word.
/*bool reservedWords(string& word,vector<string> tokenName, tokenType& the_type)
{
	for (int i = 0; i < tokenName.size(); i++)
	{
		if (tokenName[i] == word)
		{
			printReservedWord(i, the_type); 
			return true;
		} // end of if statement

	} // end of for loop
	return false;
} // end of reservedWords function
*/

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Damian
void scanner(tokenType& the_type, string& w) {

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.


  4. Return the token type & string  (pass by reference)
  */

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  // initialize the vector for the reserved words
/*  std::vector<std::string> tokenName;
  // upload the reserved wors into the vector
  tokenName.push_back("masu");
  tokenName.push_back("masen");
  tokenName.push_back("mashita");
  tokenName.push_back("masendeshita");
  tokenName.push_back("desu");
  tokenName.push_back("deshita");
  tokenName.push_back("o");
  tokenName.push_back("wa");
  tokenName.push_back("ni");
  tokenName.push_back("watashi");
  tokenName.push_back("anata");
  tokenName.push_back("kare");
  tokenName.push_back("kanojo");
  tokenName.push_back("sore");
  tokenName.push_back("mata");
  tokenName.push_back("soshite");
  tokenName.push_back("shikashi");
  tokenName.push_back("dakara");
*/
  cout << endl;
  cout << ".....Scanner was called..." << endl;
  fin >> w; // grab next word from text file.
  cout << ">>>>>Word is:" << w << endl;
  init();
    // If the word dfa is true would go over the
    // reservedWords function, word1, word2, or eofm, but if
    // none of the are true then return false and does not 
    // exitis in languages.
    if (w == "eofm")
    { cout << "Reached the end of the file…." << endl; the_type = EOFM;}   


    if (word(w))
    {
       if (w.back() == 'I' || w.back() == 'E')
	{
		cout << "passed: " << w.back() << endl;
		cout << "passing by word2" << endl;
		the_type = WORD2;
	} else {
		cout << "passed: " << w.back() << endl;
		cout << "passing by word1" << endl;
		the_type = WORD1;
	}

	for (unsigned int i = 0; i < tokenNameList.size(); i++)
	{
		tokenList r = tokenNameList.at(i);
		if (r.WORD == w)
		{
			the_type = r.TYPE;
			break;
		}
	}
    } else if (period(w))
	{
		cout << "passing by period" << endl;
		the_type = PERIOD;
	} else {
		cout << "Lexical Error: This string is not in this language" << endl;
		the_type = ERROR;
	}
     
/*    if (word(w))
    {       
	   cout << "word: " << w << " character: " <<  w.back() << endl;
		// word reserved
	    if (reservedWords(w, tokenName, the_type))
	    {
	    	cout << "passing by reserved words" << endl;
	    } // if reaches the end of the file
	    else if (w.back() == 'I' || w.back() == 'E'){
		cout << "passed: " << w.back() << endl;
		cout << "passing by word2" << endl;
		the_type = WORD2;	
	    } else if (w.back() == 'a' || w.back() == 'e' || w.back() == 'i' || w.back() == 'o' || w.back() == 'u' || w.back() == 'n' ) {
	    	// if the word belongs to word1
		cout << "passed: " << w.back() << endl;
            	cout << "passing by word1" << endl;
            	the_type = WORD1;
            }
    }  else if (period(w)) {
            // if there is no word then is a period
	    cout << "passing by period" << endl;
	    the_type = PERIOD;
    	   
    } else {
	    // does not belong to the japanese language.
	    cout << "Lexical Error: This string is not in this language" << endl;
	    the_type = ERROR;

    } // end of if statement
  */ 
}//the end of scanner

/*
// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
  	
  string filename;
  
  cout << "Enter the input file name: ";
  cin >> filename;
 
  fin.open(filename.c_str());
  
  tokenType thetype;
  string theword;

  string tokenName[16] = {"VERB","VERBNEG","VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "WORD1", "WORD2", "PERIOD", "ERROR", "EOFM"};
 

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
       
       if (theword == "eofm") break;  // stop now
	cout << ">>index: " << thetype << endl;
	cout << ">>>Type is:" << tokenName[thetype] << endl;
        cout << ">>>Word is:" << theword << endl;	
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end
*/
