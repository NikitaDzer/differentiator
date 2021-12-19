#include "../include/tex.h"
#include "../include/tree.h"
#include "../include/config.h"

static FILE *texfile = nullptr;

#define OPERATOR(op_name, op_sign, op_hash, code, optimization)   \
{                                                                 \
   case (op_hash):                                                \
   {                                                              \
      tex_##op_name(p_node);                                      \
      break;                                                      \
   }                                                              \
}

static void
tex_node(const TreeNode *const p_node);

static void
texfile_open(const char *const texfile_path)
{
   texfile = fopen(texfile_path, "w");
   assert(texfile);

   fprintf(texfile,
           "\\documentclass[12pt]{article}\n"
           "\\usepackage[utf8]{inputenc}\n"
           "\\usepackage[russian]{babel}\n"
           "\\usepackage{geometry} \n"
           "\\geometry{a4paper} \n"
           "\\usepackage{graphicx}\n"
           "\\begin{document}\n"
           "\\section*{Давай посчитаем твою производную}\n");
}

static void
texfile_close()
{
   fprintf(texfile, "\\end{document}\n");

   assert(fclose(texfile) == 0);
}

static void
texfile_controller(const char *const texfile_path)
{
   if (texfile == nullptr)
      texfile_open(texfile_path);
}

static void
tex_plus(const TreeNode *const p_node)
{
   fprintf(texfile, "{(");
   tex_node(p_node->left);
   fprintf(texfile, " + ");
   tex_node(p_node->right);
   fprintf(texfile, ")}");
}

static void
tex_minus(const TreeNode *const p_node)
{
   fprintf(texfile, "{(");
   tex_node(p_node->left);
   fprintf(texfile, " - ");
   tex_node(p_node->right);
   fprintf(texfile, ")}");
}

static void
tex_sin(const TreeNode *const p_node)
{
   fprintf(texfile, "\\sin{");
   tex_node(p_node->left);
   fprintf(texfile, "}");
}

static void
tex_cos(const TreeNode *const p_node)
{
   fprintf(texfile, "\\cos{");
   tex_node(p_node->left);
   fprintf(texfile, "}");
}

static void
tex_power(const TreeNode *const p_node)
{
   if (p_node->left->data.type != TreeNodeType::TYPE_OP)
   {
      fprintf(texfile, "{");
      tex_node(p_node->left);
      fprintf(texfile, "^{");
      tex_node(p_node->right);
      fprintf(texfile, "}}");
   }
   else
   {
      fprintf(texfile, "{(");
      tex_node(p_node->left);
      fprintf(texfile, ")^{");
      tex_node(p_node->right);
      fprintf(texfile, "}}");
   }
}

static void
tex_sh(const TreeNode *const p_node)
{

}

static void
tex_ch(const TreeNode *const p_node)
{

}

static void
tex_ln(const TreeNode *const p_node)
{
   fprintf(texfile, "\\ln{");
   tex_node(p_node->left);
   fprintf(texfile, "}");
}

static void
tex_multiply(const TreeNode *const p_node)
{
   fprintf(texfile, "{");
   tex_node(p_node->left);
   fprintf(texfile, " \\cdot ");
   tex_node(p_node->right);
   fprintf(texfile, "}");
}

static void
tex_div(const TreeNode *const p_node)
{
   fprintf(texfile, "\\frac{");
   tex_node(p_node->left);
   fprintf(texfile, "}{");
   tex_node(p_node->right);
   fprintf(texfile, "}");
}

static void
tex_node(const TreeNode *const p_node)
{
   switch (p_node->data.type)
   {
      case TreeNodeType::TYPE_VARIABLE:
      {
         fprintf(texfile, "%c", p_node->data.value.variable);
         break;
      }

      case TreeNodeType::TYPE_CONSTANT:
      {
         fprintf(texfile, "%c", p_node->data.value.constant);
         break;
      }

      case TreeNodeType::TYPE_NUMBER:
      {
         if (p_node->data.value.number < 0)
            fprintf(texfile, "(%lg)", p_node->data.value.number);
         else
            fprintf(texfile, "%lg", p_node->data.value.number);
         
         break;
      }

      case TreeNodeType::TYPE_OP:
      {
         switch (p_node->data.value.op)
         {
            #include "../operators.inc"

            default:
            {
               printf("Don't know this <%zu> operator hash.\n", p_node->data.value.op);
               abort();
            }
         }

         break;
      }

      default:
      {
         printf("Don't know this <%zu> node type.\n", p_node->data.type);
         abort();
      }
   }
}

static void
tex_tree(const Tree *const p_tree)
{
   assert(p_tree);
   
   if (p_tree->root->left != nullptr)
   {
      fprintf(texfile, "$");
      tex_node(p_tree->root->left);
      fprintf(texfile, "$\\newline\\newline");
   }
}

void
tex(const Tree *const p_tree, const size_t derivative_order, const char *const texfile_path)
{
   assert(p_tree);
   
   texfile_controller(texfile_path);
   fprintf(texfile, "$f^{");
   
   for (size_t i = 0; i < derivative_order; i++)
      fprintf(texfile, "\\prime");
   
   fprintf(texfile, "}(x) = $ ");
   tex_tree(p_tree);
}

void
show_texfile(const char *const texfile_path, const char *const htmlfile_path)
{
   if (texfile == nullptr)
      return;
   
   texfile_close();
   
   FILE *stream = nullptr;
   char  system_cmd[128]    = "";
   char  pdffile_path[128]  = "";
   
   strcat(pdffile_path, texfile_path);
  *strstr(pdffile_path, ".tex") = '\0';
   strcat(pdffile_path, ".pdf");
   
   strcat(system_cmd, "pdflatex ");
   strcat(system_cmd, texfile_path);
   system(system_cmd);
   
   stream = fopen(htmlfile_path, "w");
   assert(stream);
   
   fprintf(stream,
           "<!doctype html>                                                             \n"
           "<html>                                                                      \n"
           "\t<head lang='en'>                                                          \n"
           "\t\t<meta charset='utf-8'>                                                  \n"
           "\t\t<meta name='viewport' content='width=device-width'>                     \n"
           "\t\t<title>Differentiator</title>                                           \n"
           "\t\t<style>                                                                 \n"
           "\t\tbody {                                                                  \n"
           "\t\t\tbackground: #222222;                                                  \n"
           "\t\t\tcolor:      #DDDDDD;                                                  \n"
           "\t\t\tfont-family: Arial, sans-serif;                                       \n"
           "\t\t\twidth: 100vw;                                                         \n"
           "\t\t\theight: 100vh;                                                        \n"
           "\t\t\toverflow: hidden;                                                     \n"
           "\t\t\tpadding: 0;                                                           \n"
           "\t\t\tmargin:  0;                                                           \n"
           "\t\t}                                                                       \n"
           "\t\t</style>                                                                \n"
           "\t</head>                                                                   \n"
           "\t<body>                                                                    \n"
           "\t\t<object width = 100vw height = 100vh>                                   \n"
           "\t\t\t<embed src = %s width = \"100%\" height = \"100%\">                   \n"
           "\t\t</object>                                                               \n"
           "\t</body>                                                                   \n"
           "</html>                                                                     \n",
           pdffile_path);
   
   assert(fclose(stream) == 0);
}

