// Daniel Tran and Yuxiang Wang

#ifndef Node_H
#define Node_H

#include <string>
#include <iostream> 

#include "scanner.h"

class Node ;

// Node
class Node {
	public:
        //! Method to unparse
		virtual std::string unparse ( ) = 0 ;
		//! Method to translating into C++
		virtual std::string cppCode ( ) = 0 ;
		virtual ~Node() { }
};

// Stmts
class Stmts : public Node {
};

// Stmt
class Stmt : public Node {
};

// Decl
class Decl : public Node {
};

// Expr
class Expr : public Node {
};

/////////////////////////////////////////////////////////
// Root
class Program : public Node {
	public:
        //! Constructor for Root/Program node
		Program(std::string _varname, Stmts* _stmts) {
	varname = _varname;
	stmts = _stmts;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string varname;
		Stmts* stmts;
};

//////////////////////////////////////////////////////
// Concrete classes derived from Stmts
// EmptyStmts
class EmptyStmts : public Stmts {
	public:
        //! Constructor for EmptyStmts node
        EmptyStmts() {}
		
		std::string unparse();
		std::string cppCode();
};

// StmtsSeq
class StmtsSeq : public Stmts {
	public:
        //! Constructor for StmtsSeq node
		StmtsSeq(Stmt* _stmt, Stmts* _stmts){
	stmt = _stmt;
	stmts = _stmts;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Stmt* stmt;
		Stmts* stmts;
};

////////////////////////////////////////////////////////
// Concrete classes derived from Stmt
// StmtDecl
class StmtDecl : public Stmt {
	public:
        //! Constructor for StmtDecl node
		StmtDecl(Decl* _decl) {
	decl = _decl;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Decl* decl;
};

// StmtsStmt
class StmtsStmt : public Stmt {
	public:
        //! Constructor for StmtsStmt node
		StmtsStmt(Stmts *_stmts) {
	stmts = _stmts;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Stmts *stmts;
};

// IfStmt
class IfStmt: public Stmt {
	public:
        //! Constructor for IfStmt node
		IfStmt(Expr *_expr, Stmt *_stmt) {
	expr = _expr;
	stmt = _stmt;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
		Stmt *stmt;
};

// IfElseStmt
class IfElseStmt: public Stmt {
	public:
        //! Constructor for IfElseStmt node
		IfElseStmt(Expr *_expr, Stmt *_stmt, Stmt *_stmt2) {
	expr = _expr;
	stmt = _stmt;
	stmt2 = _stmt2;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
		Stmt *stmt;
		Stmt *stmt2;
};

// AssignStmt
class AssignStmt : public Stmt {
	public:
        //! Constructor for AssignStmt node
		AssignStmt(std::string _varname, Expr *_expr) {
	varname = _varname;
	expr = _expr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string varname;
		Expr *expr;
};

// ExtendedAssignStmt
class ExtendedAssignStmt: public Stmt {
        public:
            //  Constructor for ExtendedAssignStmt node
            ExtendedAssignStmt(std::string _varname, Expr *_expr1, Expr *_expr2, Expr *_expr3) {
        varname =_varname;
        expr1 = _expr1;
        expr2 = _expr2;
        expr3 = _expr3;
}
            std::string unparse();
            std::string cppCode();
        
        private:
            std::string varname;
            Expr *expr1;
            Expr *expr2;
            Expr *expr3;
};

// PrintStmt
class PrintStmt : public Stmt {
	public:
        //! Constructor for PrintStmt node
		PrintStmt(Expr *_expr) {
	expr = _expr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
};

// RepeatStmt
class RepeatStmt : public Stmt {
	public:
        //! Constructor for RepeatStmt node
		RepeatStmt(std::string _varname, Expr *_expr1, Expr *_expr2, Stmt *_stmt) {
	varname = _varname;
	expr1 = _expr1;
	expr2 = _expr2;
	stmt = _stmt;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string varname;
		Expr *expr1;
		Expr *expr2;
		Stmt *stmt;
		
};

// WhileStmt
class WhileStmt : public Stmt {
	public:
        //! Constructor for WhileStmt node
		WhileStmt(Expr *_expr, Stmt *_stmt) {
	expr = _expr;
	stmt = _stmt;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
		Stmt *stmt;
};

///////////////////////////////////////////////////////////
// Concrete classes derived from Decl
// KwdDecl
class KwdDecl : public Decl {
	public:
        //! Constructor for StandardDecl node
		KwdDecl(std::string _kwd, std::string _varname) {
	kwd = _kwd;
	varname = _varname;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string kwd;
		std::string varname;
};

// MatrixDecl
class MatrixDecl : public Decl {
        public:
            //! Constructor for MatrixDecl node
            MatrixDecl(std :: string _varname, Expr *_expr) {
        varname = _varname;
        expr = _expr;
}
            std::string unparse();
            std::string cppCode();
        
