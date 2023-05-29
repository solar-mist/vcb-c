// Copyright 2023 solar-mist


#include "parser/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <lexer/lexer.h>
#include <parser/parser.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("vcbc: no input files");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    long fsz = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* buffer = malloc(fsz + 1);
    fread(buffer, fsz, 1, file);
    fclose(file);

    buffer[fsz] = EOF;

    struct token* tokens = lexer_lex(buffer);

    struct ast_node* ast = parser_parse(tokens);

    struct ast_node* curr = ast;
    while(curr)
    {
        print_ast_node(curr);
        curr = curr->next;
    }
    fflush(stdout);
}