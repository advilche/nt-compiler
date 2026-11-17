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

typedef struct TokenObj *Token;
typedef struct TokenArrayObj *TokenArray;

/*** Constructors-Destructors ***/
Token newToken(TokenType type, const char *start, size_t length);
void tokenDestroy(Token *pT);
TokenArray newTokenArray();
// void tokenArrayDestroy(okenArrayObj arr);

/*** Access Functions ***/
Token firstToken(TokenArray tokens);
Token nextToken(Token token);
TokenType tokenKind(Token token);
TokenArray tokenize(char *file_content);

/*** Manipulation procedures ***/
void appendToken(TokenArray tArray, Token t);
void deleteFront(TokenArray tA);

/*** Other Functions ***/
void printTokenArray(FILE *out, TokenArray tA);
void printToken(Token token);

bool is_semi_colon(uint32_t val);
bool is_eof(uint32_t val);
bool is_left_paren(uint32_t val);
bool is_right_paren(uint32_t val);
bool is_left_brace(uint32_t val);
bool is_right_brace(uint32_t val);
bool is_left_bracket(uint32_t val);
bool is_right_bracket(uint32_t val);
bool is_digit_u32(uint32_t val);
const char *tokenTypeToString(TokenType type);
char *read_file_to_string(const char *filepath);

#endif

// c99 | c11 keyword list
// ^(?!(?:auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|_Alignas|_Alignof|_Atomic|_Bool|_Complex|_Generic|_Imaginary|_Noreturn|_Static_assert|_Thread_local)\b)[a-zA-Z_][a-zA-Z0-9_]*$