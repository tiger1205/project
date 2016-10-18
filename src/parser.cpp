/* A recursive descent parser with operator precedence.

   Author: Eric Van Wyk
   Modified: Robert Edge 
   Modified: Kevin Thomsen
   Modified: Dan Challou       

   This algorithm is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work is based on an
   algorithm described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Languages.

   Douglas Crockford's chapter is available at 
    http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at 
    http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.

   Last modified: Oct 19, 2015.

*/

#include "parser.h"
#include "scanner.h"
#include "extToken.h"
#include <stdio.h>
#include <assert.h>

using namespace std ;

/*! Destructor for parser.*/
Parser::~Parser() {
    if (s) delete s ;

    ExtToken *extTokenToDelete ;
    currToken = tokens ;
    while (currToken) {
        extTokenToDelete = currToken ;
        currToken = currToken->next ;
        delete extTokenToDelete ;
    }

    Token *tokenToDelete ;
    Token *currScannerToken = stokens ;
    while (currScannerToken) {
        tokenToDelete = currScannerToken ;
        currScannerToken = currScannerToken->next ;
        delete tokenToDelete ;
    }
}

/*! Constructor for parser*/
Parser::Parser ( ) { 
    currToken = NULL; prevToken = NULL ; tokens = NULL; 
    s = NULL; stokens = NULL; 
}

ParseResult Parser::parse (const char *text) {
    assert (text != NULL) ;

    ParseResult pr ;
    try {
        s = new Scanner() ;
        stokens = s->scan (text) ;        
        tokens = extendTokenList ( this, stokens ) ;

        assert (tokens != NULL) ;
        currToken = tokens ;
        pr = parseProgram( ) ;
    }
    catch (string errMsg) {
		
        pr.ok = false ;
        pr.errors = errMsg ;
        pr.ast = NULL ;
    }
    return pr ;
}

/* 
 * parse methods for non-terminal symbols
 * --------------------------------------
 */


/*! \fn ParseResult Parser::parseProgram ()
    \brief Begins parsing, attaches Root node for AST
*/ 
ParseResult Parser::parseProgram () {
    ParseResult pr ;
    // root
    // Program ::= varName '(' ')' '{' Stmts '}' 
    match(variableName) ;
    string name( prevToken->lexeme ) ;
    match(leftParen) ;
    match(rightParen) ;
    match(leftCurly);
    
    ParseResult pStmts = parseStmts() ;
    
    match(rightCurly);
    match(endOfFile) ;
    pr.ast = new Program(name, dynamic_cast<Stmts*>(pStmts.ast));
    return pr ;
}

/*! \fn ParseResult Parser::parseMatrixDecl ()
    \brief handles all matrix productions.
*/ 
ParseResult Parser::parseMatrixDecl () {
    ParseResult pr ;
    match(matrixKwd);
    match(variableName) ;
    string name1( prevToken->lexeme ) ;
    
    // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
    if(attemptMatch(leftSquare)){
        ParseResult pExpr = parseExpr(0);
        Expr *expr1 = dynamic_cast<Expr*>(pExpr.ast);
        match(colon);
        pExpr = parseExpr(0);
        Expr *expr2 = dynamic_cast<Expr*>(pExpr.ast);
        match(rightSquare);
        
        parseVariableName();
        string name2( prevToken->lexeme ) ;
        match(colon);
        
        parseVariableName();
        string name3( prevToken->lexeme ) ;
        match(assign);
        pExpr = parseExpr(0);
        Expr *expr3 = dynamic_cast<Expr*>(pExpr.ast);
        
        pr.ast = new ExtendedMatrixDecl(name1, expr1, expr2, name2, name3, expr3);
    }
 
    // Decl ::= 'matrix' varName '=' Expr ';'
    else if(attemptMatch(assign)){
        
        ParseResult pExpr1 = parseExpr(0);
        Expr *expr = dynamic_cast<Expr*>(pExpr1.ast);
        
        pr.ast = new MatrixDecl(name1, expr);
    }
    else{
        throw ((string) "Bad Syntax of Matrix Decl in in parseMatrixDecl" ) ;
    }  
 
    match(semiColon) ;
    return pr ;
}

