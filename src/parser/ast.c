// Copyright 2023 solar-mist


#include <stdio.h>
#include <stdlib.h>
#include <parser/ast.h>

struct ast_node* new_ast_node(enum ast_type type, union ast_node_value value, struct ast_node* children)
{
    struct ast_node* ret = malloc(sizeof(struct ast_node));
    ret->type = type;
    ret->value = value;
    ret->children = children;

    return ret;
}

void print_ast_node(struct ast_node* node)
{
    switch(node->type)
    {
        case AST_FUNC_DEF:
            printf("Function:\n\tName: %s\n", node->value.func.name);
            break;
        case AST_RETURN:
            printf("Return:\n\tValue: ");
            print_ast_node(node->children);
            break;
        case AST_INTEGER:
            printf("%s", node->value.integer.text);
            break;
    }
}