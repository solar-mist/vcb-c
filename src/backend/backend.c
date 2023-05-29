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

void backend_emit_func_def(FILE* file, struct ast_node* node)
{
    fwrite("@ ", 2, 1, file);
    fwrite(node->value.func.name, strlen(node->value.func.name), 1, file);
    fwrite("\n\tret\n\n", 7, 1, file);
}

void backend_emit(FILE* file, struct ast_node* node)
{
    switch(node->type)
    {
        case AST_FUNC_DEF:
            backend_emit_func_def(file, node);
            break;
    }
}