#include "parser.h"

Parser::Parser(string input)
{
	currentST = globalST = new SymbolTable();
	initSimbolTable();

	scanner = new Scanner(input, globalST);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	

	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program()
{
	if (lToken->name == CLASS)
		classList();
}

void
Parser::classList()
{
	do
	{
		classDecl();
	}
	while(lToken->name == CLASS);
}

void
Parser::classDecl()
{
	match(CLASS);
	match(ID);

	if (lToken->name == EXTENDS)
	{
		advance();
		match(ID);
	}

	classBody();
}

void Parser::classBody() {
    match(LBRACE);
    varDeclListOpt();
    constructDeclListOpt();
    methodDeclListOpt();
    match(RBRACE);
}

void Parser::varDeclListOpt() {
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        varDeclList();
    }
}

void Parser::varDeclList() {
    varDecl();
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        varDecl();
    }
}

void Parser::varDecl() {
    type();
    match(ID);
    varDeclOpt();
    match(SEMICOLON);
}

void Parser::varDeclOpt() {
    while (lToken->name == COMMA) {
        match(COMMA);
        match(ID);
    }
}

void Parser::type() {
    if (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        match(lToken->name);
    } else {
        error("Erro: tipo esperado");
    }
}

void Parser::constructDeclListOpt()
{
    while (lToken->name == CONSTRUCTOR)
    {
        constructDecl();
    }
}

void Parser::constructDeclList()
{
    while (lToken->name == CONSTRUCTOR)
    {
        constructDecl();
    }
}

void Parser::constructDecl()
{
    match(CONSTRUCTOR);
    methodBody();
}

void Parser::methodDeclListOpt()
{
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID)
    {
        methodDecl();
    }
}

void Parser::methodDeclList()
{
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        methodDecl();
    }
}

void Parser::methodDecl() 
{
    type();
    match(ID);
    methodBody();
}

void Parser::methodBody() 
{
    match(LPARENTHESIS);
    paramListOpt();
    match(RPARENTHESIS);
    match(LBRACE);
    statementsOpt();
    match(RBRACE);
}

void Parser::paramListOpt()
 {
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        paramList();
    }
}

void Parser::paramList() 
{
    param();
    while (lToken->name == COMMA) {
        match(COMMA);
        param();
    }
}

void Parser::param() {
    type();
    match(ID);
}

void Parser::statementsOpt() {
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID ||
           lToken->name == IF || lToken->name == FOR || lToken->name == BREAK ||
           lToken->name == SEMICOLON || lToken->name == RETURN || lToken->name == SUPER ||
           lToken->name == PRINT || lToken->name == READ || lToken->name == ID) {
        statements();
    }
}

void Parser::statements() {
    while (lToken->name == INT || lToken->name == STRING || lToken->name == ID ||
           lToken->name == IF || lToken->name == FOR || lToken->name == BREAK ||
           lToken->name == SEMICOLON || lToken->name == RETURN || lToken->name == SUPER ||
           lToken->name == PRINT || lToken->name == READ || lToken->name == ID) {
        statement();
    }
}

void Parser::statement()
 {
    if (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        varDeclList();
    } else if (lToken->name == PRINT) {
        printStat();
        match(SEMICOLON);
    } else if (lToken->name == READ) {
        readStat();
        match(SEMICOLON);
    } else if (lToken->name == RETURN) {
        returnStat();
        match(SEMICOLON);
    } else if (lToken->name == SUPER) {
        superStat();
    } else if (lToken->name == IF) {
        ifStat();
    } else if (lToken->name == FOR) {
        forStat();
    } else if (lToken->name == BREAK) {
        match(BREAK);
        match(SEMICOLON);
    } else if (lToken->name == SEMICOLON) {
        match(SEMICOLON);
    }
}

void Parser::attribStat()
 {
    lValue();
    match(ATRIB);
    expression();
}

void Parser::printStat() 
{
    match(PRINT);
    expression();
}

void Parser::readStat() 
{
    match(READ);
    lValue();
}

void Parser::returnStat() 
{
    match(RETURN);
    expression();
}

void Parser::superStat() 
{
    match(SUPER);
    match(LPARENTHESIS);
    argListOpt();
    match(RPARENTHESIS);
}

void Parser::ifStat() 
{
    match(IF);
    match(LPARENTHESIS);
    expression();
    match(RPARENTHESIS);
    match(LBRACE);
    statements();
    match(RBRACE);
    if (lToken->name == ELSE) {
        match(ELSE);
        match(LBRACE);
        statements();
        match(RBRACE);
    }
}

