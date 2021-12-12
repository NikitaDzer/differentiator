#include "../include/tree.h"

typedef tree_error_t error_t;

static size_t N_ADD_NODES = 16;

error_t
tree_construct(Tree *const p_tree, const size_t capacity)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_tree == nullptr)
      return TREE_ERROR;
   
   if (capacity > TREE_MAX_CAPACITY)
      return TREE_ERROR;
   #endif // TREE_ANTI_FOOL
   
   TreeNode *const nodes = (TreeNode *)calloc(capacity, sizeof(TreeNode));
   
   if (nodes == nullptr)
      return TREE_ERROR;
   
   p_tree->capacity = capacity;
   p_tree->size     = 0;
   p_tree->root     = nodes;
   p_tree->free     = nodes;
   p_tree->final    = nodes + capacity - 1;
   
   return TREE_NO_ERROR;
}

void
tree_destruct(Tree *const p_tree)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_tree != nullptr)
   {
      while (p_tree->final->father != nullptr)
      {
         free(p_tree->final + 1 - N_ADD_NODES);
         p_tree->final = p_tree->final->father;
      }
      free(p_tree->root);
      
      p_tree->capacity = 0;
      p_tree->size     = 0;
      p_tree->root     = nullptr;
      p_tree->free     = nullptr;
      p_tree->final    = nullptr;
   }
   #else //  !TREE_ANTI_FOOL
   while (p_tree->final->father != nullptr)
   {
      free(p_tree->final + 1 - N_ADD_NODES);
      p_tree->final = p_tree->final->father;
   }
   free(p_tree->root);
   
   p_tree->capacity = 0;
   p_tree->size     = 0;
   p_tree->root     = nullptr;
   p_tree->free     = nullptr;
   p_tree->final    = nullptr;
   #endif // !TREE_ANTI_FOOL
}

TreeNode*
tree_fill_node(TreeNode *const p_node, const TreeNodeData *const p_data)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_node == nullptr || p_data == nullptr)
      return nullptr;
   #endif // TREE_ANTI_FOOL
   
   p_node->data = *p_data;
   
   return p_node;
}

TreeNode*
tree_add_node(Tree *const p_tree, const TreeNodeData *const p_data)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_tree == nullptr || p_data == nullptr)
      return nullptr;
   #endif // TREE_ANTI_FOOL
   
   if (p_tree->free + 1 == p_tree->final)
   {
      if (p_tree->capacity + N_ADD_NODES > TREE_MAX_CAPACITY)
         return nullptr;
      
      TreeNode *const p_allocated = (TreeNode *)calloc(N_ADD_NODES, sizeof(TreeNode));
      TreeNode *const p_prevFinal = p_tree->final;
      
      assert(p_allocated);
      
      p_tree->capacity      += N_ADD_NODES;
      p_tree->free           = p_allocated;
      p_tree->final          = p_allocated + N_ADD_NODES - 1;
      p_tree->final->father  = p_prevFinal;
   }
   
   tree_fill_node(p_tree->free, p_data);
   p_tree->size += 1;
   p_tree->free += 1;
   
   return p_tree->free - 1;
}

TreeNode*
tree_relate_nodes(TreeNode *const p_father, TreeNode **const p_father_son, TreeNode *const p_son)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_father == nullptr || p_father_son == nullptr || p_son == nullptr)
      return nullptr;
   #endif // TREE_ANTI_FOOL
   
  *p_father_son  = p_son;
   p_son->father = p_father;
   
   return p_son;
}

TreeNode*
tree_latinRelate(TreeNode *const p_father, TreeNode *const p_son)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_father == nullptr || p_son == nullptr)
      return nullptr;
   #endif // TREE_ANTI_FOOL
   
   if (p_father->left == nullptr)
      p_father->left = p_son;
   else if (p_father->right == nullptr)
      p_father->right = p_son;
   else
      return nullptr;
   
   p_son->father = p_father;
   
   return p_son;
}