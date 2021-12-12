OPERATOR(sh, 957002052493, {
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
})

OPERATOR(ch, 957002056589, {
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
})

OPERATOR(sin, 244996263727133, {
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
})

OPERATOR(cos, 244996264775408, {
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
})

OPERATOR(ln, 957002058891, {
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
})

OPERATOR(^, 3738232206, {
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
})

OPERATOR(*, 3738232314, {
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
})

OPERATOR(+, 3738232315, {
    node_data.type = TreeNodeType::TYPE_OP;
    node_data.value.op = 3738232315; // +
    TreeNode *p_node_plus = tree_add_node(static_p_tree_derivative, &node_data);

    tree_latinRelate(p_node_derivative, p_node_plus);
    visitor(p_node_plus, p_node_expression->left);
    visitor(p_node_plus, p_node_expression->right);
})

OPERATOR(-, 3738232317, {
    node_data.type = TreeNodeType::TYPE_OP;
    node_data.value.op = 3738232317; // -
    TreeNode *p_node_minus = tree_add_node(static_p_tree_derivative, &node_data);

    tree_latinRelate(p_node_derivative, p_node_minus);
    visitor(p_node_minus, p_node_expression->left);
    visitor(p_node_minus, p_node_expression->right);
})

OPERATOR(/, 3738232319, {
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
})
