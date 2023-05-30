// Copyright 2023 solar-mist


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <lexer/lexer.h>

static int position = 0;
char* file;

char lexer_current();
char lexer_consume();
struct token* add_token(struct token* arr, struct token* tok);
struct token* lexer_next();

struct token* lexer_lex(char* buffer)
{
    struct token* tokens = NULL;
    file = buffer;
    while(lexer_current() != EOF)
    {
        tokens = add_token(tokens, lexer_next());
        lexer_consume();
    }
    return tokens;
}


char lexer_current()
{
    return file[position];
}

char lexer_consume()
{
    return file[position++];
}

char lexer_peek(int off)
{
    return file[position + off];
}


struct token* add_token(struct token* tokens, struct token* tok)
{
    if(!tok)
        return tokens;
    
    if(!tokens)
    {
        tokens = tok;
        return tokens;
    }

    struct token* curr = tokens;
    while(curr->next)
        curr = curr->next;
    
    curr->next = tok;
    return tokens;
}

struct token* lexer_next()
{
    while(isspace(lexer_current()))
        lexer_consume();
    
    if(isalpha(lexer_current()) || lexer_current() == '_')
    {
        char* text = malloc(256);
        int n = 0;
        text[n++] = lexer_current();

        while(isalnum(lexer_peek(1)) || lexer_peek(1) == '_')
        {
            lexer_consume();
            text[n++] = lexer_current();
        }
        text[n] = 0;

        if(!strcmp(text, "return"))
            return new_token(TOK_RETURN, 0);

        return new_token(TOK_IDENT, text);
    }
    if(isdigit(lexer_current()))
    {
        char* text = malloc(256);
        int n = 0;
        text[n++] = lexer_current();

        while(isdigit(lexer_peek(1)))
        {
            lexer_consume();
            text[n++] = lexer_current();
        }

        text[n] = 0;

        return new_token(TOK_INTEGER, text);
    }

    switch(lexer_current())
    {
        case '(':
            return new_token(TOK_LPAREN, NULL);
        case ')':
            return new_token(TOK_RPAREN, NULL);
        case '{':
            return new_token(TOK_LBRACE, NULL);
        case '}':
            return new_token(TOK_RBRACE, NULL);
        case ';':
            return new_token(TOK_SEMICOLON, NULL);
        default:
            printf("vcbc: unexpected token: %c", lexer_current());
            exit(EXIT_FAILURE);
    }
}