// Copyright 2023 solar-mist


#include "lexer/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <parser/parser.h>

struct token* curr;
bool bypass = false;

struct ast_node* add_node(struct ast_node* nodes, struct ast_node* node);
struct token* parser_current();
void expect_token(enum token_type type);
struct ast_node* parse_expression();

struct ast_node* parser_parse(struct token* tokens)
{
    struct ast_node* nodes = NULL;
    curr = tokens;

    while(parser_current())
    {
        nodes = add_node(nodes, parse_expression());
        expect_token(TOK_SEMICOLON);
    }

    return nodes;
}

struct token* parser_current()
{
    return curr;
}

struct token* parser_consume()
{
    struct token* ret = curr;
    curr = curr->next;
    return ret;
}

struct token* parser_peek(int off)
{
    struct token* ret = curr;
    while(off--)
        ret = ret->next;
    return ret;
}

void expect_token(enum token_type type)
{
    if(bypass)
        bypass = false;
    else if(parser_current()->type != type)
    {
        printf("Expected: %s. Found: %s", token_type_to_string(parser_current()->type), token_type_to_string(type));
        exit(EXIT_FAILURE);
    }
}

struct ast_node* add_node(struct ast_node* nodes, struct ast_node* node)
{
    if(!node)
        return nodes;

    if(!nodes)
    {
        nodes = node;
        return nodes;
    }

    struct ast_node* c = nodes;
    while(c->next)
        c = c->next;

    c->next = node;
    return nodes;
}

struct ast_node* parse_func_def()
{
    __attribute((unused)) char* type = parser_consume()->text;

    expect_token(TOK_IDENT);
    char* name = parser_consume()->text;

    // LPAREN already checked
    parser_consume();

    // TODO: Parse arguments

    expect_token(TOK_RPAREN);
    parser_consume();

    expect_token(TOK_LBRACE);
    parser_consume();

    // TODO: Parse body

    expect_token(TOK_RBRACE);
    parser_consume();

    bypass = true; // skip check for semicolon

    union ast_node_value value;
    value.func.name = name;

    return new_ast_node(AST_FUNC_DEF, value, NULL, 0);
}

struct ast_node* parse_primary()
{
    switch(parser_current()->type)
    {
        case TOK_IDENT:
        {
            if(parser_peek(2)->type == TOK_LPAREN)
                return parse_func_def();
        }
        default:
            printf("Expected primary expression. Found %s", token_type_to_string(parser_current()->type));
            exit(EXIT_FAILURE);
    }
}

struct ast_node* parse_expression()
{
    return parse_primary();
}