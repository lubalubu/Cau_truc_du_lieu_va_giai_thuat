#include <stdio.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node nodes[100];
int nodeIndex = 0;

Node* createNode(int value) {
    Node* node = &nodes[nodeIndex++];
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* insert(Node* node, int value) {
    if (!node) return createNode(value);

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value) {
        return rightRotate(node);
    }

    if (balance < -1 && value > node->right->value) {
        return leftRotate(node);
    }

    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->value);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->value);
    }
}

int main() {
    int nums[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int n = sizeof(nums) / sizeof(nums[0]);
    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, nums[i]);
        printf("Inorder traversal after inserting %d: ", nums[i]);
        inorderTraversal(root);
        printf("\nPreorder traversal after inserting %d: ", nums[i]);
        preorderTraversal(root);
        printf("\nPostorder traversal after inserting %d: ", nums[i]);
        postorderTraversal(root);
        printf("\n----------------------------------------\n");
    }

    return 0;
}