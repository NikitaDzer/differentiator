#ifndef DIFFERENTIATOR_PARSER_H
#define DIFFERENTIATOR_PARSER_H

#include "tree.h"

const char EXPRESSION_FILE_PATH[] = "expression.exp";

Tree*
get_expression_tree(const char *const expression_file_path = EXPRESSION_FILE_PATH);
#endif // DIFFERENTIATOR_PARSER_H