/*! \fn ParseResult Parser::parseStandardDecl()
    \brief Parses standardDecl and make proper AST node
    Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
*/ 
ParseResult Parser::parseStandardDecl(){
    ParseResult pr ;
    
    //ParseResult prType = parseType() ;
	std::string tKwd;
	std::string vName;
	
    if ( attemptMatch(intKwd) ) {
        // Type ::= intKwd
        tKwd = (string) prevToken->lexeme;
    } 
    else if ( attemptMatch(floatKwd) ) {
        // Type ::= floatKwd
        tKwd = (string) prevToken->lexeme;
    }
    else if ( attemptMatch(stringKwd) ) {
        // Type ::= stringKwd
        tKwd = (string) prevToken->lexeme;
    }
    else if ( attemptMatch(boolKwd) ) {
        // Type ::= boolKwd
        tKwd = (string) prevToken->lexeme;
    }
        
    match(variableName) ;
    vName = (string) prevToken->lexeme;;
             
    pr.ast = new KwdDecl(tKwd, vName);
    
    match(semiColon) ;
        
    return pr ;
}

/*! \fn ParseResult Parser::parseDecl ()
    \brief Parses declarations
*/
ParseResult Parser::parseDecl () {
    ParseResult pr ;
    // Decl :: matrix variableName ....
    if(nextIs(matrixKwd)){
        pr = parseMatrixDecl();
    } 
    // Decl ::= Type variableName semiColon
    else{
        pr = parseStandardDecl();
        
    }
    return pr ;
}


/*! \fn ParseResult Parser::parseStmts ()
    \brief Parses Stmts
*/
ParseResult Parser::parseStmts () {
    ParseResult pr ;
    if (!nextIs(rightCurly) && !nextIs(inKwd) ) {
        // Stmts ::= Stmt Stmts
        ParseResult pStmt = parseStmt() ;
		Stmt *stmt = dynamic_cast<Stmt*>(pStmt.ast) ;
        
        ParseResult pStmts = parseStmts() ;
        Stmts *stmts = dynamic_cast<Stmts*>(pStmts.ast) ;
        
        pr.ast = new StmtsSeq(stmt, stmts);
    }
    else {
        // Stmts ::= 
        // nothing to match.
        pr.ast = new EmptyStmts() ;
    }
    return pr ;
}


