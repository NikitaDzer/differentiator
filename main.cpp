#include <cstdio>
#include <ctime>
#include "include/tree.h"
#include "include/parser.h"
#include "include/dump.h"
#include "include/differentiator.h"
#include "include/optimizer.h"
#include "include/tex.h"


int
main()
{
   size_t   derivative_order = 0;
   Tree   **trees            = nullptr;
   
   printf("Derivative order: ");
   scanf("%zu", &derivative_order);
   
   trees = (Tree **)calloc(derivative_order + 1, sizeof(Tree *));
   assert(trees);
   
   trees[0] = get_expression_tree();
   tex(trees[0], 0);
   
   optimize(trees[0]);
   tex(trees[0], 0);
   
   for (size_t i = 1; i <= derivative_order; i++)
   {
      trees[i] = differentiate(trees[i - 1]);
      optimize(trees[i]);
      tex(trees[i], i);
   }
   show_texfile();
   
   for (size_t i = 0; i < derivative_order + 1; i++)
   {
      tree_dump(trees[i]);
      tree_destruct(trees[i]);
   }
   free(trees);
   
   return 0;
}
