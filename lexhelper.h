#pragma once

#ifndef LEXHELPER_H
#define LEXHELPER_H

#include <err.h>
#include <fcntl.h>
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
  TOKEN_KEYWORD,
  TOKEN_CONSTANT,
  TOKEN_SPECIAL,
  TOKEN_OP,
} TokenType;

typedef enum {
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_CURLY,
  TOKEN_RIGHT_CURLY,
  TOKEN_LEFT_BRACKET,
  TOKEN_RIGHT_BRACKET,
  TOKEN_SEMI_COLON,
  TOKEN_COMMA,
} Special_Symbol_Type;

extern uint32_t keywords_list[];
extern uint32_t special_symbols[];

typedef struct TokenObj *Token;
typedef struct TokenArrayObj *TokenArray;

bool is_digit_u32(uint32_t val);
bool is_semi_colon(uint32_t val);
bool is_left_paren(uint32_t val);
bool is_right_paren(uint32_t val);

void appendToken(TokenArray tArray, Token t);
// if the array is null then it should exit failure
// if not then it should create the newtoken
TokenArray newTokenArray(size_t capacity);

// void tokenArrayDestroy(TokenArrayObj arr);
// void tokenArrayAppend(TokenArrayObj arr, TokenObj token);
void printTokenArray(TokenArray arr);

const char *tokenTypeToString(TokenType type);
// void printToken(Token token);
// void printTokens(Token tokens, uint32_t token_count);

char *read_file_to_string(const char *filepath);

Token newToken(TokenType type, const char *start, size_t length);
// void tokensDestroy(TokenArray tokens);

#endif