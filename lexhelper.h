#pragma once

#ifndef LEXHELPER_H
#define LEXHELPER_H

#include <err.h>
#include <fcntl.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wctype.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef enum {
  TOKEN_RETURN,
  TOKEN_INT,
  TOKEN_VOID,
  TOKEN_IDENTIFIER,
  TOKEN_SEMI_COLON,
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_CURLY,
  TOKEN_RIGHT_CURLY,
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_SPECIAL,
  TOKEN_INTEGER,
  TOKEN_OP,
  TOKEN_EOF,
} TokenType;

typedef enum {
  TOKEN_COMMA,
} Special_Symbol_Type;

// extern uint32_t keywords_list[];
// extern uint32_t special_symbols[];

typedef struct TokenObj *Token;
typedef struct TokenArrayObj *TokenArray;

bool is_semi_colon(uint32_t val);

bool is_eof(uint32_t val);

bool is_left_paren(uint32_t val);
bool is_right_paren(uint32_t val);

bool is_left_brace(uint32_t val);
bool is_right_brace(uint32_t val);

bool is_left_bracket(uint32_t val);
bool is_right_bracket(uint32_t val);

bool is_digit_u32(uint32_t val);

void appendToken(TokenArray tArray, Token t);
// if the array is null then it should exit failure
// if not then it should create the newtoken
TokenArray newTokenArray();

void printTokenArray(FILE *out, TokenArray tA);

const char *tokenTypeToString(TokenType type);
void printToken(Token token);
// void printTokens(Token tokens, uint32_t token_count);

char *read_file_to_string(const char *filepath);

Token newToken(TokenType type, const char *start, size_t length);
TokenArray tokenize(char *file_content);
// void tokenArrayDestroy(TokenArrayObj arr);
// void tokensDestroy(TokenArray tokens);

#endif

// c99 | c11 keyword list
// ^(?!(?:auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|_Alignas|_Alignof|_Atomic|_Bool|_Complex|_Generic|_Imaginary|_Noreturn|_Static_assert|_Thread_local)\b)[a-zA-Z_][a-zA-Z0-9_]*$