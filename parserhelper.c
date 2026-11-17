#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "parserhelper.h"

typedef struct ParserObj {
  Token current;

  size_t index;

} ParserObj;

/*** Constructors-Destructors ***/

Parser newParser(TokenArray tokens) {
  Parser p = malloc(sizeof(ParserObj));

  p->current = firstToken(tokens);
  p->index = 0;

  return p;
}

/*** Access functions ***/
Token peek(Parser p) {
  if (p == NULL)
    exit(EXIT_FAILURE);

  printToken(nextToken(p->current));
  return nextToken(p->current);
}

Token advance(Parser p) {
  if (p == NULL)
    exit(EXIT_FAILURE);

  fprintf(stdout, "not advanced, p->current is now:\n");
  printToken(p->current);
  p->current = nextToken(p->current);

  fprintf(stdout, "just advanced, p->current is now:\n");
  printToken(p->current);

  return p->current;
}

/*** Manipulation procedures ***/

/*** Other Functions ***/
