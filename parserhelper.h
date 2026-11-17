#include <stdio.h>
#include <stdlib.h>

#include "lexhelper.h"

typedef struct ParserObj *Parser;

/*** Constructors-Destructors ***/

/*** Access functions ***/

/*** Manipulation procedures ***/

/*** Other Functions ***/


/**

program     = "int" identifier "(" "void" ")" "{" statement "}" EOF
statement   = "return" expression ";"
expression  = integer

**/