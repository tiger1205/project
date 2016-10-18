/*!
 \author Yuxiang Wang
 \author Daniel Tran
 \file ast.cpp
 \brief The abstract syntax tree
 */

#include "AST.h"

using namespace std;
///////////////////////////////////////////////////////


/*! \fn Program::unparse()
 \brief varName '(' ')' '{' Stmts '}'
 */
std::string Program::unparse() {
	return varname + " () {" + stmts->unparse() + "}";
}
std::string Program::cppCode() {
	return (string)
	"#include <iostream>\n" +
	"#include \"Matrix.h\"\n" +
	"#include <math.h>\n" +
	"using namespace std; \n" +
	"int main () { \n" +
	stmts->cppCode() +
	"\n}\n";
}

/*! \fn EmptyStmts::unparse()
 \brief <<empty>>
 */
std::string EmptyStmts::unparse() {
	return " ";
}

std::string EmptyStmts::cppCode() {
	return (string) " ";
}
/*! \fn StmtsSeq::unparse()
 \brief Stmt Stmts
 */
std::string StmtsSeq::unparse() {
	return stmt->unparse() + stmts->unparse();
}

std::string StmtsSeq::cppCode() {
	return (string) stmt->cppCode() + stmts->cppCode();
}

////////////////////////////////////////////////////////

/*! \fn StmtDecl::unparse()
 \brief Decl
 */
std::string StmtDecl::unparse() {
	return decl->unparse();
}

std::string StmtDecl::cppCode() {
	return (string) decl->cppCode();
}

/*! \fn StmtsStmt::unparse()
 \brief '{' Stmts '}'
 */
std::string StmtsStmt::unparse() {
	return "{ \n" + stmts->unparse() + "\n} \n";
}

std::string StmtsStmt::cppCode() {
	return (string) "{ \n" + stmts->cppCode()+ "} \n";
}

/*! \fn IfStmt::unparse()
 \brief 'if' '(' Expr ')' Stmt
 */
std::string IfStmt::unparse() {
	return "if (" + expr->unparse() + ")" + "\t" + stmt->unparse();
}

std::string IfStmt::cppCode() {
	return (string) "if (" + expr->cppCode() + ")" + stmt->cppCode();
}
/*! \fn IfElseStmt::unparse()
 \brief 'if' '(' Expr ')' Stmt 'else' Stmt
 */
std::string IfElseStmt::unparse() {
	return "if (" + expr->unparse() + ")" + stmt->unparse() + "\n else" + stmt2->unparse();
}

std::string IfElseStmt::cppCode() {
	return (string) "if (" + expr->cppCode() + ")" + stmt->cppCode() + "\n else " + stmt2->cppCode();
}
/*! \fn AssignStmt::unparse()
 \brief varName '=' Expr ';'
 */
std::string AssignStmt::unparse() {
	return varname + " = " + expr->unparse() + ";";
}

std::string AssignStmt::cppCode() {
	return (string) varname + " = " + expr->cppCode() + ";";
}

/*! \fn ExtendedAssignStmt::unparse()
 \brief varName '[' Expr ',' Expr ']' '=' Expr ';'
 */
std::string ExtendedAssignStmt::unparse() {
	return varname + "[" + expr1->unparse() +":"+ expr2->unparse() + "] = " + expr3->unparse() + ";";
}

std::string ExtendedAssignStmt::cppCode() {
	return (string) "*("+varname + ".access(" + expr1->cppCode() + ", " + expr2->cppCode() + ")) = " + expr3->cppCode() + " ;";
}
/*! \fn PrintStmt::unparse()
 \brief 'print' '(' Expr ')' ';'
 */
std::string PrintStmt::unparse() {
	return "print(" + expr->unparse() + "); \n";
}

std::string PrintStmt::cppCode() {
	return (string) "cout << " + expr->cppCode() + "; \n";
}

/*! \fn RepeatStmt::unparse()
 \brief 'for' '(' varName '=' Expr ':' Expr ')' Stmt
 */
std::string RepeatStmt::unparse() {
	return "repeat(" + varname + " = " + expr1->unparse() + " to " + expr2->unparse() + ")" + stmt->unparse();
}

std::string RepeatStmt::cppCode() {
	return (string) "for (" + varname + " = " + expr1->cppCode() + " ;" + varname + " <= " + expr2->cppCode() + "; " + varname + "++ )" + "\t" + stmt->cppCode() + "\n";
}

/*! \fn WhileStmt::unparse()
 \brief 'while' '(' Expr ')' Stmt
 */
std::string WhileStmt::unparse() {
	return "while (" + expr->unparse() + ")" + stmt->unparse() ;
}

std::string WhileStmt::cppCode() {
	return (string) "while (" + expr->cppCode() + ")" + stmt->cppCode() ;
}
//////////////////////////////////////////////////////////
/*! \fn KwdDecl::unparse()
 \brief 'type' varName ';'
 */
std::string KwdDecl::unparse() {
	return kwd + " " + varname + ";";
}

