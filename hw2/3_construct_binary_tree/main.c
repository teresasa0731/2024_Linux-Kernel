#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tree.h"


struct TreeNode *createTreeNode(int data)
{
    struct TreeNode *newNode = malloc(sizeof(struct TreeNode));
    newNode->val = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode *generateTree(int height, int *nodeNum)
{
    if (height <= 0 || (rand() % 2 == 0 && *nodeNum))
        return NULL;

    struct TreeNode *root = createTreeNode(rand() % 100);
    (*nodeNum) += 1;

    root->left = generateTree(height - 1, nodeNum);
    root->right = generateTree(height - 1, nodeNum);
    return root;
}

void preorderTraversal(struct TreeNode *root, int *result, int *index)
{
    if (!root)
        return;

    result[(*index)++] = root->val;
    preorderTraversal(root->left, result, index);
    preorderTraversal(root->right, result, index);
}

void inorderTraversal(struct TreeNode *root, int *result, int *index)
{
    if (!root)
        return;

    inorderTraversal(root->left, result, index);
    result[(*index)++] = root->val;
    inorderTraversal(root->right, result, index);
}

void postorderTraversal(struct TreeNode *root, int *result, int *index)
{
    if (!root)
        return;

    postorderTraversal(root->left, result, index);
    postorderTraversal(root->right, result, index);
    result[(*index)++] = root->val;
}

bool compareTree(int *postorder, int *result_postorder, int size)
{
    for (int i = 0; i < size; i++)
        if (postorder[i] != result_postorder[i])
            return false;
    return true;
}

void freeTree(struct TreeNode *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}



int main(void)
{
    srand(time(NULL));

    int height = 5;
    int nodeNum = 0;

    /* Generate a random binary tree as test case */
    struct TreeNode *root = generateTree(height, &nodeNum);


    int *preorder = malloc((nodeNum) * sizeof(int));
    int *inorder = malloc((nodeNum) * sizeof(int));
    int *postorder = malloc((nodeNum) * sizeof(int));

    int preIndex = 0, inIndex = 0, postIndex = 0;

    preorderTraversal(root, preorder, &preIndex);
    inorderTraversal(root, inorder, &inIndex);
    postorderTraversal(root, postorder, &postIndex);

    printf("tree height = %d, tree nodes = %d\n", height, nodeNum);


    /* Try to reconstruct binary tree */
    clock_t time = clock();
    struct TreeNode *result_root =
        buildTree(preorder, nodeNum, inorder, nodeNum);
    time = clock() - time;
    if (!root)
        printf("Fail building a tree.\n");
    printf("Reconstruct time : %ld\n", time);

    free(preorder);
    free(inorder);


    /* Test the result correctness */
    int *result_postorder = malloc((nodeNum) * sizeof(int));
    postIndex = 0;

    postorderTraversal(result_root, result_postorder, &postIndex);

    if (compareTree(postorder, result_postorder, nodeNum))
        printf("successfully rebuilt\n");
    else
        printf("rebuild failed\n");

    free(postorder);
    free(result_postorder);

    freeTree(root);
    freeTree(result_root);

    return 0;
}