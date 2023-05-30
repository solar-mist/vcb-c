// Copyright 2023 solar-mist


#include <string.h>
#include <backend/backend.h>

void backend_emit(FILE* file, struct ast_node* node);

void backend_generate(struct ast_node* ast, FILE* file)
{
    struct ast_node* current = ast;
    while(current)
    {
        backend_emit(file, current);
        current = current->next;
    }
}

void writef(FILE* file, char* s)
{
    fwrite(s, strlen(s), 1, file);
}

void backend_emit_func_def(FILE* file, struct ast_node* node)
{
    writef(file, "@ ");
    writef(file, node->value.func.name);
    struct ast_node* current = node->children;
    while(current)
    {
        backend_emit(file, current);
        current = current->next;
    }
}

void backend_emit_return(FILE* file, struct ast_node* node)
{
    backend_emit(file, node->children);
    writef(file, "\n\tret");
}

void backend_emit_integer_literal(FILE* file, struct ast_node* node)
{
    writef(file, "\n\tlia "); // TODO: Properly emit immediates, registers etc
    writef(file, node->value.integer.text);
}

void backend_emit(FILE* file, struct ast_node* node)
{
    switch(node->type)
    {
        case AST_FUNC_DEF:
            backend_emit_func_def(file, node);
            break;
        case AST_RETURN:
            backend_emit_return(file, node);
            break;
        case AST_INTEGER:
            backend_emit_integer_literal(file, node);
            break;
    }
}