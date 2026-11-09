#include "./lexhelper.h"

TokenArray tokenize(char *file_content) {
  size_t length = strlen(file_content);

  TokenArray tArray = newTokenArray(50);
  size_t token_count = 0;

  uint32_t cursor;
  for (size_t i = 0; i < length;) {
    // printf("DEBUG: i=%u, char='%c'\n", i, file_content[i]);
    cursor = i;

    if (iswalpha(file_content[cursor])) {
      size_t start = i;

      while (i < length && iswalpha((unsigned char)file_content[i])) {
        printf("is walpha\n");
        i++;
      }

      size_t word_length = i - start;

      if (word_length == strlen("return") &&
          strncmp(&file_content[start], "return", word_length) == 0) {

        Token token =
            newToken(TOKEN_KEYWORD, &file_content[start], word_length);
        
        appendToken(tArray, token);

        printToken(token);
        // tokens[token_count++] = *token;
      }
      continue;
    }

    if (isspace((unsigned char)file_content[cursor])) {
      printf("is space \n");
      i++;
      continue;
    }

    if (is_digit_u32(file_content[cursor])) {
      char *numeric;
      numeric = &file_content[cursor];

      while (is_digit_u32(file_content[i])) {
        printf("is digi \n");
        i++;
      }

      Token token = newToken(TOKEN_CONSTANT, numeric, i - cursor);
      printToken(token);

      // tokens[token_count++] = newToken;
    }

    if (is_semi_colon(file_content[cursor])) {
      printf("is semi \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);

      printToken(token);
      // tokens[token_count++] = newToken;

      i++;
    }

    if (is_left_paren(file_content[cursor])) {
      printf("is left paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      printToken(token);

      //   tokens[token_count++] = newToken;

      i++;
    }

    if (is_right_paren(file_content[cursor])) {
      printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      printToken(token);

      //   tokens[token_count++] = newToken;
      i++;
    }
  }

  return 0;
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    err(EXIT_FAILURE, "usage: ./lexer <filename>");
  }

  char *file_content = read_file_to_string(argv[1]);
  tokenize(file_content);

  //   printTokens(tokens, 3);
  if (file_content != NULL) {
    printf("File Content:\n%s\n", file_content);

    free(file_content);
  }

  // free(tokens);
  // free(file_content);

  return 0;
}
