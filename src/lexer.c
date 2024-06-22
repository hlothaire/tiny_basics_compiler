#include "../includes/lexer.h"

Lexer *initLexer(const char *input) {
  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
  lexer->source = strdup(input);
  lexer->curChar = '\0';
  lexer->curPos = -1;
  nextChar(lexer);
  return lexer;
}

void freeLexer(Lexer *lexer) {
  free(lexer->source);
  free(lexer);
}

void nextChar(Lexer *lexer) {
  lexer->curPos++;
  lexer->curChar = lexer->source[lexer->curPos];
}

char peek(Lexer *lexer) { return lexer->source[lexer->curPos + 1]; }

void skipWhitespace(Lexer *lexer) {
  while (isspace(lexer->curChar)) {
    nextChar(lexer);
  }
}

void skipComment(Lexer *lexer) {
  if (lexer->curChar == '#') {
    while (lexer->curChar != '\n') {
      nextChar(lexer);
    }
  }
}

void abortLexing(Lexer *lexer, const char *message) {
  fprintf(stderr, "lexing error. %s\n", message);
  exit(EXIT_FAILURE);
}

Token *getToken(Lexer *lexer) {
  skipWhitespace(lexer);
  skipComment(lexer);
  Token *token = (Token *)malloc(sizeof(Token));
  token->text = NULL;

  switch (lexer->curChar) {
  case '+':
    token->text = "+";
    token->kind = PLUS_TOKEN;
    nextChar(lexer);
    break;
  case '-':
    token->text = "-";
    token->kind = MINUS_TOKEN;
    nextChar(lexer);
    break;
  case '*':
    token->text = "*";
    token->kind = ASTERISK_TOKEN;
    break;
  case '/':
    token->text = "/";
    token->kind = SLASH_TOKEN;
    break;
  case '=':
    if (peek(lexer) == '=') {
        nextChar(lexer);
        token->text = "==";
        token->kind = EQEQ_TOKEN;
      } else {
        token->text = "=";
        token->kind = EQ_TOKEN;
      }
    break;
  case '>':
    if (peek(lexer) == '=') {
        nextChar(lexer);
        token->text = ">=";
        token->kind = GTEQ_TOKEN;
      } else {
        token->text = ">";
        token->kind = GT_TOKEN;
      }
    break;
  case '<':
    if (peek(lexer) == '=') {
        nextChar(lexer);
        token->text = "<=";
        token->kind = LTEQ_TOKEN;
      } else {
        token->text = "<";
        token->kind = LT_TOKEN;
      }
    break;
  case '!':
    if (peek(lexer) == '=') {

      }
  default:
    abortLexing(lexer, "Unknown token");
  }

  return token;
}

void printToken(Token *token) {
  printf("Token(text='%s', type=%d)\n", token->text, token->kind);
}
