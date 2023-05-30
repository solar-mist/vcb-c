// Copyright 2023 solar-mist


#ifndef VCBC_LEXER_TOKEN_H
#define VCBC_LEXER_TOKEN_H 1

enum token_type
{
    TOK_IDENT,

    TOK_RETURN,

    TOK_INTEGER,

    TOK_LPAREN, TOK_RPAREN,

    TOK_LBRACE, TOK_RBRACE,

    TOK_SEMICOLON,
};

struct token
{
    enum token_type type;
    char* text;
    struct token* next;
};

struct token* new_token(enum token_type type, char* text);
char* token_type_to_string(enum token_type type);

#endif // VCBC_LEXER_TOKEN_H