void Parser::forStat() 
{
    match(FOR);
    match(LPARENTHESIS);
    attribStatOpt();
    match(SEMICOLON);
    expressionOpt();
    match(SEMICOLON);
    attribStatOpt();
    match(RPARENTHESIS);
    match(LBRACE);
    statements();
    match(RBRACE);
}

void Parser::attribStatOpt() 
{
    if (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        attribStat();
    }
}

void Parser::expressionOpt() 
{
    if (lToken->name == NEW || lToken->name == INT || lToken->name == STRING ||
        lToken->name == ID || lToken->name == LPARENTHESIS || lToken->name == PLUS ||
        lToken->name == MINUS) {
        expression();
    }
}

void Parser::lValue() 
{
    match(ID);
    lValueComp();
}

void Parser::lValueComp() 
{
    while (lToken->name == PERIOD || lToken->name == LBRACKET) {
        if (lToken->name == PERIOD) {
            match(PERIOD);
            match(ID);
        } else if (lToken->name == LBRACKET) {
            match(LBRACKET);
            expression();
            match(RBRACKET);
        } else if (lToken->name == LPARENTHESIS) {
            match(LPARENTHESIS);
            argListOpt();
            match(RPARENTHESIS);
        }
    }
}

void Parser::expression() 
{
    numExpression();
    while (lToken->name == LT || lToken->name == GT || lToken->name == EQ || lToken->name == NE) {
        match(lToken->name);
        numExpression();
    }
}

void Parser::allocExpression()
{
    if (lToken->name == NEW) {
        match(NEW);
        match(ID);
        match(LPARENTHESIS);
        argListOpt();
        match(RPARENTHESIS);
    } else if (lToken->name == INT || lToken->name == STRING || lToken->name == ID) {
        type();
        match(LBRACKET);
        expression();
        match(RBRACKET);
    }
}

void Parser::numExpression() {
    term();
    while (lToken->name == PLUS || lToken->name == MINUS) {
        match(lToken->name);
        term();
    }
}

void Parser::term() {
    unaryExpression();
    while (lToken->name == MULT || lToken->name == DIV || lToken->name == MOD) {
        match(lToken->name);
        unaryExpression();
    }
}

void Parser::unaryExpression() {
    if (lToken->name == PLUS || lToken->name == MINUS) {
        match(lToken->name);
        factor();
    } else {
        factor();
    }
}

void Parser::factor() 
{
    if (lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL) {
        match(lToken->name);
    } else if (lToken->name == ID) {
        lValue();
    } else if (lToken->name == LPARENTHESIS) {
        match(LPARENTHESIS);
        expression();
        match(RPARENTHESIS);
    }
}

void Parser::argListOpt() 
{
    if (lToken->name == ID || lToken->name == INTEGER_LITERAL || lToken->name == STRING_LITERAL ||
        lToken->name == LPARENTHESIS || lToken->name == NEW || lToken->name == PLUS || lToken->name == MINUS) {
        argList();
    }
}

void Parser::argList() 
{
    expression();
    while (lToken->name == COMMA) {
        match(COMMA);
        expression();
    }
}

void
Parser::initSimbolTable()
{
	Token* t;
        
	t = new Token(CLASS, "class");
	globalST->add(new STEntry(t, true));
	t = new Token(EXTENDS, "extends");
    	globalST->add(new STEntry(t, true));
	t = new Token(INT, "int");
    	globalST->add(new STEntry(t, true));
    	t = new Token(BREAK, "break");
    	globalST->add(new STEntry(t, true));
    	t = new Token(PRINT, "print");
    	globalST->add(new STEntry(t, true));
    	t = new Token(READ, "read");
    	globalST->add(new STEntry(t, true));
    	t = new Token(RETURN, "return");
    	globalST->add(new STEntry(t, true));
    	t = new Token(SUPER, "super");
    	globalST->add(new STEntry(t, true));
    	t = new Token(IF, "if");
    	globalST->add(new STEntry(t, true));
    	t = new Token(ELSE, "else");
    	globalST->add(new STEntry(t, true));
    	t = new Token(FOR, "for");
    	globalST->add(new STEntry(t, true));
    	t = new Token(NEW, "new");
    	globalST->add(new STEntry(t, true));
    	t = new Token(CONSTRUCTOR, "constructor");
    	globalST->add(new STEntry(t, true));
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
