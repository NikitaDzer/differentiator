#ifndef DIFFERENTIATOR_TEX_H
#define DIFFERENTIATOR_TEX_H

#include "tree.h"

const char TEXFILE_PATH[]  = "derivative.tex";
const char HTMLFILE_PATH[] = "derivative.html";

void
tex(const Tree *const p_tree, const size_t derivative_order, const char *const texfile_path = TEXFILE_PATH);

void
show_texfile(const char *const texfile_path = TEXFILE_PATH, const char *const htmlfile_path = HTMLFILE_PATH);

#endif // DIFFERENTIATOR_TEX_H