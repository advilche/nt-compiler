#include <stdio.h>
#include <stdlib.h>

#include "lexhelper.h"
#include "parserhelper.h"

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    err(EXIT_FAILURE, "usage: ./lexer <filename>");
  }

  char *file_content = read_file_to_string(argv[1]);

  if (file_content == NULL) {
    err(EXIT_FAILURE, "File Error: file_content not read");
  }

  TokenArray tokens = tokenize(file_content);
  // printTokenArray(stdout, tokens);

  Parser p = newParser(tokens);

  advance(p);
  // peek(p);
  //   printTokens(tokens, 3);
  if (file_content != NULL) {
    printf("File Content:\n%s\n", file_content);

    free(file_content);
  }

  // free(tokens);
  // free(file_content);

  return 0;
}
