#include <cstdarg>
#include "../include/tree.h"

typedef tree_bitmask_t bitmask_t;

static const size_t NUM_ADD_NODES = 128;

static inline bitmask_t*
control_bitmask(bitmask_t *const p_bitmask, const TreeError error_1 = PLUG, const TreeError error_2 = PLUG)
{
   if (p_bitmask == nullptr)
      return nullptr;
   
  *p_bitmask |= error_1 | error_2;
   return p_bitmask;
}

Tree*
tree_construct(const size_t initialCapacity, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (initialCapacity > TREE_MAX_CAPACITY || initialCapacity < 2)
   {
      control_bitmask(p_bitmask, BAD_CAPACITY, BAD_ARGUMENTS);
      return nullptr;
   }
   #endif // TREE_ANTI_FOOL
   
    /// ?Maybe malloc and memset
//   Tree     *const  p_tree   = (Tree *)malloc(sizeof(Tree) * 1 + sizeof(TreeNode) * initialCapacity);
//   TreeNode *const  nodes  = (TreeNode *)(p_tree + 1);
//   memset(p_tree, 0x0, sizeof(Tree) * 1 + sizeof(TreeNode) * initialCapacity);

   Tree     *const p_tree = (Tree *)calloc(1, sizeof(Tree));
   TreeNode *const nodes  = (TreeNode *)calloc(initialCapacity, sizeof(TreeNode));
   
   if (p_tree == nullptr || nodes == nullptr)
   {
      control_bitmask(p_bitmask, BAD_ALLOC);
      return nullptr;
   }
   
   p_tree->capacity = initialCapacity;
   p_tree->free     = nodes;
   p_tree->root     = nodes;
   p_tree->final    = nodes + initialCapacity - 1;
   
   p_tree->final->left  = nodes;
   p_tree->final->right = nullptr;
   
   return p_tree;
}

void
tree_destruct(Tree *const p_tree, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_tree == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_TREE, BAD_ARGUMENTS);
      return;
   }
   #endif // TREE_ANTI_FOOL
   
   if (p_tree->final->right != nullptr)
   {
      TreeNode *subfinal = p_tree->final->right;
      TreeNode *temp     = nullptr;
   
      while (true)
      {
         if (subfinal->right == nullptr)
         {
            free(subfinal->left);
            break;
         }
         
         temp = subfinal->right;
         free(subfinal->left);
         subfinal = temp;
      }
   }
   else
      free(p_tree->root);
   
   free(p_tree);
}

TreeNode*
tree_add_node(Tree *const p_tree, const TreeNodeData *const p_data, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_tree == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_TREE, BAD_ARGUMENTS);
      return nullptr;
   }
   
   if (p_data == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_DATA, BAD_ARGUMENTS);
      return nullptr;
   }
   #endif // TREE_ANTI_FOOL
   
   if (p_tree->capacity == TREE_MAX_CAPACITY)
      return nullptr;
   
   if (p_tree->free == p_tree->final)
   {
      TreeNode *section      = nullptr;
      TreeNode *final        = nullptr;
      size_t    section_size = 0;
      
      if (p_tree->capacity + NUM_ADD_NODES > TREE_MAX_CAPACITY)
         section_size = TREE_MAX_CAPACITY - p_tree->capacity;
      else
         section_size = NUM_ADD_NODES;
      
      section = (TreeNode *)calloc(section_size, sizeof(TreeNode));
      if (section == nullptr)
      {
         control_bitmask(p_bitmask, BAD_ALLOC);
         return nullptr;
      }
      
      final        = (TreeNode *)section + section_size - 1;
      final->left  = section;
      final->right = p_tree->final;
   
      p_tree->capacity += section_size;
      p_tree->free      = section;
      p_tree->final     = final;
   }
   
   tree_fill_node(p_tree->free, p_data);
   p_tree->free += 1;
   
   return p_tree->free - 1;
}

TreeNode*
tree_relate(TreeNode *const p_father, TreeNode *const p_son, TreeNode **const p_relation, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_father == nullptr || p_son == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_NODE, BAD_ARGUMENTS);
      return nullptr;
   }
   
   if (p_relation == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_RELATION, BAD_ARGUMENTS);
      return nullptr;
   }
   #endif // TREE_ANTI_FOOL
   
  *p_relation = p_son;
   return p_son;
}

TreeNode*
tree_latinRelate(TreeNode *const p_father, TreeNode *const p_son, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_father == nullptr || p_son == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_NODE, BAD_ARGUMENTS);
      return nullptr;
   }
   #endif // TREE_ANTI_FOOL
   
   if (p_father->left == nullptr)
      p_father->left = p_son;
   else if (p_father->right == nullptr)
      p_father->right = p_son;
   else
   {
      control_bitmask(p_bitmask, BOUND_RELATIONS);
      return nullptr;
   }
   
   return p_son;
}

TreeNode*
tree_fill_node(TreeNode *const p_node, const TreeNodeData *const p_data, bitmask_t *const p_bitmask)
{
   #ifdef    TREE_ANTI_FOOL
   if (p_node == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_TREE, BAD_ARGUMENTS);
      return nullptr;
   }
   
   if (p_data == nullptr)
   {
      control_bitmask(p_bitmask, BAD_PTR_DATA, BAD_ARGUMENTS);
      return nullptr;
   }
   #endif // TREE_ANTI_FOOL
   
   p_node->data = *p_data;
   
   return p_node;
}

void
tree_parse_bitmask(const bitmask_t bitmask)
{
   if (bitmask == PLUG)
   {
      printf("Tree bitmask is clean.\n");
      return;
   }
   
   size_t    counter     = 1;
   bitmask_t copyBitmask = bitmask;
   
   printf("Maybe fix this problems?\n"
          "------------------------\n");
   
   while (copyBitmask != PLUG)
   {
      if (copyBitmask & BAD_ALLOC)
      {
         printf("%zu: Memory wasn't allocated.\n", counter);
         copyBitmask &= ~BAD_ALLOC;
      }
      else if (copyBitmask & BAD_ARGUMENTS)
      {
         printf("%zu: Bad arguments were put in function.\n", counter);
         copyBitmask &= ~BAD_ARGUMENTS;
      }
      else if (copyBitmask & BAD_PTR_TREE)
      {
         printf("%zu: Nullptr tree.\n", counter);
         copyBitmask &= ~BAD_PTR_TREE;
      }
      else if (copyBitmask & BAD_PTR_NODE)
      {
         printf("%zu: Nullptr node.\n", counter);
         copyBitmask &= ~BAD_PTR_NODE;
      }
      else if (copyBitmask & BAD_PTR_DATA)
      {
         printf("%zu: Nullptr data.\n", counter);
         copyBitmask &= ~BAD_PTR_DATA;
      }
      else if (copyBitmask & BAD_PTR_RELATION)
      {
         printf("%zu: Nullptr relation.\n", counter);
         copyBitmask &= ~BAD_PTR_RELATION;
      }
      else if (copyBitmask & BAD_CAPACITY)
      {
         printf("%zu: Bad initial capacity. Available range [%zu, %zu].\n",
                counter, 2, TREE_MAX_CAPACITY);
         copyBitmask &= ~BAD_CAPACITY;
      }
      else if (copyBitmask & BOUND_RELATIONS)
      {
         printf("%zu: Bad call <tree_latinRelate>. Relations are already bound.\n",
                counter);
         copyBitmask &= ~BOUND_RELATIONS;
      }
      else
      {
         printf("Don't know <%zu> error(s).\n", copyBitmask);
         copyBitmask = 0;
      }
      
      counter += 1;
   }
}