#include "../include/differentiator.h"
#include "../include/tree.h"

static TreeNodeData  node_data                = {};
static Tree         *static_p_tree_derivative = nullptr;

#define OPERATOR(op_name, op_sign, op_hash, code, optimization)   \
{                                                                 \
   case (op_hash):                                                \
   {                                                              \
      diff_##op_name(p_node_derivative, p_node_expression);       \
      break;                                                      \
   }                                                              \
}                                                                 \

static void
visitor(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression);

static void
copy_subtree(TreeNode *const p_distNode, const TreeNode *const p_srcNode)
{
   TreeNode *const p_node = tree_add_node(static_p_tree_derivative, &p_srcNode->data);

   if (p_srcNode->left != nullptr)
   {
      copy_subtree(p_node, p_srcNode->left);

      if (p_srcNode->right != nullptr)
         copy_subtree(p_node, p_srcNode->right);
   }

   tree_latinRelate(p_distNode, p_node);
}

static void
diff_plus(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232315; // +
   TreeNode *p_node_plus = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_plus);
   visitor(p_node_plus, p_node_expression->left);
   visitor(p_node_plus, p_node_expression->right);
}

static void
diff_minus(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232317; // -
   TreeNode *p_node_minus = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_minus);
   visitor(p_node_minus, p_node_expression->left);
   visitor(p_node_minus, p_node_expression->right);
}

static void
diff_multiply(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232315; // +
   TreeNode *p_node_plus = tree_add_node(static_p_tree_derivative, &node_data);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply_left = tree_add_node(static_p_tree_derivative, &node_data);
   
   visitor(p_node_multiply_left, p_node_expression->left);
   copy_subtree(p_node_multiply_left, p_node_expression->right);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply_right = tree_add_node(static_p_tree_derivative, &node_data);

   copy_subtree(p_node_multiply_right, p_node_expression->left);
   visitor(p_node_multiply_right, p_node_expression->right);

   tree_latinRelate(p_node_plus, p_node_multiply_left);
   tree_latinRelate(p_node_plus, p_node_multiply_right);
   tree_latinRelate(p_node_derivative, p_node_plus);
}

static void
diff_div(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232319; // /
   TreeNode *p_node_div = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_div);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232317; // -
   TreeNode *p_node_minus = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_div, p_node_minus);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply_left = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_minus, p_node_multiply_left);
   visitor(p_node_multiply_left, p_node_expression->left);
   copy_subtree(p_node_multiply_left, p_node_expression->right);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply_right = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_minus, p_node_multiply_right);
   copy_subtree(p_node_multiply_right, p_node_expression->left);
   visitor(p_node_multiply_right, p_node_expression->right);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232206; // ^
   TreeNode *p_node_power = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_div, p_node_power);
   copy_subtree(p_node_power, p_node_expression->right);

   node_data.type = TreeNodeType::TYPE_NUMBER;
   node_data.value.number = 2;
   TreeNode *p_node_number = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_power, p_node_number);
}

static void
diff_sin(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 244996264775408; // cos
   TreeNode *p_node_cos = tree_add_node(static_p_tree_derivative, &node_data);

   copy_subtree(p_node_cos, p_node_expression->left);
   tree_latinRelate(p_node_multiply, p_node_cos);

   visitor(p_node_multiply, p_node_expression->left);

   tree_latinRelate(p_node_derivative, p_node_multiply);
}

static void
diff_cos(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply_father = tree_add_node(static_p_tree_derivative, &node_data);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 244996263727133; // sin
   TreeNode *p_node_sin = tree_add_node(static_p_tree_derivative, &node_data);

   copy_subtree(p_node_sin, p_node_expression->left);
   tree_latinRelate(p_node_multiply_father, p_node_sin);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *const p_node_multiply_son = tree_add_node(static_p_tree_derivative, &node_data);

   node_data.type = TreeNodeType::TYPE_NUMBER;
   node_data.value.number = -1;
   TreeNode *p_node_number = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_multiply_son, p_node_number);
   visitor(p_node_multiply_son, p_node_expression->left);

   tree_latinRelate(p_node_multiply_father, p_node_multiply_son);
   tree_latinRelate(p_node_derivative, p_node_multiply_father);
}

static void
diff_ln(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_multiply);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232319; // /
   TreeNode *const p_node_div = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_multiply, p_node_div);

   node_data.type = TreeNodeType::TYPE_NUMBER;
   node_data.value.number = 1;
   TreeNode *p_node_number = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_div, p_node_number);
   copy_subtree(p_node_div, p_node_expression->left);

   visitor(p_node_multiply, p_node_expression->left);
}

