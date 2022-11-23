#include <iostream>
#include <string>

using namespace std;

#ifndef __SCANNER_H__
#define __SCANNER_H__
	enum tokenType {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, WORD1, WORD2, PERIOD, ERROR, EOFM };



	bool vowel (char s1);
	bool singleConsonant(char s1);
	bool pairConsonant(char s1);
	bool word(string s); //Word DFA
	bool period(string s); //Period DFA
	void init(); //Initalizes the reserved words list.
	void scanner(tokenType &a, string &s); //Scanner function that calls the DFA(s).

#endif
