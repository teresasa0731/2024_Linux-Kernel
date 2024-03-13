#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct StackNode {
    struct TreeNode *node;
    int pre_low;
    int pre_high;
    int in_low;
    int in_high;
};

struct TreeNode *buildTree(int *preorder,
                           int preorderSize,
                           int *inorder,
                           int inorderSize)
{
    if (preorderSize == 0 || inorderSize == 0)
        return NULL;

    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = NULL;
    root->right = NULL;

    struct StackNode *stack = malloc(preorderSize * sizeof(struct StackNode));
    int top = -1;  // Initialize stack top

    struct StackNode root_node = {root, 0, preorderSize - 1, 0,
                                  inorderSize - 1};
    stack[++top] = root_node;

    while (top >= 0) {
        struct StackNode current = stack[top--];
        struct TreeNode *current_node = current.node;
        int pre_low = current.pre_low;
        int pre_high = current.pre_high;
        int in_low = current.in_low;
        int in_high = current.in_high;

        // Find the index of current node in inorder
        int idx = in_low;
        while (inorder[idx] != current_node->val)
            idx++;

        // Build left subtree
        if (idx > in_low) {
            current_node->left = malloc(sizeof(struct TreeNode));
            current_node->left->val = preorder[pre_low + 1];
            current_node->left->left = NULL;
            current_node->left->right = NULL;
            struct StackNode left_node = {current_node->left, pre_low + 1,
                                          pre_low + (idx - in_low), in_low,
                                          idx - 1};
            stack[++top] = left_node;
        }

        // Build right subtree
        if (idx < in_high) {
            current_node->right = malloc(sizeof(struct TreeNode));
            current_node->right->val = preorder[pre_high - (in_high - idx - 1)];
            current_node->right->left = NULL;
            current_node->right->right = NULL;
            struct StackNode right_node = {current_node->right,
                                           pre_high - (in_high - idx - 1),
                                           pre_high, idx + 1, in_high};
            stack[++top] = right_node;
        }
    }

    free(stack);
    return root;
}
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct StackNode {
    struct TreeNode *node;
    int pre_low;
    int pre_high;
    int in_low;
    int in_high;
};

struct TreeNode *buildTree_test(int *preorder,
                           int preorderSize,
                           int *inorder,
                           int inorderSize)
{
    if (preorderSize == 0 || inorderSize == 0)
        return NULL;

    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = NULL;
    root->right = NULL;

    struct StackNode *stack = malloc(preorderSize * sizeof(struct StackNode));
    int top = -1;  // Initialize stack top

    struct StackNode root_node = {root, 0, preorderSize - 1, 0,
                                  inorderSize - 1};
    stack[++top] = root_node;

    while (top >= 0) {
        struct StackNode current = stack[top--];
        struct TreeNode *current_node = current.node;
        int pre_low = current.pre_low;
        int pre_high = current.pre_high;
        int in_low = current.in_low;
        int in_high = current.in_high;

        // Find the index of current node in inorder
        int idx = in_low;
        while (inorder[idx] != current_node->val)
            idx++;

        // Build left subtree
        if (idx > in_low) {
            current_node->left = malloc(sizeof(struct TreeNode));
            current_node->left->val = preorder[pre_low + 1];
            current_node->left->left = NULL;
            current_node->left->right = NULL;
            struct StackNode left_node = {current_node->left, pre_low + 1,
                                          pre_low + (idx - in_low), in_low,
                                          idx - 1};
            stack[++top] = left_node;
        }

        // Build right subtree
        if (idx < in_high) {
            current_node->right = malloc(sizeof(struct TreeNode));
            current_node->right->val = preorder[pre_high - (in_high - idx - 1)];
            current_node->right->left = NULL;
            current_node->right->right = NULL;
            struct StackNode right_node = {current_node->right,
                                           pre_high - (in_high - idx - 1),
                                           pre_high, idx + 1, in_high};
            stack[++top] = right_node;
        }
    }

    free(stack);
    return root;
}