#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names
{
    UNDEF,//0
    ID,//1
    //PALAVRAS RESERVADAS
    CLASS,//2
    EXTENDS,//3
    INT,//4
    BREAK,//5
    PRINT,//6
    READ,//7
    RETURN,//8
    SUPER,//9
    IF,//10
    ELSE,//11
    FOR,//12
    NEW,//13
    CONSTRUCTOR,//14

    INTEGER_LITERAL,//15
    
    //OPERADORES
    OP, //operador
    LT, //16 <
    GT, //17 >
    LEQ, //18 <=
    GEQ, //19 >=
    PLUS, //20 +
    MINUS, //21 -
    MULT, //22 *
    DIV, //23 /
    MOD, //24 %
    ATRIB, //25 =
    EQ, //26 ==
    NE, //27 !=
    //SEPARADORES
    LPARENTHESIS,//28 (
    RPARENTHESIS,//29 )
    LBRACKET,//30 [
    RBRACKET, //31 ]
    LBRACE, //32 {
    RBRACE, //33 }
    SEMICOLON, //34 ;
    PERIOD, //35 .
    COMMA, //36 ,
    STRING, //37
    STRING_LITERAL, //38
    COMMENT, //39
    END_OF_FILE
};

class Token 
{
public: 
    int name;
    int attribute;
    string lexeme;
    bool reserved; // Novo atributo para indicar se é uma palavra reservada

    Token(int name)
    {
        this->name = name;
        attribute = UNDEF;
        reserved = false;
    }

    Token(int name, string l)
    {
        this->name = name;
        attribute = UNDEF;
        lexeme = l;
        reserved = false;
    }
    
    Token(int name, int attr)
    {
        this->name = name;
        attribute = attr;
        reserved = false;
    }
};
