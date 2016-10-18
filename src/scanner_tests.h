/*
 * Daniel Tran & Yuxiang Wang
 */

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "readInput.h"
#include "scanner.h"
#include <stdio.h>

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s ;
    void test_setup_code ( ) {
        s = new Scanner() ;
    }


    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You should test the regular expressions you use to make and match 
       regular expressions,and the functions used by makeRegex and 
       matchRegex using regex_tests.h.
       However, You will likely need to write several tests to 
       adequately test  the functions that are called from "scan".
       Once you are confident that the components used by "scan" 
       work properly, then you can run tests on the "scan" method itself.
    */

    // You should place tests for these other functions used by
    // scan below.


    /* Below is one of the tests for these components in the project
       solution created by your instructor.  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly ( ) {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) ;
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */


    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */

    
    /*
    intKwd, floatKwd,  stringKwd, matrixKwd,
    letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd,
    repeatKwd, printKwd, toKwd, trueKwd, falseKwd, boolKwd, whileKwd,
     */
     
    void test_terminal_whileKwd() {
		Token *key = s->scan("while i = 11");
		TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, whileKwd);
        TS_ASSERT_EQUALS (key->lexeme, "while");
    }
    
    void test_terminal_boolKwd() {
		Token *key = s->scan("bool interger float haha");
		TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, boolKwd);
        TS_ASSERT_EQUALS (key->lexeme, "bool");
    } 
     
    void test_terminal_trueKwd() {
		Token *key = s->scan("true false");
		TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, trueKwd);
        TS_ASSERT_EQUALS (key->lexeme, "true");
    }
    
    void test_terminal_falseKwd() {
		Token *key = s->scan("false true");
		TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, falseKwd);
        TS_ASSERT_EQUALS (key->lexeme, "false");
    } 
     
    void test_terminal_intKwd() {
    	Token *key = s->scan("int float string matrix");
        TS_ASSERT(key != NULL);
    	TS_ASSERT_EQUALS (key->terminal, intKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "int");
    }

    void test_terminal_floatKwd() {
    	Token *key = s->scan("float string matrix");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, floatKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "float");
    }

    void test_terminal_stringKwd() {
    	Token *key = s->scan("string matrix");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, stringKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "string");
    }

    void test_terminal_matrixKwd() {
    	Token *key = s->scan("matrix");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, matrixKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "matrix");
    }
    
    void test_terminal_letKwd() {
        Token *key = s->scan("let in end if then else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, letKwd);
        TS_ASSERT_EQUALS (key->lexeme, "let");
    }
    
    void test_terminal_inKwd() {
        Token *key = s->scan("in end if then else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, inKwd);
        TS_ASSERT_EQUALS (key->lexeme, "in");
    }
    
    void test_terminal_endKwd() {
        Token *key = s->scan("end if then else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, endKwd);
        TS_ASSERT_EQUALS (key->lexeme, "end");
    }
    
    void test_terminal_ifKwd() {
        Token *key = s->scan("if then else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, ifKwd);
        TS_ASSERT_EQUALS (key->lexeme, "if");
    }
    
    void test_terminal_thenKwd() {
    	Token *key = s->scan("then else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, thenKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "then");
    }

    void test_terminal_elseKwd() {
    	Token *key = s->scan("else");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, elseKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "else");
    }

    void test_terminal_repeatKwd() {
    	Token *key = s->scan("repeat print to");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, repeatKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "repeat");
    }

    void test_terminal_printKwd() {
    	Token *key = s->scan("print to");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, printKwd);
    	TS_ASSERT_EQUALS (key->lexeme, "print");
    }

    void test_terminal_toKwd() {
        Token *key = s->scan("to");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, toKwd);
        TS_ASSERT_EQUALS (key->lexeme, "to");
    }
    
    // intConst, floatConst, stringConst
    
    void test_terminal_intConst() {
        Token *key = s->scan("12344 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, intConst);
        TS_ASSERT_EQUALS (key->lexeme, "12344");
    }
    
    void test_terminal_floatConst() {
        Token *key = s->scan("123.44 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, floatConst);
        TS_ASSERT_EQUALS (key->lexeme, "123.44");
    }
    
    void test_terminal_stringConst() {
        Token *key = s->scan(" \"this is a string \"");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, stringConst);
        TS_ASSERT_EQUALS (key->lexeme, "\"this is a string \"");
    }
    
    // variableName
    
    void test_terminal_variableName() {
        Token *key = s->scan("firstVar");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, variableName);
        TS_ASSERT_EQUALS (key->lexeme, "firstVar");
    }
        
    /*
     leftParen, rightParen,
     leftCurly, rightCurly,
     leftSquare, rightSquare,
     semiColon, colon,
     */
    
    void test_terminal_leftParen() {
        Token *key = s->scan("( 123.44 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, leftParen);
        TS_ASSERT_EQUALS (key->lexeme, "(");
    }
    
    void test_terminal_rightParen() {
        Token *key = s->scan(" ) thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, rightParen);
        TS_ASSERT_EQUALS (key->lexeme, ")");
    }
    
    void test_terminal_leftCurly() {
        Token *key = s->scan("{ thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, leftCurly);
        TS_ASSERT_EQUALS (key->lexeme, "{");
    }
    
    void test_terminal_rightCurly() {
        Token *key = s->scan(" } 12344 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, rightCurly);
        TS_ASSERT_EQUALS (key->lexeme, "}");
    }
    
    void test_terminal_leftSquare() {
        Token *key = s->scan(" [ 12344 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, leftSquare);
        TS_ASSERT_EQUALS (key->lexeme, "[");
    }
    
    void test_terminal_rightSquare() {
        Token *key = s->scan(" ] 123.44 2.22 ");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, rightSquare);
        TS_ASSERT_EQUALS (key->lexeme, "]");
    }
    
    void test_terminal_colon() {
        Token *key = s->scan(" : 123.44 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, colon);
        TS_ASSERT_EQUALS (key->lexeme, ":");
    }
    
    void test_terminal_semiColon() {
        Token *key = s->scan("; 123.44 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, semiColon);
        TS_ASSERT_EQUALS (key->lexeme, ";");
    }
    
    /*
     assign,
     plusSign, star, dash, forwardSlash,
     lessThan, lessThanEqual, greaterThan, greaterThanEqual,
     equalsEquals, notEquals,
     andOp, orOp, notOp,
     */
    
    
    void test_terminal_assign() {
        Token *key = s->scan(" = thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, assign);
        TS_ASSERT_EQUALS (key->lexeme, "=");
    }
    
    void test_terminal_plusSign() {
        Token *key = s->scan(" + 12344  222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, plusSign);
        TS_ASSERT_EQUALS (key->lexeme, "+");
    }
    
    void test_terminal_star() {
        Token *key = s->scan("* 123.44 * 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, star);
        TS_ASSERT_EQUALS (key->lexeme, "*");
    }
    
    void test_terminal_dash() {
        Token *key = s->scan(" - thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, dash);
        TS_ASSERT_EQUALS (key->lexeme, "-");
    }
    
    void test_terminal_forwardSlash() {
        Token *key = s->scan("/ 12344 + 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, forwardSlash);
        TS_ASSERT_EQUALS (key->lexeme, "/");
    }
    
    void test_terminal_lessThan() {
        Token *key = s->scan("< 123.44 * 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, lessThan);
        TS_ASSERT_EQUALS (key->lexeme, "<");
    }
    
    void test_terminal_lessThanEqual() {
        Token *key = s->scan(" <= thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, lessThanEqual);
        TS_ASSERT_EQUALS (key->lexeme, "<=");
    }
    
    void test_terminal_greaterThan() {
        Token *key = s->scan("> 12344 + 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, greaterThan);
        TS_ASSERT_EQUALS (key->lexeme, ">");
    }
    
    void test_terminal_greaterThanEqual() {
        Token *key = s->scan(">= 123.44 * 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, greaterThanEqual);
        TS_ASSERT_EQUALS (key->lexeme, ">=");
    }
    
    void test_terminal_equalsEquals() {
        Token *key = s->scan(" == thisisastring");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, equalsEquals);
        TS_ASSERT_EQUALS (key->lexeme, "==");
    }
    
    void test_terminal_notEquals() {
        Token *key = s->scan("!= 12344 222");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, notEquals);
        TS_ASSERT_EQUALS (key->lexeme, "!=");
    }
    
    void test_terminal_andOp() {
        Token *key = s->scan("&& 123.44 && 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, andOp);
        TS_ASSERT_EQUALS (key->lexeme, "&&");
    }
    
    void test_terminal_orOp() {
        Token *key = s->scan("|| 123.44 || 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, orOp);
        TS_ASSERT_EQUALS (key->lexeme, "||");
    }
    
    void test_terminal_notOp() {
        Token *key = s->scan("! 123.44 ! 2.22");
        TS_ASSERT(key != NULL);
        TS_ASSERT_EQUALS (key->terminal, notOp);
        TS_ASSERT_EQUALS (key->lexeme, "!");
    }
    
    
    // endOfFile, lexicalError
    
    void test_terminal_endOfFile ( ) {
        Token *key = s->scan ("  ") ;
        TS_ASSERT (key != NULL) ;
        TS_ASSERT_EQUALS (key->terminal, endOfFile) ;
        TS_ASSERT (key->next == NULL) ;
    }

    void test_terminal_lexicalErrors ( ) {
        Token *tks = s->scan ("$ & 1") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "$");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "&");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, intConst) ;
        TS_ASSERT_EQUALS (tks->lexeme, "1");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors (Token *tks) {
        Token *currentToken = tks ;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                printf("priblem: %s\n",currentToken->lexeme.c_str());
				return false ;
            }
            else {
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
    */
    void scanFileNoLexicalErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT (noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
            printf("%i: %i should be %i\n",termIndex,currentToken->terminal , ts[termIndex]);
			fflush(stdout);
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }


    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty ( ) {
        Token *tks = s->scan ("  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    void test_scan_empty_comment ( ) {
        Token *tks = s->scan (" /* a comment */ ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
   void test_scan_lexicalErrors ( ) {
        Token *tks = s->scan ("$&1  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "$");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "&");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, intConst) ;
        TS_ASSERT_EQUALS (tks->lexeme, "1");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }


    // A test for scanning numbers and a variable.
    void test_scan_nums_vars ( ) {
        Token *tks = s->scan (" 123 x 12.34 ") ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
        TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
    }



    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexemes
       are correct.
     */
    
    void test_scan_bad_syntax_good_tokens ( ) {
        const char *filename = "../samples/bad_syntax_good_tokens.dsl" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
            intConst, intConst, intConst, intConst, 

            stringConst, stringConst, stringConst,

            floatConst, floatConst, floatConst,

                   matrixKwd,



            semiColon, colon,
            leftCurly, leftParen, rightCurly, rightParen,

            plusSign, star, dash, forwardSlash, 

            equalsEquals, lessThanEqual, 
            greaterThanEqual, notEquals, 
            assign,

            variableName, variableName, variableName, variableName, 
            variableName, variableName, variableName,


            intKwd, floatKwd,  stringKwd, 

            endOfFile
       } ;
        int count = 38; 
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }

    void test_scan_sample_forestLoss ( ) {
        scanFileNoLexicalErrors ("../samples/forest_loss_v2.dsl") ;
    }

      

} ;
