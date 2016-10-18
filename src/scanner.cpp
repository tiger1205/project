/* 
 * Daniel Tran & Yuxiang Wang
 */

#include "scanner.h"
#include <iostream>
#include <string>
#include <cstring>
#include "regex.h"
using namespace std;

regex_t* regexKeys[44];

void makeRegexArray() {
    for (int i = 0 ; i < 44; i++) {
		regexKeys[i] = makeRegex ("/");
    }
    
    // keywords
	regexKeys[intKwd] = makeRegex("^int");
	regexKeys[floatKwd] = makeRegex("^float");
	regexKeys[stringKwd] = makeRegex("^string");
	regexKeys[matrixKwd] = makeRegex("^matrix");
    
    // new added keywords
    regexKeys[whileKwd] = makeRegex("^while");
	regexKeys[boolKwd] = makeRegex("^bool");
	regexKeys[trueKwd] = makeRegex("^true");
	regexKeys[falseKwd] = makeRegex("^false");
    
	regexKeys[letKwd] = makeRegex("^let");
	regexKeys[inKwd] = makeRegex("^in");
	regexKeys[endKwd] = makeRegex("^end");
	regexKeys[ifKwd] = makeRegex("^if");
	regexKeys[thenKwd] = makeRegex("^then");
	regexKeys[elseKwd] = makeRegex("^else");
    
	regexKeys[repeatKwd] = makeRegex("^repeat");
	regexKeys[printKwd] = makeRegex("^print");
	regexKeys[toKwd] = makeRegex("^to");
    
    // constants
    regexKeys[intConst]  = makeRegex("^[0-9]+");
	// regexKeys[floatConst] = makeRegex("^[+-]?[0-9]*\\.[0-9]+");
    regexKeys[floatConst] = makeRegex("^[0-9]+\\.[0-9]+");
	regexKeys[stringConst] = makeRegex ("^\"[^\"]*\"");
    // regexKeys[stringConst] = makeRegex ("^\"[a-zA-Z0-9. ()_/]*\"");
    
    // names
	regexKeys[variableName] = makeRegex("^[a-zA-Z_]+[a-zA-Z_0-9]*");
    
    // punctuations
	regexKeys[leftParen] = makeRegex("^[(]");
	regexKeys[rightParen] = makeRegex("^\\)");
	regexKeys[leftCurly] = makeRegex("^[{]");
	regexKeys[rightCurly] = makeRegex("^[\\}]");
	regexKeys[leftSquare] = makeRegex("^\\[");
	regexKeys[rightSquare] = makeRegex("^\\]");
	regexKeys[semiColon] = makeRegex("^;");
	regexKeys[colon] = makeRegex("^:");
    
    // operators
	regexKeys[assign] = makeRegex("^=");
	regexKeys[plusSign] = makeRegex("^\\+");
	regexKeys[star] = makeRegex("^\\*");
	regexKeys[dash] = makeRegex("^-");
	regexKeys[forwardSlash] = makeRegex("^/") ;
	regexKeys[lessThan] = makeRegex("^<") ;
	regexKeys[lessThanEqual] = makeRegex("^<=") ;
	regexKeys[greaterThan] = makeRegex("^>") ;
	regexKeys[greaterThanEqual] = makeRegex("^>=") ;
	regexKeys[equalsEquals] = makeRegex("^==") ;
	regexKeys[notEquals] = makeRegex("^!=") ;
	regexKeys[andOp] = makeRegex("^&&");
	regexKeys[orOp] = makeRegex("^\\|\\|");
	regexKeys[notOp] = makeRegex("^!");
    
    // special terminal types
	regexKeys[endOfFile] = makeRegex("^\\z"); // "^$"

}

// from wordCount.cpp
int consumeWhiteSpaceAndComments (regex_t *whiteSpace,
                                  regex_t *blockComment,
                                  regex_t *lineComment,
                                  const char *text) {
    int numMatchedChars = 0 ;
    int totalNumMatchedChars = 0 ;
    int stillConsumingWhiteSpace ;
    
    do {
        stillConsumingWhiteSpace = 0 ;  // exit loop if not reset by a match
        
        // Try to match white space
        numMatchedChars = matchRegex (whiteSpace, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
        
        // Try to match block comments
        numMatchedChars = matchRegex (blockComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
        
        // Try to match single-line comments
        numMatchedChars = matchRegex (lineComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
    }
    while ( stillConsumingWhiteSpace ) ;
    
    return totalNumMatchedChars ;
}

Token *Scanner::scan(const char *text) {

    regex_t* whiteSpace ;
    whiteSpace = makeRegex ("^[\n\t\r ]+") ;

    regex_t *blockComment ;
    blockComment = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/") ;

    regex_t *lineComment ;
    lineComment = makeRegex ("^//[^\n]*\n") ;
    
    Token *head = new Token();
    Token *tail = 0;
	
    int numMatchedChars = 0;
    
	numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockComment, lineComment, text);
    
	text = text + numMatchedChars;
    
    while(text[0] != '\0') {
        int maxNumChars = 0;
        tokenType matchedTerminal = lexicalError; // set the first token to be the type lexicalError
        
        // match matchedTerminal to an appropriate token type
        for (int i = 0; i < 43; i++) {
            numMatchedChars = matchRegex(regexKeys[i],text);
            
            if (maxNumChars < numMatchedChars) {
                maxNumChars = numMatchedChars;
                matchedTerminal = (tokenType)i;
            }
            else if (maxNumChars == numMatchedChars) {
                if (matchedTerminal == variableName) matchedTerminal = (tokenType)i;
            }
        }
        
        if (matchedTerminal == lexicalError && maxNumChars == 0) {
            maxNumChars = 1;
        }
        
        // get the matched lexeme
        string matchedLexeme(text,maxNumChars);
        
        // first match case - create a head token
        if (tail == NULL) {
            tail = new Token(matchedTerminal, matchedLexeme, maxNumChars);
            head = tail;
        }
        else {
            Token *matchedToken = new Token(matchedTerminal, matchedLexeme, maxNumChars);
            tail->next = matchedToken;
            tail = tail->next;
        }

        text = text + maxNumChars;
        numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockComment, lineComment, text);
        text = text + numMatchedChars;
    }

    // put the token of type endOfFile at the end of the link list
    char* endLexeme = "EOF";
    if (tail == NULL) {
        tail = new Token(endOfFile, endLexeme, 3);
        head = tail;
    }
    else {
        Token *endToken = new Token(endOfFile, endLexeme, 3);
        tail->next = endToken;
        tail = endToken;
    }
    
    return head;
}

    
    
    
    
    
    
    
    
    
    
    
    