/*! \fn ParseResult Parser::parseStmt ()
    \brief Parses any kind of stmt 
*/
ParseResult Parser::parseStmt () {
    ParseResult pr ;
 
    //Stmt ::= Decl
    if(nextIs(intKwd)||nextIs(floatKwd)||nextIs(matrixKwd)||nextIs(stringKwd)||nextIs(boolKwd)){
        ParseResult pDecl = parseDecl();
        pr.ast = new StmtDecl(dynamic_cast<Decl*>(pDecl.ast));
    }
    //Stmt ::= '{' Stmts '}'
    else if (attemptMatch(leftCurly)){
        ParseResult pStmts = parseStmts() ;
        match(rightCurly);
        pr.ast = new StmtsStmt(dynamic_cast<Stmts*>(pStmts.ast));
    }  
    //Stmt ::= 'if' '(' Expr ')' Stmt
    //Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    else if (attemptMatch(ifKwd)){
        match(leftParen);
        
        ParseResult pExpr = parseExpr(0);
        Expr *expr = dynamic_cast<Expr*>(pExpr.ast);
        match(rightParen);
        
        ParseResult pStmt = parseStmt();
        Stmt *stmt = dynamic_cast<Stmt*>(pStmt.ast);
       
        if(attemptMatch(elseKwd)){
            ParseResult pStmt = parseStmt();
            Stmt *stmt2 = dynamic_cast<Stmt*>(pStmt.ast);
            pr.ast = new IfElseStmt(expr, stmt, stmt2);
        }
        else {
            pr.ast = new IfStmt(expr, stmt);
        }
 
    }
    //Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']' '=' Expr ';'
    else if  ( attemptMatch (variableName) ) { 
        std::string name(prevToken->lexeme);
        
        //Stmt ::= varName '[' Expr ':' Expr ']' '=' Expr ';
        if (attemptMatch ( leftSquare ) ) {
			ParseResult pExpr1 = parseExpr(0);
            Expr *expr1 = dynamic_cast<Expr*>(pExpr1.ast);
            match ( colon ) ;
                        
            pExpr1 = parseExpr (0) ;
            Expr *expr2 = dynamic_cast<Expr*>(pExpr1.ast);
            match (rightSquare) ;
            match (assign);
                        
            pExpr1 = parseExpr (0) ;
            Expr *expr3 = dynamic_cast<Expr*>(pExpr1.ast);
            match(semiColon);      
            pr.ast = new ExtendedAssignStmt(name, expr1, expr2, expr3);
        }
        else {  //Stmt ::= varName '=' Expr ';'
            match(assign);
                        
            ParseResult pExpr = parseExpr(0);
            match(semiColon);
                        
            pr.ast = new AssignStmt(name, dynamic_cast<Expr*>(pExpr.ast));
                }
    }
    //Stmt ::= 'print' '(' Expr ')' ';'
    else if ( attemptMatch (printKwd) ) {
        match (leftParen) ;
        
        ParseResult pExpr = parseExpr(0);
        match (rightParen) ;
        match (semiColon) ;
        
        pr.ast = new PrintStmt(dynamic_cast<Expr*>(pExpr.ast));
    }
    //Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    else if ( attemptMatch (repeatKwd) ) {
        match (leftParen) ;
        match (variableName) ;
       
        std::string name(prevToken->lexeme);
       
        match (assign) ;
        
        ParseResult pExpr1 = parseExpr (0) ;
        Expr *from_expr = dynamic_cast<Expr*>(pExpr1.ast);
       
        match (toKwd) ;
        ParseResult pExpr2 = parseExpr (0) ;
        Expr *till_expr = dynamic_cast<Expr*>(pExpr2.ast);
       
        match (rightParen) ;
        
        ParseResult pStmt = parseStmt () ;
        Stmt *statement_under_repeat = dynamic_cast<Stmt*>(pStmt.ast);
       
        pr.ast = new RepeatStmt(name, from_expr, till_expr, statement_under_repeat);
    }
    //Stmt ::= 'while' '(' Expr ')' Stmt
    else if (attemptMatch(whileKwd)) {
        match(leftParen);
        ParseResult pExpr = parseExpr(0);
        Expr *condition_expr = dynamic_cast<Expr*>(pExpr.ast);
       
        match(rightParen);
       
        ParseResult pStmt = parseStmt();
        Stmt *statement_under_while = dynamic_cast<Stmt*>(pStmt.ast);
       
        pr.ast = new WhileStmt(condition_expr, statement_under_while);
    }
    //Stmt ::= ';'
    else if ( attemptMatch (semiColon) ) {
        // parsed a skip
    }
    else{
        throw ( makeErrorMsg ( currToken->terminal ) + " while parsing a statement" ) ;
    }
    // Stmt ::= variableName assign Expr semiColon
    return pr ;
}



/*! \fn ParseResult Parser::parseExpr (int rbp)
    \brief calls different parse functions for expression
*/
ParseResult Parser::parseExpr (int rbp) {
    /* Examine current token, without consuming it, to call its
       associated parse methods.  The ExtToken objects have 'nud' and
       'led' methods that are dispatchers that call the appropriate
       parse methods.*/
    ParseResult left = currToken->nud() ;
   
    while (rbp < currToken->lbp() ) {
        left = currToken->led(left) ;
    }

    return left ;
}


/*
 * parse methods for Expr productions
 * ----------------------------------
 */

 // Expr ::= trueKwd
 ParseResult Parser::parseTrueKwd ( ) {
     ParseResult pr ;
     match ( trueKwd ) ;
     pr.ast = new BooleanExpr(prevToken->lexeme);
     return pr ;
 }

 // Expr ::= falseKwd
 ParseResult Parser::parseFalseKwd ( ) {
     ParseResult pr ;
     match ( falseKwd ) ;
     pr.ast = new BooleanExpr(prevToken->lexeme);
     return pr ;
 }

// Expr ::= intConst
ParseResult Parser::parseIntConst ( ) {
    ParseResult pr ;
    match (intConst) ;
    pr.ast = new AnyExpr(prevToken->lexeme);
    return pr ;
}

