#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable* globalST;
    	SymbolTable* currentST;

		void advance();
		void match(int);
		void error(string);
		void initSimbolTable();

		void program();
		void classList();
		void classDecl();
		void classBody();
		void varDeclListOpt();
		void varDeclList();
		void varDecl();
		void varDeclOpt();
		void type();
		void constructDeclListOpt();
		void constructDeclList();
		void constructDecl();
		void methodDeclListOpt();
		void methodDeclList();
		void methodDecl();
		void methodBody();
		void paramListOpt();
		void paramList();
		void param();
		void statementsOpt();
		void statements();
		void statement();
		void attribStat();
		void printStat();
		void readStat();
		void returnStat();
		void superStat();
		void ifStat();
		void forStat();
		void attribStatOpt();
		void expressionOpt();
		void lValue();
		void lValueComp();
		void expression();
		void allocExpression();
		void numExpression();
		void term();
		void unaryExpression();
		void factor();
		void argListOpt();
		void argList();
		
	public:
		Parser(string);
		void run();
};
