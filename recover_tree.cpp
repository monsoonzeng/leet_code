#include<iostream>

using namespace std;
/**
 Definition for binary tree
*/
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    void recoverTree(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //use morris traversal
        //x[j] > x[j+1] then swap1=x[j] x[j]>x[j+1] then swap2=x[j+1]
        TreeNode *current = root;
        TreeNode *pre;
        TreeNode *swap1, *swap2;
	TreeNode *predecessor=NULL;
        bool find = false;
        while (current != NULL) {
            if (current->left == NULL) {
                //visit current
		cout << current->val << endl;
		if (predecessor!=NULL && predecessor->val > current->val) {
                    if (find) {
                        swap2 = current;
                    } else {
                        swap1 = predecessor;
                        swap2 = current;
                        find = true;
                    }
                }
		predecessor = current;
		current = current->right;
                continue;
            }
            pre = current->left;
            while(pre->right!=NULL && pre->right != current) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            } else {
                //visit current
		cout << current->val << endl;
		if (predecessor!=NULL && predecessor->val > current->val) {
                    if (find) {
                        swap2 = current;
                    } else {
                        swap1 = predecessor;
                        swap2 = current;
                        find = true;
                    }
                }
		pre->right = NULL;
		predecessor = current;
		current = current->right;
            }
            
        }
        if (find) {
            int tmp = swap1->val;
            swap1->val = swap2->val;
            swap2->val = tmp;
        }
    }
};


TreeNode* newtNode(int val) 
{
    TreeNode* result = new TreeNode(val);
    return result;
}
void print_tree(TreeNode *root) {
    if(root ==NULL) {
        cout<<"# ";
	return;
    }
    cout<<root->val<<' ';
    print_tree(root->left);
    print_tree(root->right);
}
int main()
{
  /* Constructed binary tree is
            1
          /   \
        2      3
      /  \
    4     5
  */
  TreeNode *root = new TreeNode(0);
  root->left = new TreeNode(1);
  Solution so;
  so.recoverTree(root);
  print_tree(root);
  return 0;
}