static void
diff_power(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);
   
   tree_latinRelate(p_node_derivative, p_node_multiply);
   
   if (p_node_expression->right->data.type == TreeNodeType::TYPE_NUMBER
       || p_node_expression->right->data.type == TreeNodeType::TYPE_CONSTANT)
   {
      copy_subtree(p_node_multiply, p_node_expression->right);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232206; // ^
      TreeNode *p_node_power = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_multiply, p_node_power);
      copy_subtree(p_node_power, p_node_expression->left);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232317; // -;
      TreeNode *const p_node_minus = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_power, p_node_minus);
      copy_subtree(p_node_minus, p_node_expression->right);
      
      node_data.type = TreeNodeType::TYPE_NUMBER;
      node_data.value.number = 1;
      TreeNode *const p_node_number = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_minus, p_node_number);
   }
   else
   {
      copy_subtree(p_node_multiply, p_node_expression);
      
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232315; // +
      TreeNode *p_node_plus = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_multiply, p_node_plus);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232314; // *
      p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_plus, p_node_multiply);
      visitor(p_node_multiply, p_node_expression->left);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232319; // /
      TreeNode *const p_node_div = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_multiply, p_node_div);
      copy_subtree(p_node_div, p_node_expression->right);
      copy_subtree(p_node_div, p_node_expression->left);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 3738232314; // *
      p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_plus, p_node_multiply);
   
      node_data.type = TreeNodeType::TYPE_OP;
      node_data.value.op = 957002058891; // ln
      TreeNode *const p_node_ln = tree_add_node(static_p_tree_derivative, &node_data);
   
      tree_latinRelate(p_node_multiply, p_node_ln);
      copy_subtree(p_node_ln, p_node_expression->left);
   
      visitor(p_node_multiply, p_node_expression->right);
   }
}

static void
diff_sh(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_multiply);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 957002056589; // ch
   TreeNode *p_node_ch = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_multiply, p_node_ch);
   copy_subtree(p_node_ch, p_node_expression->left);

   visitor(p_node_multiply, p_node_expression->left);
}

static void
diff_ch(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 3738232314; // *
   TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_derivative, p_node_multiply);

   node_data.type = TreeNodeType::TYPE_OP;
   node_data.value.op = 957002052493; // sh
   TreeNode *p_node_sh = tree_add_node(static_p_tree_derivative, &node_data);

   tree_latinRelate(p_node_multiply, p_node_sh);
   copy_subtree(p_node_sh, p_node_expression->left);

   visitor(p_node_multiply, p_node_expression->left);
}

static void
visitor(TreeNode *const p_node_derivative, const TreeNode *const p_node_expression)
{
   switch (p_node_expression->data.type)
   {
      case TreeNodeType::TYPE_VARIABLE:
      {
         node_data.type = TreeNodeType::TYPE_NUMBER;
         node_data.value.number = 1;

         tree_latinRelate(p_node_derivative, tree_add_node(static_p_tree_derivative, &node_data));
         break;
      }

      case TreeNodeType::TYPE_CONSTANT:
      {
         node_data.type = TreeNodeType::TYPE_NUMBER;
         node_data.value.number = 0;

         tree_latinRelate(p_node_derivative, tree_add_node(static_p_tree_derivative, &node_data));
         break;
      }

      case TreeNodeType::TYPE_NUMBER:
      {
         node_data.type = TreeNodeType::TYPE_NUMBER;
         node_data.value.number = 0;

         tree_latinRelate(p_node_derivative, tree_add_node(static_p_tree_derivative, &node_data));
         break;
      }

      case TreeNodeType::TYPE_OP:
      {
         switch (p_node_expression->data.value.op)
         {
            #include "../operators.inc"

            default:
            {
               printf("I don't know this <%zu> operator hash.\n", p_node_expression->data.value.op);
               tree_destruct(static_p_tree_derivative);
               abort();
            }
         }

         break;
      }

      default:
      {
         printf("I don't know this <%zu> type of node.\n", p_node_expression->data.type);
         tree_destruct(static_p_tree_derivative);
         abort();
      }
   }
}

Tree*
differentiate(const Tree *const p_tree_expression)
{
   assert(p_tree_expression);

   static_p_tree_derivative = tree_construct();

   tree_add_node(static_p_tree_derivative);
   visitor(static_p_tree_derivative->root, p_tree_expression->root->left);
   
   return static_p_tree_derivative;
}