#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "scanner.h"
#include "mparser.h"



//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
 // call the reserved words from the scanner
 // create a void init() in the parser code or scanner code
  init();
  // read the file
  ifstream fin;
  string filename;
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

  //** calls the <story> to start parsing
  //** closes the input file 
  cout << "End of file is encountered." << endl;
  fin.close();
  // end of the file

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
