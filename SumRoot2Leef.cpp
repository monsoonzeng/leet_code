/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) {
            return 0;
        }
        int result = 0;
        vector<TreeNode*> node_stack;
        int stack_value = root->val;
        node_stack.push_back(root);
        while(!node_stack.empty()) {
            TreeNode* cur_node = node_stack.back();
            if (cur_node->left != NULL) {
                node_stack.push_back(cur_node->left);
                stack_value = stack_value*10 + cur_node->left->val;
            } else if (cur_node->right != NULL) {
                node_stack.push_back(cur_node->right);
                stack_value = stack_value*10 + cur_node->right->val;
            } else {
                //get path
                result += stack_value;
                node_stack.pop_back();
                stack_value = (stack_value-cur_node->val)/10;
                TreeNode* child_node = cur_node;
                while (!node_stack.empty()) {
                    TreeNode* father_node = node_stack.back();
                    if (father_node->left == child_node && father_node->right != NULL) {
                       node_stack.push_back(father_node->right);
                       stack_value = stack_value*10 + father_node->right->val;
                       break; 
                    } else {
                        child_node = father_node;
                        node_stack.pop_back();
                        stack_value = (stack_value - father_node->val)/10;
                    }
                }
            }
        }
        
        return result;
    }
};