// Expr ::= floatConst
ParseResult Parser::parseFloatConst ( ) {
    ParseResult pr ;
    match ( floatConst ) ;
    pr.ast = new AnyExpr(prevToken->lexeme);
    return pr ;
}

// Expr ::= stringConst
ParseResult Parser::parseStringConst ( ) {
    ParseResult pr ;
    match ( stringConst ) ;
    pr.ast = new AnyExpr(prevToken->lexeme);
    return pr ;
}

// Expr ::= variableName .....
ParseResult Parser::parseVariableName ( ) {
    ParseResult pr ;
    match (variableName) ;
    
    std::string name(prevToken->lexeme);
    
    // Expr ::= variableName '[' Expr ':' Expr ']' 
    if(attemptMatch(leftSquare)){
        ParseResult pExpr1 = parseExpr(0);
        match(colon);
        ParseResult pExpr2 = parseExpr(0);
        match(rightSquare);
        Expr *expr1 = dynamic_cast<Expr *>(pExpr1.ast);
        Expr *expr2 = dynamic_cast<Expr *>(pExpr2.ast);
        pr.ast = new MatrixRefExpr(name, expr1, expr2);
    }
    //Expr ::= varableName '(' Expr ')'        //NestedOrFunctionCall
    else if(attemptMatch(leftParen)){
        ParseResult pExpr = parseExpr(0);
        match(rightParen);
        Expr *expr = dynamic_cast<Expr *>(pExpr.ast);
        pr.ast = new NestedOrFunctionCallExpr(name, expr);
    }
    //Expr := variableName
    else{
        pr.ast = new VarExpr(name); 
    }
    return pr ;
}


// Expr ::= leftParen Expr rightParen
ParseResult Parser::parseNestedExpr ( ) {
    ParseResult pr ;
    match (leftParen) ;
    ParseResult pExpr = parseExpr(0) ; 
    Expr *exprInParen = dynamic_cast<Expr*>(pExpr.ast);
    match(rightParen) ;
    pr.ast = new NestedExpr(exprInParen);
    return pr ;
}

//Expr ::= 'if' Expr 'then' Expr 'else' Expr  
ParseResult Parser::parseIfExpr(){  
    ParseResult pr ; 
    
    match(ifKwd);
    ParseResult pExpr1 = parseExpr(0);
    Expr *ifExpr = dynamic_cast<Expr*>(pExpr1.ast);
    
    match(thenKwd);
    ParseResult pExpr2 = parseExpr(0);
    Expr *thenExpr = dynamic_cast<Expr*>(pExpr2.ast);
    
    match(elseKwd);
    ParseResult pExpr3 = parseExpr(0);
    Expr *elseExpr = dynamic_cast<Expr*>(pExpr3.ast);
    
    pr.ast = new IfElseExpr(ifExpr, thenExpr, elseExpr);

    return pr;
}


// Expr ::= 'let' Stmts 'in' Expr 'end' 
ParseResult Parser::parseLetExpr(){
	ParseResult pr ;
	match(letKwd);
	
	ParseResult pStmts = parseStmts();
	Stmts *letStmts = dynamic_cast<Stmts*>(pStmts.ast);
	
	match(inKwd);
	
	ParseResult pExpr = parseExpr(0);
	Expr *exprAfterLet = dynamic_cast<Expr*>(pExpr.ast); 
	
	match(endKwd);

	pr.ast = new LetExpr(letStmts, exprAfterLet);

	return pr;
}

// Expr ::= '!' Expr 
ParseResult Parser::parseNotExpr () {
    ParseResult pr ;
    match ( notOp ) ;
    ParseResult pExpr = parseExpr( 0 );
    Expr *notExpr = dynamic_cast<Expr*>(pExpr.ast);
    pr.ast =  new NotExpr(notExpr);
    return pr ;

}
// Expr ::= Expr plusSign Expr
ParseResult Parser::parseAddition ( ParseResult pLeft ) {
    // parser has already matched left expression 
    ParseResult pr ;
    Expr *left = dynamic_cast<Expr*>(pLeft.ast);
    
    match (plusSign) ;
    std::string opSign(prevToken->lexeme);
    
    ParseResult pRight = parseExpr( prevToken->lbp() ); 
    Expr *right = dynamic_cast<Expr*>(pRight.ast);
    
    pr.ast = new BinOpExpr(left, opSign, right);
    
    return pr ;
}

