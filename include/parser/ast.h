// Copyright 2023 solar-mist


#ifndef VCBC_PARSER_AST_H
#define VCBC_PARSER_AST_H 1

enum ast_type
{
    AST_FUNC_DEF,
    AST_RETURN,
    AST_INTEGER
};

union ast_node_value
{
    struct ast_node_func {
        char* name;
    } func;

    struct ast_node_integer {
        char* text;
    } integer;
};

struct ast_node
{
    enum ast_type type;
    union ast_node_value value;
    struct ast_node* children;
    struct ast_node* next;
};

struct ast_node* new_ast_node(enum ast_type type, union ast_node_value value, struct ast_node* children);

void print_ast_node(struct ast_node* node);

#endif // VCBC_PARSER_AST_H