#include "../include/optimizer.h"
#include "../include/dump.h"
#include <cmath>

static bool was_optimized = false;

#define OPERATOR(op_name, op_sign, op_hash, code, optimization)         \
{                                                                       \
   case (op_hash):                                                      \
   {                                                                    \
      optimize_##op_name(p_father, p_node);                             \
      break;                                                            \
   }                                                                    \
}                                                                       \

static void
visitor(TreeNode *const p_father, TreeNode *const p_node);

static void
optimize_plus(TreeNode *const p_father, TreeNode *const p_node)
{
   
   TreeNodeData *const p_leftSon_data = &p_node->left->data;
   TreeNodeData *const p_rightSon_data = &p_node->right->data;

   if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
   {
      tree_relate(p_father,
                  p_node->right,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
   {
      tree_relate(p_father,
                  p_node->left,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->type == TreeNodeType::TYPE_NUMBER)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = p_leftSon_data->value.number + p_rightSon_data->value.number;

      was_optimized = true;
   }
   else if ((p_leftSon_data->type == TreeNodeType::TYPE_VARIABLE && p_rightSon_data->type == TreeNodeType::TYPE_VARIABLE)
            ||
            (p_leftSon_data->type == TreeNodeType::TYPE_CONSTANT
             && p_rightSon_data->type == TreeNodeType::TYPE_CONSTANT
             && p_leftSon_data->value.constant == p_rightSon_data->value.constant))
   {
      p_node->data.type = TreeNodeType::TYPE_OP;
      p_node->data.value.op = 3738232314; // *

      p_leftSon_data->type = TreeNodeType::TYPE_NUMBER;
      p_leftSon_data->value.number = 2;

      was_optimized = true;
   }
   else
   {
      if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->left);

      if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->right);
   }
}

static void
optimize_minus(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_leftSon_data = &p_node->left->data;
   TreeNodeData *const p_rightSon_data = &p_node->right->data;

   if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
   {
      tree_relate(p_father,
                  p_node->left,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);
      
      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->type == TreeNodeType::TYPE_NUMBER)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = p_leftSon_data->value.number - p_rightSon_data->value.number;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
   {
      p_node->data.type = TreeNodeType::TYPE_OP;
      p_node->data.value.op = 3738232314; // *

      p_leftSon_data->type = TreeNodeType::TYPE_NUMBER;
      p_leftSon_data->value.number = -1;

      was_optimized = true;
   }
   else if ((p_leftSon_data->type == TreeNodeType::TYPE_VARIABLE && p_rightSon_data->type == TreeNodeType::TYPE_VARIABLE)
            ||
            (p_leftSon_data->type == TreeNodeType::TYPE_CONSTANT
             && p_rightSon_data->type == TreeNodeType::TYPE_CONSTANT
             && p_leftSon_data->value.constant == p_rightSon_data->value.constant))
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 0;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else
   {
      if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->left);

      if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->right);
   }
}

static void
optimize_multiply(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_leftSon_data = &p_node->left->data;
   TreeNodeData *const p_rightSon_data = &p_node->right->data;

   if ((p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
       ||
       (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0))
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 0;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->type == TreeNodeType::TYPE_NUMBER)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = p_leftSon_data->value.number * p_rightSon_data->value.number;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 1)
   {
      tree_relate(p_father,
                  p_node->right,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 1)
   {
      tree_relate(p_father,
                  p_node->left,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else
   {
      if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->left);

      if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->right);
   }
}

static void
optimize_power(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_leftSon_data = &p_node->left->data;
   TreeNodeData *const p_rightSon_data = &p_node->right->data;

   if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
   {
      printf("Raising a zero to a power. Ban!");
      abort();
   }

   if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->type == TreeNodeType::TYPE_NUMBER)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = pow(p_leftSon_data->value.number, p_rightSon_data->value.number);

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 1;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 1)
   {
      tree_relate(p_father,
                  p_node->left,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else
   {
      if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->left);

      if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->right);
   }
}

static void
optimize_sin(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_son_data = &p_node->left->data;

   if (p_son_data->type == TreeNodeType::TYPE_NUMBER && p_son_data->value.number == 0)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 0;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_son_data->type == TreeNodeType::TYPE_OP)
      visitor(p_node, p_node->left);
}

static void
optimize_cos(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_son_data = &p_node->left->data;

   if (p_son_data->type == TreeNodeType::TYPE_NUMBER && p_son_data->value.number == 0)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 1;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_son_data->type == TreeNodeType::TYPE_OP)
      visitor(p_node, p_node->left);
}

static void
optimize_div(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_leftSon_data = &p_node->left->data;
   TreeNodeData *const p_rightSon_data = &p_node->right->data;

   if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
   {
      printf("Division by zero. Ban!\n");
      abort();
   }

   if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 0;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->type == TreeNodeType::TYPE_NUMBER)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = p_leftSon_data->value.number / p_rightSon_data->value.number;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 1)
   {
      tree_relate(p_father,
                  p_node->left,
                  p_father->left == p_node
                  ? &p_father->left
                  : &p_father->right);

      was_optimized = true;
   }
   else if ((p_leftSon_data->type == TreeNodeType::TYPE_VARIABLE && p_rightSon_data->type == TreeNodeType::TYPE_VARIABLE)
            || (p_leftSon_data->type == TreeNodeType::TYPE_CONSTANT && p_rightSon_data->type == TreeNodeType::TYPE_CONSTANT))
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 1;
      
      p_node->left  = nullptr;
      p_node->right = nullptr;
   
      was_optimized = true;
   }
   else
   {
      if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->left);

      if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
         visitor(p_node, p_node->right);
   }
}

static void
optimize_ln(TreeNode *const p_father, TreeNode *const p_node)
{
   TreeNodeData *const p_son_data = &p_node->left->data;

   if (p_son_data->type == TreeNodeType::TYPE_NUMBER && p_son_data->value.number <= 0)
   {
      printf("Taking <ln> of <%lg>. Ban!\n", p_son_data->value.number);
      abort();
   }

   if (p_son_data->type == TreeNodeType::TYPE_NUMBER && p_son_data->value.number == 1)
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 0;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_son_data->type == TreeNodeType::TYPE_CONSTANT && p_son_data->value.constant == 'e')
   {
      p_node->data.type = TreeNodeType::TYPE_NUMBER;
      p_node->data.value.number = 1;

      p_node->left  = nullptr;
      p_node->right = nullptr;

      was_optimized = true;
   }
   else if (p_son_data->type == TreeNodeType::TYPE_OP)
      visitor(p_node, p_node->left);
}

static void
optimize_sh(TreeNode *const p_father, TreeNode *const p_node)
{

}

static void
optimize_ch(TreeNode *const p_father, TreeNode *const p_node)
{

}

static void
visitor(TreeNode *const p_father, TreeNode *const p_node)
{
   assert(p_node);

   switch (p_node->data.value.op)
   {
      #include "../operators.inc"

      default:
      {
         printf("I don't know this <%zu> operator hash.\n", p_node->data.value.op);
         abort();
      }
   }
}

void
optimize(Tree *const p_tree_derivative)
{
   assert(p_tree_derivative);

   do
   {
      was_optimized = false;
      
      if (p_tree_derivative->root->left->data.type == TreeNodeType::TYPE_OP)
         visitor(p_tree_derivative->root, p_tree_derivative->root->left);
      
   } while (was_optimized);
}