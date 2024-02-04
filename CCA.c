#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* findCCA(struct TreeNode* root, int n1, int n2) {
    if (root == NULL) return NULL;

    if (root->data > n1 && root->data > n2) {
        return findCCA(root->left, n1, n2);
    } else if (root->data < n1 && root->data < n2) {
        return findCCA(root->right, n1, n2);
    } else {
        return root;
    }
}

int main() {
    struct TreeNode* root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);

    int n1 = 10, n2 = 14;
    struct TreeNode* cca = findCCA(root, n1, n2);

    if (cca != NULL) {
        printf("Closest Common Ancestor of %d and %d is: %d\n", n1, n2, cca->data);
    } else {
        printf("Closest Common Ancestor not found.\n");
    }

    return 0;
}
