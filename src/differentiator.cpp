#include "../include/differentiator.h"
#include "../include/tree.h"

static TreeNodeData  node_data                = {};
static const Tree   *static_p_tree_expression = nullptr;
static Tree         *static_p_tree_derivative = nullptr;

#define OPERATOR(op_name, op_hash, code)        \
{                                               \
   case (op_hash):                              \
   {                                            \
      (code);                                   \
      break;                                    \
   }                                            \
}                                               \

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

void
differentiate(Tree *const p_tree_derivative, const Tree *const p_tree_expression)
{
   assert(p_tree_derivative);
   assert(p_tree_expression);
   
   static_p_tree_derivative = p_tree_derivative;
   static_p_tree_expression = p_tree_expression;
   
   tree_add_node(p_tree_derivative);
   
   visitor(p_tree_derivative->root, p_tree_expression->root->left);
}