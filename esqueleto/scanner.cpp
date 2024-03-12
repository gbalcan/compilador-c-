#include "scanner.h"    

//Construtor
Scanner::Scanner(string input, SymbolTable* table)
{
    pos = 0;
    line = 1;

    st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 
}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;
    
    // Trecho que reconhece Identificadores
    if (isalpha(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;
        while (isalnum(input[pos]) || input[pos] == '_')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        // Verifica se é uma palavra reservada
        STEntry* obj = st->get(lexeme);
        if (obj) {
            // Identificador é uma palavra reservada
            tok = new Token(obj->token->name);
        } else {
            // Identificador normal
            tok = new Token(ID, lexeme);
        }
    }
    // Trecho que reconhece Números
    else if (isdigit(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;
        while (isdigit(input[pos]))
        {
            lexeme.push_back(input[pos]);
            pos++;
        }
        tok = new Token(INTEGER_LITERAL, lexeme);
    }
    // Trecho que reconhece Strings
    else if (input[pos] == '\"')
    {
        pos++;  // Pula a primeira aspas
        while (input[pos] != '\"')
        {
            if (input[pos] == '\0' || input[pos] == '\n')
            {
                lexicalError("Unterminated string");
            }
            lexeme.push_back(input[pos]);
            pos++;
        }
        pos++;  // Pula a última aspas
        tok = new Token(STRING_LITERAL, lexeme);
    }
    // Trecho que reconhece Operadores
    else if (input[pos] == '<' || input[pos] == '>' || input[pos] == '=' || input[pos] == '!')
    {
        lexeme.push_back(input[pos]);
        pos++;
        if (input[pos] == '=')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }
        // Outros operadores relacionais
        else if (input[pos] == '<' || input[pos] == '>')
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        // Verifica o tipo do operador e retorna o token correspondente
        if (lexeme == "<")
            tok = new Token(LT);
        else if (lexeme == ">")
            tok = new Token(GT);
        else if (lexeme == "<=")
            tok = new Token(LEQ);
        else if (lexeme == ">=")
            tok = new Token(GEQ);
        else if (lexeme == "==")
            tok = new Token(EQ);
        else if (lexeme == "!=")
            tok = new Token(NE);
        else
            lexicalError("Operador não reconhecido");
    }
    else if (input[pos] == '+')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(PLUS);
    }
    else if (input[pos] == '-')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(MINUS);
    }
    else if (input[pos] == '*')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(MULT);
    }
    else if (input[pos] == '/')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(DIV);
    }
    else if (input[pos] == '%')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(MOD);
    }
    else if (input[pos] == '=')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(ATRIB);
    }
    // Trecho que reconhece Separadores
    else if (input[pos] == '(')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(LPARENTHESIS);
    }
    else if (input[pos] == ')')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(RPARENTHESIS);
    }
    else if (input[pos] == '[')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(LBRACKET);
    }
    else if (input[pos] == ']')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(RBRACKET);
    }
    else if (input[pos] == '{')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(LBRACE);
    }
    else if (input[pos] == '}')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(RBRACE);
    }
    else if (input[pos] == ';')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(SEMICOLON);
    }
    else if (input[pos] == '.')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(PERIOD);
    }
    else if (input[pos] == ',')
    {
        lexeme.push_back(input[pos]);
        pos++;
        tok = new Token(COMMA);
    }

    return tok;
 
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
