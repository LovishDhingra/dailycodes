// 235. Lowest Common Ancestor of a Binary Search Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// (Also includes the general-tree version, 236, since that came up while
//  debugging a non-BST test case in the conversation.)

import java.util.*;

public class Solution235_LCA_BST {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    // ---------- Brute Force (235): find both root-to-node paths, compare ----------
    static class SolutionBruteForce {
        private boolean findPath(TreeNode node, TreeNode target, List<TreeNode> path) {
            while (node != null) {
                path.add(node);
                if (node.val == target.val) return true;
                else if (target.val < node.val) node = node.left;
                else node = node.right;
            }
            return false;
        }

        public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
            List<TreeNode> pathP = new ArrayList<>();
            List<TreeNode> pathQ = new ArrayList<>();
            findPath(root, p, pathP);
            findPath(root, q, pathQ);

            TreeNode lca = null;
            int i = 0;
            while (i < pathP.size() && i < pathQ.size() && pathP.get(i) == pathQ.get(i)) {
                lca = pathP.get(i);
                i++;
            }
            return lca;
        }
    }

    // ---------- Optimal (235): single pass using BST ordering property ----------
    static class SolutionOptimalBST {
        public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
            TreeNode node = root;
            while (node != null) {
                if (p.val < node.val && q.val < node.val) {
                    node = node.left;
                } else if (p.val > node.val && q.val > node.val) {
                    node = node.right;
                } else {
                    return node;
                }
            }
            return null;
        }
    }

    // ---------- 236: General Binary Tree version (no ordering to exploit) ----------
    static class SolutionGeneralTree {
        public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
            if (root == null || root == p || root == q) return root;

            TreeNode left = lowestCommonAncestor(root.left, p, q);
            TreeNode right = lowestCommonAncestor(root.right, p, q);

            if (left != null && right != null) return root;
            return left != null ? left : right;
        }
    }

    public static void main(String[] args) {
        // BST example: root = [6,2,8,0,4,7,9,null,null,3,5]
        TreeNode root = new TreeNode(6);
        root.left = new TreeNode(2);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(4);
        root.left.right.left = new TreeNode(3);
        root.left.right.right = new TreeNode(5);
        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(9);

        SolutionOptimalBST s = new SolutionOptimalBST();
        TreeNode p = root.left;             // 2
        TreeNode q = root.right;            // 8
        System.out.println(s.lowestCommonAncestor(root, p, q).val); // 6
    }
}
