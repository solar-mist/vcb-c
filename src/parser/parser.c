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
struct token* parser_consume();
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
        if(!bypass)
            parser_consume();
        else
            bypass = false;
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
    if(!bypass)
        if(parser_current()->type != type)
        {
            printf("Expected: %s. Found: %s", token_type_to_string(type), token_type_to_string(parser_current()->type));
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

    struct ast_node* children = NULL;


    while(parser_current()->type != TOK_RBRACE)
    {
        children = add_node(children, parse_expression());
        expect_token(TOK_SEMICOLON);
        parser_consume();
    }
    parser_consume();

    bypass = true; // skip check for semicolon

    union ast_node_value value;
    value.func.name = name;

    return new_ast_node(AST_FUNC_DEF, value, children);
}

struct ast_node* parse_integer_literal()
{
    union ast_node_value value;
    value.integer.text = parser_consume()->text;
    
    return new_ast_node(AST_INTEGER, value, NULL);
}

struct ast_node* parse_return_statement()
{
    parser_consume();
    struct ast_node* retval = parse_expression();

    return new_ast_node(AST_RETURN, (union ast_node_value){}, retval);
}

struct ast_node* parse_primary()
{
    switch(parser_current()->type)
    {
        case TOK_INTEGER:
        {
            return parse_integer_literal();
        }
        case TOK_RETURN:
        {
            return parse_return_statement();
        }
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