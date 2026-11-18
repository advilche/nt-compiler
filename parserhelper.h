#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "lexhelper.h"

typedef struct ParserObj *Parser;

/*** Constructors-Destructors ***/
Parser newParser(TokenArray tokens);
void freeParser(Parser p);

/*** Access functions ***/
size_t getIndex(Parser p);
Token getCurrent(Parser p);

/*** Manipulation procedures ***/
Token peek(Parser p);
Token advance(Parser p);
Token expect(Parser p, TokenType type);

/*** Other Functions ***/


/**

program     = "int" identifier "(" "void" ")" "{" statement "}" EOF
statement   = "return" expression ";"
expression  = integer

**/