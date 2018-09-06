%{
#include <stdio.h>
#include <string.h>
#define YYERROR_VERBOSE

int lineNo=1;
int errCnt=0;
void yyerror( char const *s );
%}

%token AND
%token BY
%token CHAR
%token ELSE
%token FOR
%token IF
%token INT
%token NOT
%token OR
%token PROCEDURE
%token READ
%token THEN
%token TO
%token WHILE
%token WRITE

%token LT
%token LE
%token EQ
%token NE
%token GT
%token GE

%token NAME
%token NUMBER
%token CHARCONST

%%
Procedure: PROCEDURE NAME '{' Decls Stmts '}'

Decls: Decls Decl ';' 
	 | Decl ';' ;

Decl: Type SpecList;

Type : INT
	 | CHAR;

SpecList : SpecList ',' Spec
		 | Spec ;

Spec : NAME 
	 | NAME '[' Bounds ']' ;

Bounds : Bounds ',' Bound 
       | Bound ;

Bound : NUMBER ':' NUMBER ;

Stmts : Stmts Stmt 
	  | Stmt ;

Stmt : Reference '=' Expr ';' 
     | '{' Stmts '}' 
     | WHILE '(' Bool ')' '{' Stmts '}' 
     | FOR NAME '=' Expr TO
          Expr BY Expr '{' Stmts '}' 
     | IF '(' Bool ')' THEN Stmt 
     | IF '(' Bool ')' THEN WithElse 
          ELSE Stmt 
     | READ Reference ';' 
     | WRITE Expr ';' 
     | error ';' { yyerrok; } 
     | '{' '}' { yyerror("Empty bracket");}; 
	
WithElse : IF '(' Bool ')' THEN WithElse ELSE WithElse
 	 	| Reference '=' Expr ';' 
     	 	| '{' Stmts '}' 
	 	| WHILE '(' Bool ')' '{' Stmts '}' 
     	 	| FOR NAME '=' Expr TO 
			Expr BY Expr '{' Stmts '}' 
	 	| READ Reference ';' 
	 	| WRITE Expr ';' ;

Bool : NOT OrTerm 
	 | OrTerm ;

OrTerm : OrTerm OR AndTerm 
	   | AndTerm ;

AndTerm : AndTerm AND RelExpr 
		| RelExpr ;
		
RelExpr : RelExpr LT Expr 
		| RelExpr LE Expr 
		| RelExpr EQ Expr 
		| RelExpr NE Expr 
		| RelExpr GE Expr 
		| RelExpr GT Expr 
		| Expr;

Expr : Expr '+' Term 
	 | Expr '-' Term
	 | Term ;

Term : Term '*' Factor 
	 | Term '/' Factor 
	 | Factor ;

Factor : '(' Expr ')' 
	   | Reference 
	   | NUMBER 
	   | CHARCONST ;
	   
Reference : NAME 
	   | NAME '[' Exprs ']';
	   
Exprs : Expr ',' Exprs 
	  | Expr ;
	
%%
int yywrap(void) {	/* for flex: only one input file */
    return 1;
}

void yyerror (char const *s)
{
	errCnt++;
	fprintf(stderr, "Parser: '%s' around line %d.\n", s, lineNo);
}