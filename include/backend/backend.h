// Copyright 2023 solar-mist


#ifndef VCBC_BACKEND_BACKEND_H
#define VCBC_BACKEND_BACKEND_H 1
#include <stdio.h>
#include <parser/ast.h>

void backend_generate(struct ast_node* ast, FILE* file);

#endif // VCBC_BACKEND_BACKEND_H