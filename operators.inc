OPERATOR(sh, sh, 957002052493, {
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
},
{

})

OPERATOR(ch, ch, 957002056589, {
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
},
{

})

OPERATOR(sin, sin, 244996263727133, {
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
},
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
        visitor(p_node->left);
})

OPERATOR(cos, cos, 244996264775408, {
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
},
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
        visitor(p_node->left);
})

OPERATOR(ln, ln, 957002058891, {
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
},
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
        visitor(p_node->left);
})

OPERATOR(power, ^, 3738232206, {
    node_data.type = TreeNodeType::TYPE_OP;
    node_data.value.op = 3738232314; // *
    TreeNode *p_node_multiply = tree_add_node(static_p_tree_derivative, &node_data);

    tree_latinRelate(p_node_derivative, p_node_multiply);
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
},
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
        tree_relate_nodes(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->left);

        was_optimized = true;
    }
    else
    {
        if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->left);

        if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->right);
    }
})

OPERATOR(multiply, *, 3738232314, {
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
},
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
        tree_relate_nodes(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->right);

        was_optimized = true;
    }
    else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 1)
    {
        tree_relate_nodes(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->left);

        was_optimized = true;
    }
    else
    {
        if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->left);

        if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->right);
    }
})

OPERATOR(plus, +, 3738232315, {
    node_data.type = TreeNodeType::TYPE_OP;
    node_data.value.op = 3738232315; // +
    TreeNode *p_node_plus = tree_add_node(static_p_tree_derivative, &node_data);

    tree_latinRelate(p_node_derivative, p_node_plus);
    visitor(p_node_plus, p_node_expression->left);
    visitor(p_node_plus, p_node_expression->right);
},
{
    TreeNodeData *const p_leftSon_data = &p_node->left->data;
    TreeNodeData *const p_rightSon_data = &p_node->right->data;

    if (p_leftSon_data->type == TreeNodeType::TYPE_NUMBER && p_leftSon_data->value.number == 0)
    {
        tree_relate_nodes(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->right);

        was_optimized = true;
    }
    else if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
    {
        tree_relate_nodes(p_node->father,
                                  p_node->father->left == p_node
                                  ? &p_node->father->left
                                  : &p_node->father->right,
                                  p_node->left);

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
            visitor(p_node->left);

        if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->right);
    }
})

OPERATOR(minus, -, 3738232317, {
    node_data.type = TreeNodeType::TYPE_OP;
    node_data.value.op = 3738232317; // -
    TreeNode *p_node_minus = tree_add_node(static_p_tree_derivative, &node_data);

    tree_latinRelate(p_node_derivative, p_node_minus);
    visitor(p_node_minus, p_node_expression->left);
    visitor(p_node_minus, p_node_expression->right);
},
{
    TreeNodeData *const p_leftSon_data = &p_node->left->data;
    TreeNodeData *const p_rightSon_data = &p_node->right->data;

    if (p_rightSon_data->type == TreeNodeType::TYPE_NUMBER && p_rightSon_data->value.number == 0)
    {
        tree_relate_nodes(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->left);

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
            visitor(p_node->left);

        if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->right);
    }
})

OPERATOR(div, /, 3738232319, {
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
},
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
        tree_relate(p_node->father,
                          p_node->father->left == p_node
                          ? &p_node->father->left
                          : &p_node->father->right,
                          p_node->left);

        was_optimized = true;
    }
    else
    {
        if (p_leftSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->left);

        if (p_rightSon_data->type == TreeNodeType::TYPE_OP)
            visitor(p_node->right);
    }
})
