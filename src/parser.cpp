#include "../include/parser.h"
#include "../include/hash.h"

static const hash_t  HASH_VARIABLE     = 3738232232; // hash of variable 'x'

static TreeNodeData  node_data         = {};
static const char   *data_end          = nullptr;
static char         *trimmedExpression = nullptr;

static Tree         *static_p_tree     = nullptr;
static TreeNode     *static_p_node     = nullptr;

#define OPERATOR(op_name, op_sign, op_hash, code, optimization)       \
      case (op_hash):                                                 \
      {                                                               \
         node_data.type     = TYPE_OP;                                \
         node_data.value.op = (op_hash);                              \
                                                                      \
         break;                                                       \
      }                                                               \
      

[[noreturn]] static void
NORETURN_bad_constant(const char *const start, const char *const end)
{
   printf("Cannot create variable <");
   
   for (const char *iterator = start; iterator <= end; iterator++)
      printf("%c", *iterator);
   
   printf(">!\n"
          "Only single character names for variable are available.\n");
   
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_bad_operands_number(const char *const pointer)
{
   printf("Trying to use more than 2 operands at <%zu> position.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_bad_function()
{
   printf("Bad function.\n");
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_no_operand(const char *const pointer)
{
   printf("No operand at <%zu> position.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_operand_after_number(const char *const pointer)
{
   printf("Operand after number at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_operand_after_variable(const char *const pointer)
{
   printf("Operand after variable at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_operand_after_constant(const char *const pointer)
{
   printf("Operand after constant at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_no_operator(const char *const pointer)
{
   printf("No operator at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_many_close_n_braces(const char *const pointer)
{
   printf("Excess close brace at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_few_close_n_braces(const char *const pointer)
{
   printf("Not enough close brace at <%zu>.\n", pointer - trimmedExpression);
   tree_destruct(static_p_tree);
   abort();
}

[[noreturn]] static void
NORETURN_bad_expression()
{
   printf("No expression to differentiate.\n");
   tree_destruct(static_p_tree);
   abort();
}

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

static const char*
get_expression(const char *const expression_file_path)
{
   size_t  expression_file_size = 0;
   FILE   *expression_file      = nullptr;
   char   *expression           = nullptr;
   
   expression_file = fopen(expression_file_path, "r");
   assert(expression_file);
   
   expression_file_size = get_file_size(expression_file);
   expression           = (char *)calloc(expression_file_size, sizeof(char));
   assert(expression);
   
   fread(expression, sizeof(char), expression_file_size, expression_file);
   assert(fclose(expression_file) == 0);
   
   return expression;
}

static void
trim_expression(const char *const expression)
{
   const size_t  expression_len             = strlen(expression);
   const char   *expression_iterator        = expression;
   char         *trimmedExpression_iterator = nullptr;
   
   trimmedExpression = (char *)calloc(expression_len + 1, sizeof(char));
   trimmedExpression_iterator = trimmedExpression;
   
   for (; expression_iterator < expression + expression_len; expression_iterator++)
      if (*expression_iterator != ' ')
      {
         *trimmedExpression_iterator = *expression_iterator;
         trimmedExpression_iterator += 1;
      }
   
   *trimmedExpression_iterator = '\0';
}

static void
validate_expression(const char *const expression)
{
   const size_t expression_len = strlen(expression);
   size_t       braces_counter = 0;
   bool         was_data        = false;
   
   for (const char *iterator = expression; iterator < expression + expression_len; iterator++)
   {
      if (*iterator == '(')
         braces_counter += 1;
      else if (*iterator == ')')
         braces_counter -= 1;
      else
         was_data = true;
      
      if (braces_counter == -1)
         NORETURN_many_close_n_braces(iterator);
   }
   
   if (braces_counter != 0)
      NORETURN_few_close_n_braces(expression + expression_len);
   
   if (!was_data)
      NORETURN_bad_expression();
}

static const char*
get_data_end(const char *const start)
{
   const char *iterator = start;
   
   while (*iterator != '\0')
   {
      if (*iterator == '(' || *iterator == ')')
         return iterator - 1;
      
      iterator += 1;
   }
   
   NORETURN_no_operand(start);
}

static const char*
fill_node_data(const char *const start)
{
   data_end = get_data_end(start);
   
   if (sscanf(start, "%lf", &node_data.value.number))
   {
      node_data.type = TreeNodeType::TYPE_NUMBER;
      
      if (*(data_end + 1) == '(')
         NORETURN_operand_after_number(data_end + 1);
   }
   else
      switch (qhash(start, data_end - start + 1))
      {
         #include "../operators.inc"
       
         case HASH_VARIABLE:
         {
            if (*(data_end + 1) == '(')
               NORETURN_operand_after_variable(data_end + 1);
            
            node_data.type = TreeNodeType::TYPE_VARIABLE;
            node_data.value.variable = *start;
            
            break;
         }
      
         default:
         {
            if (data_end - start >= 1)
               NORETURN_bad_constant(start, data_end);
            
            if (*(data_end + 1) == '(')
               NORETURN_operand_after_constant(data_end + 1);
            
            node_data.type = TreeNodeType::TYPE_CONSTANT;
            node_data.value.constant = *start;
            
            break;
         }
   }
   
   tree_fill_node(static_p_node, &node_data);
   
   return data_end + 1;
}

static const char*
visitor(TreeNode *const father, const char *const start)
{
   if (*start != '(')
      NORETURN_bad_function();
   
   static_p_node = tree_add_node(static_p_tree);
   assert(static_p_node);
   
   if (father != nullptr)
   {
   
   }
      if (tree_latinRelate(father, static_p_node) == nullptr)
         NORETURN_bad_operands_number(start);
   
   const char *iterator = start + 1;
   
   while (true)
   {
      if (*iterator == '(')
         iterator = visitor(static_p_node, iterator);
      else if (*iterator != ')')
         iterator = fill_node_data(iterator);
   
      if (*iterator == ')')
      {
         if (static_p_node->left != nullptr
             && (static_p_node->data.type == TreeNodeType::TYPE_VARIABLE
                 || static_p_node->data.type == TreeNodeType::TYPE_CONSTANT))
            NORETURN_no_operator(start);
   
         if (static_p_node->left == nullptr && static_p_node->data.type == TreeNodeType::TYPE_OP)
            NORETURN_no_operand(start);
         
         static_p_node = father;
         return iterator + 1;
      }
   }
}

static void
parse(const char *const expression)
{
   assert(expression);
   
   trim_expression(expression);
   validate_expression(trimmedExpression);
   
   tree_add_node(static_p_tree);
   visitor(static_p_tree->root, trimmedExpression);
   
   free(trimmedExpression);
}

Tree*
get_expression_tree(const char *const expression_file_path)
{
   const char *const expression = get_expression(expression_file_path);
   
   static_p_tree = tree_construct();
   parse(expression);
   free((void *)expression);
   
   return static_p_tree;
}