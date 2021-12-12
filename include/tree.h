#ifndef DIFFERENTIATOR_TREE_H
#define DIFFERENTIATOR_TREE_H

#include "config.h"

enum TreeNodeType
{
   TYPE_VARIABLE = 1,
   TYPE_CONSTANT = 2,
   TYPE_NUMBER   = 3,
   TYPE_OP       = 4,
};

struct TreeNodeData
{
   union Value
   {
      char   variable;
      char   constant;
      double number;
      size_t op;
   } value;
   
   TreeNodeType type;
};

struct TreeNode
{
   TreeNode *father;
   TreeNode *left;
   TreeNode *right;
   
   TreeNodeData data;
};

struct Tree
{
   size_t    capacity;
   size_t    size;
   
   TreeNode *root;
   TreeNode *free;
   TreeNode *final;
};

const tree_error_t TREE_NO_ERROR =  0;
const tree_error_t TREE_ERROR    = -1;

const TreeNodeData TREE_NODE_DEFAULT_DATA = {
        .value = { .op = 0 },
        .type  = TYPE_OP,
};

tree_error_t
tree_construct(Tree *const p_tree, const size_t capacity = TREE_NODES_DEFAULT_NUMBER);

void
tree_destruct(Tree *const p_tree);

TreeNode*
tree_fill_node(TreeNode *const p_node, const TreeNodeData *const p_data);

TreeNode*
tree_add_node(Tree *const p_tree, const TreeNodeData *const p_data = &TREE_NODE_DEFAULT_DATA);

TreeNode*
tree_relate_nodes(TreeNode *const p_father, TreeNode **const p_father_son, TreeNode *const p_son);

TreeNode*
tree_latinRelate(TreeNode *const p_father, TreeNode *const p_son);

#endif //DIFFERENTIATOR_TREE_H
