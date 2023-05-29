// Copyright 2023 solar-mist


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <lexer/lexer.h>

static int position = 0;
char* file;

char current();
char consume();
struct token* add_token(struct token* arr, struct token* tok);
struct token* lexer_next();

struct token* lexer_lex(char* buffer)
{
    struct token* tokens = NULL;
    file = buffer;
    while(current() != EOF)
    {
        tokens = add_token(tokens, lexer_next());
        consume();
    }
    return tokens;
}


char current()
{
    return file[position];
}

char consume()
{
    return file[position++];
}

char peek(int off)
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
    while(isspace(current()))
        consume();
    
    if(isalpha(current()) || current() == '_')
    {
        char* text = malloc(256);
        int n = 0;
        text[n++] = current();

        while(isalnum(peek(1)) || peek(1) == '_')
        {
            consume();
            text[n++] = current();
        }
        text[n] = 0;

        return new_token(TOK_IDENT, text);
    }

    switch(current())
    {
        case '(':
            return new_token(TOK_LPAREN, NULL);
        case ')':
            return new_token(TOK_RPAREN, NULL);
        case '{':
            return new_token(TOK_LBRACE, NULL);
        case '}':
            return new_token(TOK_RBRACE, NULL);
        default:
            printf("vcbc: unexpected token: %c", current());
            exit(EXIT_FAILURE);
    }
}