#include "lexhelper.h"

typedef struct TokenObj {
  TokenType type;
  Token prev;
  Token next;

  const char *start;
  size_t length;
} TokenObj;

typedef struct TokenArrayObj {
  Token front;
  Token back;

  size_t length;
  size_t capacity;
} TokenArrayObj;

bool is_semi_colon(uint32_t val) { return (val == ';'); }
bool is_left_paren(uint32_t val) { return (val == '('); }
bool is_right_paren(uint32_t val) { return (val == ')'); }
bool is_digit_u32(uint32_t val) { return (val >= '0' && val <= '9'); }

const char *tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_KEYWORD:
    return "keyword";

  case TOKEN_CONSTANT:
    return "constant";

  case TOKEN_OP:
    return "operator";

  case TOKEN_SPECIAL:
    return "special";

  default:
    return "UNKNOWN";
  }
}

void appendToken(TokenArray tA, Token t) {
  if (tA == NULL) {
    printf("Token Array Error: calling append() on NULL Token Array reference\n");
    exit(EXIT_FAILURE);
  }

  if (t == NULL) {
    printf("Token Error: calling append() on NULL Token reference\n");
    exit(EXIT_FAILURE);
  }

  if (tA->length == 0) {
    tA->front = t;
    tA->back = t;
  } else {
    t->prev = tA->back;
    tA->back->next = t;
    tA->back = t;
  }
  tA->length += 1;
}

// uint32_t keywords_list[] = {'return', 'if', 'while', 'for'};
// uint32_t special_symbols[] = {'(', ')', '{', '}', '[', ']', ';', ','};

void printToken(Token token) {
  printf("\n");
  printf("Type: %s\n", tokenTypeToString(token->type));
  printf("Text: %.*s\n", (int)token->length, token->start);
  printf("Length: %zu\n", token->length);
  printf("\n");
}

// void printTokenArray(TokenArray arr) {
//   for (size_t i = 0; i <= arr->length; i++){

//   }
// }

// void printTokens(Token *tokens, uint32_t token_count) {
//   for (size_t i = 0; i < token_count; i++) {
//     printf("%zu: ", i);
//     printToken(tokens[i]);
//   }
// }

char *read_file_to_string(const char *filepath) {
  int fd = open(filepath, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return NULL;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("Error getting file stats");
    close(fd);
    return NULL;
  }

  size_t file_size = sb.st_size;
  char *buffer = malloc(file_size + 1);
  if (buffer == NULL) {
    perror("Memory allocation failed");
    close(fd);
    return NULL;
  }

  size_t total_read = 0;
  ssize_t bytes_read;

  while (total_read < file_size) {
    bytes_read = read(fd, buffer + total_read, file_size - total_read);

    if (bytes_read == -1) {
      perror("Error reading file");
      free(buffer);
      close(fd);
      return NULL;
    }

    if (bytes_read == 0) {
      break;
    }

    total_read += bytes_read;
  }

  buffer[total_read] = '\0';

  close(fd);

  return buffer;
}

// void tokenArrayDestroy(TokenArr arr){
//     if (arr != NULL){
//         tokensDestroy(arr->tokens);
//         free(arr);
//     }
// }

// void tokensDestroy(Token* tokens){
//     free(tokens);
// }

Token newToken(TokenType type, const char *start, size_t length) {
  Token t = malloc(sizeof(TokenObj));

  t->type = type;
  t->start = start;
  t->length = length;

  t->prev = NULL;
  t->next = NULL;

  return t;
}

TokenArray newTokenArray(size_t capacity) {
  if (capacity == 0)
    return NULL;
  TokenArray tArray;

  tArray = malloc(sizeof(TokenArrayObj));

  if (tArray == NULL)
    return NULL;

  tArray->front = NULL;
  tArray->back = NULL;

  tArray->length = 0;
  tArray->capacity = capacity;

  return tArray;
}