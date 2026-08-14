// Problem: Lowest Common Ancestor (LCA) of a Binary Search Tree
// Approach: Use BST property - if both p and q are smaller, go left;
// if both bigger, go right; otherwise current node is the split point (LCA).
// Time: O(h) where h is tree height   Space: O(1) iterative

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* curr = root;
    while (curr) {
        if (p->val < curr->val && q->val < curr->val) curr = curr->left;
        else if (p->val > curr->val && q->val > curr->val) curr = curr->right;
        else return curr; // split point found
    }
    return nullptr;
}

int main() {
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode* p = root->left;        // node 2
    TreeNode* q = root->left->right; // node 4

    TreeNode* lca = lowestCommonAncestor(root, p, q);
    cout << "LCA: " << lca->val << endl; // expected 2
    return 0;
}