        private:
            std :: string varname;
            Expr *expr;
};

// ExtendedMatrixDecl
class ExtendedMatrixDecl : public Decl {
        public:
            //! Constructor for ExtendedMatrixDecl node
            ExtendedMatrixDecl(std :: string _varname1, Expr *_expr1, Expr *_expr2, std :: string _varname2, std :: string _varname3, Expr *_expr3) {
        varname1 = _varname1;
        varname2 = _varname2;
        varname3 = _varname3;
        expr1 = _expr1;
        expr2 = _expr2;
        expr3 = _expr3;
}
            std::string unparse();
            std::string cppCode();
        
        private:
            Expr *expr1;
            Expr *expr2;
            Expr *expr3;
            std :: string varname1;
            std :: string varname2;
            std :: string varname3;
};

//////////////////////////////////////////////////////////
// Concrete classes derived from Expr
// VarExpr
class VarExpr : public Expr {
	public:
        // Concrete classes derived from VarExpr
		VarExpr(std::string _varname) {
	varname = _varname;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string varname;
};

// AnyExpr
class AnyExpr : public Expr {
	public:
        //! Constructor for ConstExpr node
		AnyExpr(std::string _anyStr) {
	anyStr = _anyStr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string anyStr;
};

// BooleanExpr
class BooleanExpr : public Expr {
	public:
        //! Constructor for BooleanExpr node
		BooleanExpr(std::string _var) {
	var = _var;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std::string var;
};

// BinOpExpr
class BinOpExpr : public Expr {
	public:
        //! Constructor for BinOpExpr node
		BinOpExpr(Expr *_expr1, std::string _op, Expr *_expr2) {
	expr1 = _expr1;
	op = _op;
	expr2 = _expr2;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr1;
		std::string op;
		Expr *expr2;
};

// MatrixRefExpr
class MatrixRefExpr : public Expr {
        public:
            //! Constructor for MatrixRefExpr node
            MatrixRefExpr(std :: string _varname, Expr *_expr1, Expr *_expr2) {
        varname = _varname;
        expr1 = _expr1;
        expr2 = _expr2;
}
            std::string unparse();
            std::string cppCode();
        
        private:
            std :: string varname;
            Expr *expr1;
            Expr *expr2;
};

// NestedOrFunctionCallExpr
class NestedOrFunctionCallExpr : public Expr {
	public:
        //! Constructor for NestedOrFunctionCallExpr node
		NestedOrFunctionCallExpr(std :: string _varname, Expr *_expr) {
	varname = _varname;
	expr = _expr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		std :: string varname;
		Expr *expr;
};

// NestedExpr
class NestedExpr : public Expr {
	public:
        //! Constructor for NestedExpr node
		NestedExpr(Expr *_expr) {
	expr = _expr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
};

// LetExpr
class LetExpr : public Expr {
	public:
        //! Constructor for LetExpr node
		LetExpr(Stmts *_stmts, Expr *_expr) {
	stmts = _stmts;
	expr = _expr;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Stmts *stmts;
		Expr *expr;
};

// IfElseExpr
class IfElseExpr : public Expr {
	public:
        //! Constructor for IfElseExpr node
		IfElseExpr(Expr *_expr1, Expr *_expr2, Expr *_expr3) {
	expr1 = _expr1;
	expr2 = _expr2;
	expr3 = _expr3;
}
		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr1;
		Expr *expr2;
		Expr *expr3;
};

// NotExpr
class NotExpr : public Expr {
	public:
        //! Constructor for NotExpr node
		NotExpr(Expr *_expr) {
	expr = _expr;
}

		std::string unparse();
		std::string cppCode();
	
	private:
		Expr *expr;
};


#endif


