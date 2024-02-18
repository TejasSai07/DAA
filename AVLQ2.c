#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

struct AVLNode* newNode(int key) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(struct AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int balanceFactor(struct AVLNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

struct AVLNode* insert(struct AVLNode* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node; 

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(struct AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct AVLNode* minValueNode(struct AVLNode* node) {
    struct AVLNode* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct AVLNode* successor(struct AVLNode* root, int key) {
    struct AVLNode* current = root;
    struct AVLNode* succ = NULL;

    while (current != NULL) {
        if (current->key > key) {
            succ = current;
            current = current->left;
        } else if (current->key < key) {
            current = current->right;
        } else {
            if (current->right != NULL) {
                succ = minValueNode(current->right);
            }
            break;
        }
    }

    return succ;
}

struct AVLNode* maxValueNode(struct AVLNode* node) {
    struct AVLNode* current = node;

    while (current && current->right != NULL)
        current = current->right;

    return current;
}

struct AVLNode* predecessor(struct AVLNode* root, int key) {
    struct AVLNode* current = root;
    struct AVLNode* pred = NULL;

    while (current != NULL) {
        if (current->key < key) {
            pred = current;
            current = current->right;
        } else if (current->key > key) {
            current = current->left;
        } else {
            if (current->left != NULL) {
                pred = maxValueNode(current->left);
            }
            break;
        }
    }

    return pred;
}

int main() {
    struct AVLNode* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal of the constructed AVL tree is: ");
    inorder(root);
    printf("\n");

    int key_to_find = 30;
    struct AVLNode* successor_node = successor(root, key_to_find);
    struct AVLNode* predecessor_node = predecessor(root, key_to_find);

    printf("Successor of %d is %d\n", key_to_find, (successor_node != NULL) ? successor_node->key : -1);
    printf("Predecessor of %d is %d\n", key_to_find, (predecessor_node != NULL) ? predecessor_node->key : -1);

    return 0;
}