std::string KwdDecl::cppCode() {
	if(kwd == "int")
	return (string) "int " + varname + "; \n";
	if(kwd == "float")
	return (string) "float " + varname + "; \n";
	if(kwd == "string")
	return (string) "string " + varname + "; \n";
	if(kwd == "boolean")
	return (string) "boolean " + varname + "; \n";
}

/*! \fn ExtendedMatrixDecl::unparse()
 \brief 'Matrix' varName '[' Expr ',' Expr ']' varName ',' varName  '=' Expr ';'
 */
std::string ExtendedMatrixDecl::unparse() {
	return "matrix " + varname1 + "[" + expr1->unparse() + ":" + expr2->unparse() + "]" + varname2 + ":" + varname3 + "=" + expr3->unparse() + ";";
}

std::string ExtendedMatrixDecl::cppCode() {
	    
		string e1 = expr1->cppCode();
		string e2 = expr2->cppCode();
	
	return (string) "matrix " + varname1 + "( "+ e1 +","+ e2 +") ; \n" 
						+ "for (int " + varname2 + " = 0;" + varname2 + " < " + e1 + "; " + varname2 +" ++ ) { \n"
							+ "		for (int " + varname3 + " = 0;" + varname3 + " < " + e2 + "; " + varname3 +" ++ ) { \n" 
								+ " 	*("+ varname1 +".access(" + varname2 + "," + varname3 + ")) = " + expr3->cppCode() + " ;} } \n";
}
/*! \fn MatrixDecl::unparse()
 \brief 'Matrix' varName '=' Expr ';'
 */
std::string MatrixDecl::unparse() {
	return "matrix " + varname + "=" + expr->unparse() + ";";
}

std::string MatrixDecl::cppCode() {
	return (string) "matrix " + varname +"( " + expr->cppCode() + " ) ; \n" ;
	
}
//////////////////////////////////////////////////////////
/*! \fn VarExpr::unparse()
 \brief varName
 */
std::string VarExpr::unparse() {
	return varname;
}
std::string VarExpr::cppCode() {
	return (string) varname;
}	

/*! \fn AnyExpr::unparse()
 \brief integerConst | floatConst |  stringConst
 */
std::string AnyExpr::unparse() {
	return anyStr;
}

std::string AnyExpr::cppCode() {
	return (string) anyStr ; 
}

/*! \fn  BooleanExpr::unparse()
 \brief Expr 'op' Expr
 */

std::string BooleanExpr::unparse() {
	return var;
}

std::string BooleanExpr::cppCode() {
	return (string) var;
}

/*! \fn BinOpExpr::unparse()
 \brief Expr 'op' Expr
 */
std::string BinOpExpr::unparse() {
	return expr1->unparse() + op + expr2->unparse();
}

std::string BinOpExpr::cppCode() {
	return "(" + expr1->cppCode() + op + expr2->cppCode() +")"; 
}
/*! \fn MatrixRefExpr::unparse()
 \brief varName '[' Expr ',' Expr ']'
 */
std::string MatrixRefExpr::unparse() {
    return varname + "[" + expr1->unparse() + ":" + expr2->unparse() + " ]";
}

std::string MatrixRefExpr::cppCode() {
	return (string) "*( " + varname + ".access(" + expr1->cppCode() + ", " + expr2->cppCode() + ")) ";
}


/*! \fn NestedOrFunctionCall::unparse()
 \brief varName '(' Expr ')'
 */
std::string NestedOrFunctionCallExpr::unparse() {
	return varname + "(" + expr->unparse() + ")";
}

std::string NestedOrFunctionCallExpr::cppCode() {
	if (varname == "numRows" || varname == "numCols") 
	{	
		return (string) expr->cppCode()+ "." + varname + "()\n"; 
	}
	else if (varname == "matrixRead")
	{
		return (string) ("matrix::matrixRead") + " (" + expr -> cppCode() + " )";
	}
	else
		return (string) varname + " (" + expr->cppCode() + " )\n";
}
/*! \fn NestedExpr::unparse()
 \brief '(' Expr ')'
 */
std::string NestedExpr::unparse() {
	return "(" + expr->unparse() + ")";
}

std::string NestedExpr::cppCode() {
	return (string) "" + expr->cppCode() + "";
}

/*! \fn  LetExpr::unparse()
 \brief 'let' Stmts 'in' Expr 'end'
 */
std::string LetExpr::unparse() {
	return "let " + stmts->unparse() + " in " + expr->unparse() + " end ";
}

std::string LetExpr::cppCode() {
	return (string) "({" + stmts->cppCode() + expr->cppCode() + "; })\n " ;
}


/*! \fn IfElseExpr::unparse()
 \brief 'if' Expr 'then' Expr 'else' Expr
 */
std::string IfElseExpr::unparse() {
	return "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse();
}

std::string IfElseExpr::cppCode() {
	return (string) "( (" + expr1->cppCode() + ") ? (" +expr2->cppCode() + ") : " + expr3->cppCode() + " )\n";
}
/*! \fn NotExpr::unparse()
 \brief '!' Expr
 */
std::string NotExpr::unparse() {
	return "!" + expr->unparse();
}
std::string NotExpr::cppCode() {
	return (string) "! (" + expr->cppCode() +") ";
}




