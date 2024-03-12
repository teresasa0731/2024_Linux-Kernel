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
    if (height <= 0 || rand() % 2 == 0)
        return NULL;

    struct TreeNode *root = createTreeNode(rand() % height);
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

bool compareTree(int *preorder,
                 int *result_preorder,
                 int *inorder,
                 int *result_inorder,
                 int size)
{
    for (int i = 0; i < size; i++)
        if (preorder[i] != result_preorder[i] ||
            inorder[i] != result_inorder[i])
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

    int height = 100;
    int nodeNum = 0;

    /* Generate a random binary tree as test case */
    struct TreeNode *root = generateTree(height, &nodeNum);

    printf("tree height = %d, tree nodes = %d\n", height, nodeNum);

    int *preorder = malloc((nodeNum) * sizeof(int));
    int *inorder = malloc((nodeNum) * sizeof(int));

    int preIndex = 0, inIndex = 0;

    preorderTraversal(root, preorder, &preIndex);
    inorderTraversal(root, inorder, &inIndex);

    /* Try to reconstruct binary tree */
    clock_t time = clock();
    struct TreeNode *result_root =
        buildTree(preorder, nodeNum, inorder, nodeNum);
    time = clock() - time;
    printf("Reconstruct time : %ld\n", time);


    /* Test the result correctness */
    int *result_preorder = malloc((nodeNum) * sizeof(int));
    int *result_inorder = malloc((nodeNum) * sizeof(int));

    preIndex = 0;
    inIndex = 0;

    preorderTraversal(result_root, result_preorder, &preIndex);
    inorderTraversal(result_root, result_inorder, &inIndex);

    if (compareTree(preorder, result_preorder, inorder, result_inorder,
                    nodeNum))
        printf("successfully rebuilt\n");
    else
        printf("rebuild failed\n");

    free(preorder);
    free(inorder);

    freeTree(root);
    freeTree(result_root);

    return 0;
}