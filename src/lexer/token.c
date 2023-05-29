// Copyright 2023 solar-mist


#include <stdlib.h>
#include <lexer/token.h>

struct token* new_token(enum token_type type, char* text)
{
    struct token* ret = malloc(sizeof(struct token));
    ret->text = text;
    ret->type = type;
    ret->next = NULL;

    return ret;
}

char* token_type_to_string(enum token_type type)
{
    switch(type)
    {
        case TOK_IDENT:
            return "IDENT";
        case TOK_LPAREN:
            return "LPAREN";
        case TOK_RPAREN:
            return "RPAREN";
        case TOK_LBRACE:
            return "LBRACE";
        case TOK_RBRACE:
            return "RBRACE";
    }
    return "";
}