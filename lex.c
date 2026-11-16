#include "./lexhelper.h"

TokenArray tokenize(char *file_content) {
  size_t length = strlen(file_content);

  TokenArray tArray = newTokenArray();
  size_t token_count = 0;

  uint32_t cursor;
  for (size_t i = 0; i < length;) {
    //  printf("DEBUG: i=%u, char='%c'\n", i, file_content[i]);
    cursor = i;

    if (iswalpha(file_content[cursor])) {
      size_t start = i;

      while (i < length && iswalpha((unsigned char)file_content[i])) {
        // printf("is walpha\n");
        i++;
      }

      size_t word_length = i - start;

      //  keyword checking start

      if (word_length == strlen("return") &&
          strncmp(&file_content[start], "return", word_length) == 0) {

        Token token =
            newToken(TOKEN_RETURN, &file_content[start], word_length);

        appendToken(tArray, token);


      } else if (word_length == strlen("int") &&
        strncmp(&file_content[start], "int", word_length) == 0) {

        Token token = 
          newToken(TOKEN_INT, &file_content[start], word_length);

          appendToken(tArray, token);

      } else if (word_length == strlen("void") && 
      strncmp(&file_content[start], "void", word_length) == 0) {

        Token token = 
          newToken(TOKEN_VOID, &file_content[start], word_length);

          appendToken(tArray, token);

      } else {        
        printf("prob an identifier\n");
        Token token = 
          newToken(TOKEN_IDENTIFIER, &file_content[start], word_length);
          
          appendToken(tArray, token);

    };

      //  keyword checking end

      continue;
    }

    if (isspace((unsigned char)file_content[cursor])) {
      // printf("is space \n");
      i++;
      continue;
    }

    if (is_digit_u32(file_content[cursor])) {
      char *numeric;
      numeric = &file_content[cursor];

      while (is_digit_u32(file_content[i])) {
        // printf("is digi \n");
        i++;
      }

      Token token = newToken(TOKEN_INTEGER, numeric, i - cursor);
      appendToken(tArray, token);

    }

    if (is_semi_colon(file_content[cursor])) {
      // printf("is semi \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    if (is_left_paren(file_content[cursor])) {
      // printf("is left paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    if (is_right_paren(file_content[cursor])) {
      // printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    if (is_left_brace(file_content[cursor])) {
      // printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    if (is_right_brace(file_content[cursor])) {
      // printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }
    
    if (is_left_bracket(file_content[cursor])) {
      // printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    if (is_right_bracket(file_content[cursor])) {
      // printf("is right paren \n");
      Token token = newToken(TOKEN_SPECIAL, &file_content[cursor], (size_t)1);
      appendToken(tArray, token);

      i++;
    }

    // if (is_eof(file_content[cursor] == EOF)) {

    //   Token token = newToken(TOKEN_EOF, &file_content[cursor], (size_t)1);
    //   appendToken(tArray, token);

    //   i++;
    // }
  }

  return tArray;
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    err(EXIT_FAILURE, "usage: ./lexer <filename>");
  }

  char *file_content = read_file_to_string(argv[1]);

  if (file_content == NULL) {
    err(EXIT_FAILURE, "File Error: file_content not read");
  }

  TokenArray tArray = tokenize(file_content);
  printTokenArray(stdout, tArray);

  //   printTokens(tokens, 3);
  if (file_content != NULL) {
    printf("File Content:\n%s\n", file_content);

    free(file_content);
  }

;  // free(tokens);
  // free(file_content);

  return 0;
}
