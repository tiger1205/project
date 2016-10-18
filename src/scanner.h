/*
 * Daniel Tran & Yuxiang Wang
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string>
#include "regex.h"
#include <stdlib.h>
class Token ;

/* This enumerated type is used to keep track of what kind of
   construct was matched. 
 */

enum tokenEnumType { 

	intKwd, floatKwd,  stringKwd, matrixKwd,
	letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd,
	repeatKwd, printKwd, toKwd, whileKwd, boolKwd, trueKwd, falseKwd,

	// Constants
	intConst, floatConst, stringConst, 

	// Names
	variableName ,

	// Punctuation
	leftParen, rightParen, 
	leftCurly, rightCurly, 
	leftSquare, rightSquare,

	semiColon, colon,

	//Operators
	assign, 
	plusSign, star, dash, forwardSlash,
	lessThan, lessThanEqual, greaterThan, greaterThanEqual,
	equalsEquals, notEquals,
	andOp, orOp, notOp,

	// Special terminal types
	endOfFile ,
	lexicalError
} ;
typedef enum tokenEnumType tokenType ;

// Below you need to write your class definitions for Token and Scanner.

void makeRegexArray();

class Token {
	public: tokenType terminal;
		std::string lexeme;
		Token *next;

		Token (){
		}

		Token (tokenType token, std::string str, int num) {
			terminal = token;
			lexeme = str.substr(0,num);
			next = NULL;
		}
		
		Token (std::string str, tokenType token, int num) {
			lexeme = str.substr(0,num);
			terminal = token;
			next = NULL;
		}
		/*
		Token (std::string str, tokenType token, Token *nextp){
			lexeme = str;
			terminal = token;
			next = nextp;
			}
		*/
};

class Scanner {
    public:
        Scanner() {
            makeRegexArray();
        };
    
        Token * scan(const char *text) ;
};


int consumeWhiteSpaceAndComments (regex_t *whiteSpace,
                                  regex_t *blockComment,
				  regex_t *lineComment,
                                  const char *text);


#endif /* SCANNER_H */
