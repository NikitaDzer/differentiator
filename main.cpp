#include <cstdio>
#include "include/tree.h"
#include "include/parser.h"
#include "include/dump.h"
#include "include/differentiator.h"

static long
get_file_size(FILE *const file)
{
   assert(file);
   
   long position = ftell(file);
   long size     = 0;
   
   fseek(file, 0L, SEEK_END);
   size = ftell(file);
   fseek(file, position, SEEK_SET);
   
   return size;
}

int main()
{
   FILE *const file = fopen("expression.exp", "r");
   size_t      file_size = get_file_size(file);
   char *const expression = (char *)calloc(file_size, sizeof(char));
   
   fread(expression, sizeof(char), file_size, file);
   
   Tree tree_expression = {};
   Tree tree_derivative = {};
   tree_construct(&tree_expression);
   tree_construct(&tree_derivative);
   
   parse(expression, &tree_expression);
   
   differentiate(&tree_derivative, &tree_expression);
   
   tree_dump(&tree_expression);
   tree_dump(&tree_derivative);
   
   tree_destruct(&tree_expression);
   tree_destruct(&tree_derivative);
   
   free(expression);
   fclose(file);
   
   return 0;
}
