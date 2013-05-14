        if (root == NULL) {
            return 0;
        }
        int result = 0;
        vector<TreeNode*> node_stack;
        int stack_value = root->val;
        node_stack.push_back(root);
        int op = 0;
        TreeNode* father_node = NULL;
        TreeNode* child_node = NULL;
        while(!node_stack.empty()) {
            //insert op
            if (op == 0) {
                //insert child
                TreeNode* cur_node = node_stack.back();
                if (cur_node->left != NULL) {
                    node_stack.push_back(cur_node->left);
                    stack_value = stack_value*10 + cur_node->left->val;
                } else if (cur_node->right != NULL) {
                    node_stack.push_back(cur_node->right);
                    stack_value = stack_value*10 + cur_node->right->val;
                } else {
                    op = 1;
                }
            } else if(op==1) {
                //get path value
                child_node = node_stack.back();
                result += stack_value;
                node_stack.pop_back();
                stack_value = (stack_value-child_node->val)/10;
                op = 2;
            } else if (op==2) {
                //insert brother
                father_node = node_stack.back();
                if (father_node->left == child_node && father_node->right != NULL) {
                    node_stack.push_back(father_node->right);
                    stack_value = stack_value*10 + father_node->right->val;
                    op = 0;
                } else {
                    child_node = father_node;
                    node_stack.pop_back();
                    stack_value = (stack_value - father_node->val)/10;
                }
            }
        }
        
        return result;