// Expr ::= Expr star Expr
ParseResult Parser::parseMultiplication ( ParseResult pLeft ) {
    // parser has already matched left expression 
    ParseResult pr ;
    Expr *left = dynamic_cast<Expr*>(pLeft.ast);
    
    match ( star ) ;
    std::string opSign(prevToken->lexeme);
    
    ParseResult pRight = parseExpr( prevToken->lbp() ); 
    Expr *right = dynamic_cast<Expr*>(pRight.ast);
    
    pr.ast = new BinOpExpr(left, opSign, right);
    
    return pr ;
}

// Expr ::= Expr dash Expr
ParseResult Parser::parseSubtraction ( ParseResult prLeft ) {
    // parser has already matched left expression 
    ParseResult pr ;
    Expr *left = dynamic_cast<Expr*>(prLeft.ast);
    
    match ( dash ) ;
    std::string opSign(prevToken->lexeme);
    
    ParseResult prRight = parseExpr( prevToken->lbp() ); 
    Expr *right = dynamic_cast<Expr*>(prRight.ast);
    
    pr.ast = new BinOpExpr(left, opSign, right);
    
    return pr ;
}

// Expr ::= Expr forwardSlash Expr
ParseResult Parser::parseDivision ( ParseResult pLeft ) {
    // parser has already matched left expression 
    ParseResult pr ;
    Expr *left = dynamic_cast<Expr*>(pLeft.ast);
    
    match (forwardSlash);
    std::string opSign(prevToken->lexeme);
    
    ParseResult pRight = parseExpr( prevToken->lbp() ); 
    Expr *right = dynamic_cast<Expr*>(pRight.ast);
    
    pr.ast = new BinOpExpr(left, opSign, right);
    
    return pr ;
}


// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
 */
ParseResult Parser::parseRelationalExpr ( ParseResult pLeft ) {
    // parser has already matched left expression 
    ParseResult pr ;
	Expr *left = dynamic_cast<Expr*>(pLeft.ast);
	
    nextToken( ) ;
    // just advance token, since examining it in parseExpr caused
    // this method being called.
    string op = (string) prevToken->lexeme ;
	
    ParseResult pRight = parseExpr( prevToken->lbp() ); 
    Expr *right = dynamic_cast<Expr*>(pRight.ast);
    
    pr.ast = new BinOpExpr(left, op, right);
    
    return pr ;
}


// Helper function used by the parser.

void Parser::match (tokenType tt) {
    if (! attemptMatch(tt)) {
        throw ( makeErrorMsgExpected ( tt ) ) ;
    }
}

bool Parser::attemptMatch (tokenType tt) {
    if (currToken->terminal == tt) { 
        nextToken() ;
        return true ;
    }
    return false ;
}

bool Parser::nextIs (tokenType tt) {
    return currToken->terminal == tt ;
}

void Parser::nextToken () {
    if ( currToken == NULL ) 
        throw ( string("Internal Error: should not call nextToken in unitialized state"));
    else 
    if (currToken->terminal == endOfFile && currToken->next == NULL) {
        prevToken = currToken ;
    } else if (currToken->terminal != endOfFile && currToken->next == NULL) {
        throw ( makeErrorMsg ( "Error: tokens end with endOfFile" ) ) ;
    } else {
        prevToken = currToken ;
        currToken = currToken->next ;
    }
}

string Parser::terminalDescription ( tokenType terminal ) {
    Token *dummyToken = new Token ("",terminal, NULL) ;
    ExtToken *dummyExtToken = extendToken (this, dummyToken) ;
    string s = dummyExtToken->description() ;
    delete dummyToken ;
    delete dummyExtToken ;
    return s ;
}

string Parser::makeErrorMsgExpected ( tokenType terminal ) {
    string s = (string) "Expected " + terminalDescription (terminal) +
        " but found " + currToken->description() ;
    return s ;
}

string Parser::makeErrorMsg ( tokenType terminal ) {
    string s = "Unexpected symbol " + terminalDescription (terminal) ;
    return s ;
}

string Parser::makeErrorMsg ( const char *msg ) {
    return msg ;
}


