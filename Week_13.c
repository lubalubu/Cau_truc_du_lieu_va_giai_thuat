#include <stdio.h>

typedef struct Node {
    char value[10];          
    struct Node* left;       
    struct Node* right;      
} Node;

Node nodes[100]; 
int nodeIndex = 0;

Node* createNode(const char* value) {
    Node* node = &nodes[nodeIndex++]; 
    int i = 0;
    while (value[i] != '\0' && i < 9) { 
        node->value[i] = value[i];
        i++;
    }
    node->value[i] = '\0';
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* buildExpressionTree() {
    Node* a = createNode("a");
    Node* b = createNode("b");
    Node* c = createNode("c");
    Node* d = createNode("d");
    Node* e = createNode("e");
    Node* num_5 = createNode("5");
    Node* num_8 = createNode("8");
    Node* num_half = createNode("1/2");
    
    Node* power = createNode("^");
    Node* multiply1 = createNode("*");
    Node* divide = createNode("/");
    Node* multiply2 = createNode("*");
    Node* add1 = createNode("+");
    Node* subtract = createNode("-");
    Node* add2 = createNode("+");

    power->left = c;
    power->right = num_8;

    multiply1->left = num_5;
    multiply1->right = b;

    divide->left = multiply1;
    divide->right = c;

    subtract->left = divide;
    subtract->right = power;

    multiply2->left = d;
    multiply2->right = createNode("^");
    multiply2->right->left = e;
    multiply2->right->right = num_half;

    add1->left = a;
    add1->right = subtract;

    add2->left = add1;
    add2->right = multiply2;

    return add2;
}

void printString(const char* str) {
    while (*str) {
        putchar(*str); 
        str++;
    }
    putchar(' '); 
}

void preorderTraversal(Node* root) {
    if (root != NULL) {
        printString(root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printString(root->value);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printString(root->value);
    }
}

int main() {
    Node* root = buildExpressionTree();

    printString("Duyet truoc (Pre-order):");
    putchar('\n');
    preorderTraversal(root);
    putchar('\n');

    printString("Duyet giua (In-order):");
    putchar('\n');
    inorderTraversal(root);
    putchar('\n');

    printString("Duyet sau (Post-order):");
    putchar('\n');
    postorderTraversal(root);
    putchar('\n');

    return 0;
}