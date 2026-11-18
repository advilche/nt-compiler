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

  p->current = getFront(tokens);
  p->index = 0;

  return p;
}

/*** Access functions ***/
size_t getIndex(Parser p) { return p->index; }
Token getCurrent(Parser p) { return p->current; }

/*** Manipulation procedures ***/
Token peek(Parser p) {
  if (p == NULL)
    exit(EXIT_FAILURE);

  //   printToken(nextToken(p->current));
  return nextToken(p->current);
}

Token advance(Parser p) {
  if (p == NULL)
    exit(EXIT_FAILURE);

  //   fprintf(stdout, "not advanced, p->current is now:\n");
  //   printToken(p->current);
  p->current = nextToken(p->current);
  p->index += 1;

  //   fprintf(stdout, "just advanced, p->current is now:\n");
  //   printToken(p->current);

  return p->current;
}

Token expect(Parser p, TokenType type) {
  if (p == NULL) {
    exit(EXIT_FAILURE);
  }

  Token nextToken = peek(p);
  if (tokenKind(nextToken) != type) {
    exit(EXIT_FAILURE);
  }

  p->current = (advance(p));
  return p->current;
}

/*** Other Functions ***/
