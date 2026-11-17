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
} TokenArrayObj;

/*** Constructors-Destructors ***/

Token newToken(TokenType type, const char *start, size_t length) {
  Token t = malloc(sizeof(TokenObj));

  t->type = type;
  t->start = start;
  t->length = length;

  t->prev = NULL;
  t->next = NULL;

  return t;
}

void tokenDestroy(Token *pT) {
  if ((pT != NULL) && (*pT != NULL)) {
    free(*pT);
    *pT = NULL;
  }
}

TokenArray newTokenArray() {
  TokenArray tArray;

  tArray = malloc(sizeof(TokenArrayObj));

  if (tArray == NULL)
    return NULL;

  tArray->front = NULL;
  tArray->back = NULL;

  tArray->length = 0;

  return tArray;
}

/*** Access Functions ***/

Token firstToken(TokenArray tokens) {
  if (tokens == NULL)
    return NULL;

  return tokens->front;
}

Token nextToken(Token token) {
  if (token == NULL)
    return NULL;
  return token->next;
}

TokenType tokenKind(Token token) {
  if (token == NULL)
    exit(EXIT_FAILURE);
  return token->type;
}

/*** Manipulation procedures ***/

void appendToken(TokenArray tA, Token t) {
  if (tA == NULL) {
    printf(
        "Token Array Error: calling append() on NULL Token Array reference\n");
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

void deleteFront(TokenArray tA);

/*** Other Functions ***/
void printToken(Token token) {
  printf("\n");
  printf("Type: %s\n", tokenTypeToString(token->type));
  printf("Text: %.*s\n", (int)token->length, token->start);
  printf("Length: %zu\n", token->length);
  printf("\n");
}

void printTokenArray(FILE *out, TokenArray tA) {
  Token current = tA->front;
  while (current != NULL) {
    printToken(current);
    current = current->next;
  }
  fprintf(out, "\n");
}

bool is_semi_colon(uint32_t val) { return (val == ';'); }
bool is_apostrophe(uint32_t val) { return (val) == '\''; }
bool is_eof(uint32_t val) { return (val) == '\0'; }
bool is_left_paren(uint32_t val) { return (val == '('); }
bool is_right_paren(uint32_t val) { return (val == ')'); }
bool is_left_brace(uint32_t val) { return (val) == '{'; }
bool is_right_brace(uint32_t val) { return (val) == '}'; }
bool is_right_bracket(uint32_t val) { return (val) == ']'; }
bool is_left_bracket(uint32_t val) { return (val) == '['; }
bool is_digit_u32(uint32_t val) { return (val >= '0' && val <= '9'); }

const char *tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_RETURN:
    return "return";

  case TOKEN_INT:
    return "int";

  case TOKEN_VOID:
    return "void";

  case TOKEN_IDENTIFIER:
    return "identifier";

  case TOKEN_SEMI_COLON:
    return "semi colon";

  case TOKEN_LEFT_PAREN:
    return "left paren";

  case TOKEN_RIGHT_PAREN:
    return "right paren";

  case TOKEN_LEFT_CURLY:
    return "left curly";

  case TOKEN_RIGHT_CURLY:
    return "right curly";

  case TOKEN_LEFT_BRACKET:
    return "left bracket";

  case TOKEN_RIGHT_BRACKET:
    return "right bracket";

  case TOKEN_SPECIAL:
    return "special";

  case TOKEN_INTEGER:
    return "integer";

  case TOKEN_OP:
    return "operator";

  case TOKEN_EOF:
    return "eof";

  default:
    return "UNKNOWN";
  }
}

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
