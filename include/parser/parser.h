// Copyright 2023 solar-mist


#ifndef VCBC_PARSER_PARSER_H
#define VCBC_PARSER_PARSER_H 1
#include <parser/ast.h>
#include <lexer/token.h>

struct ast_node* parser_parse(struct token* tokens);

#endif // VCBC_PARSER_PARSER_H