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

    struct TreeNode *root = createTreeNode((*nodeNum)++);

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

    FILE *ftest, *fmain;

    ftest = fopen("test.txt", "w+");
    fmain = fopen("main.txt", "w+");

    for (int i = 0; i < 10000; i++) {
        int height = 200;
        int nodeNum = 0;

        /* Generate a random binary tree as test case */
        struct TreeNode *root = generateTree(height, &nodeNum);

        if (nodeNum < 1000)
            continue;


        int *preorder = malloc((nodeNum) * sizeof(int));
        int *inorder = malloc((nodeNum) * sizeof(int));
        int *postorder = malloc((nodeNum) * sizeof(int));

        int preIndex = 0, inIndex = 0, postIndex = 0;

        preorderTraversal(root, preorder, &preIndex);
        inorderTraversal(root, inorder, &inIndex);
        postorderTraversal(root, postorder, &postIndex);

        printf("tree height = %d, tree nodes = %d\n", height, nodeNum);

        clock_t time;
        struct TreeNode *result_root;
        int *result_postorder = malloc((nodeNum) * sizeof(int));

        /* Try to reconstruct binary tree */
        time = clock();
        result_root = buildTree(preorder, nodeNum, inorder, nodeNum);
        time = clock() - time;
        if (!root)
            printf("Fail building a tree.\n");
        printf("Reconstruct time : %ld\n", time);

        /* Test the result correctness */
        postIndex = 0;

        postorderTraversal(result_root, result_postorder, &postIndex);

        if (compareTree(postorder, result_postorder, nodeNum)) {
            printf("successfully rebuilt\n");
            fprintf(fmain, "%d,%ld\n", nodeNum, time);
        } else
            printf("rebuild failed\n");

        /* Try to reconstruct binary tree */
        time = clock();
        result_root = buildTree_test(preorder, nodeNum, inorder, nodeNum);
        time = clock() - time;
        if (!root)
            printf("Fail building a tree.\n");
        printf("Reconstruct time : %ld\n", time);

        /* Test the result correctness */
        postIndex = 0;
        postorderTraversal(result_root, result_postorder, &postIndex);

        if (compareTree(postorder, result_postorder, nodeNum)) {
            printf("successfully rebuilt\n");
            fprintf(ftest, "%d,%ld\n", nodeNum, time);
        }

        else
            printf("rebuild failed\n");

        free(postorder);
        free(result_postorder);

        freeTree(root);
        freeTree(result_root);
    }
    fclose(fmain);
    fclose(ftest);

    return 0;
}