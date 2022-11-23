#include "scanner.h"
#include <iostream>

using namespace std;

#ifndef __PARSER_H__
#define __PARSER_H__


	void syntax_error1(string lexeme , tokenType savedT);
	void syntax_error2(string expec, string lexeme );
	tokenType next_token();
	bool match(tokenType expected);
	void tense();
	void be();
	void verb();
	void noun();
	void after_verb();
	void after_destination();
	void after_object();
	void after_noun();
	void after_subject();
	void sentenceS();

#endif
