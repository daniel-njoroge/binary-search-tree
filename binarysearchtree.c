#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new BST node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of BST
int height(struct Node* root) {
    if (root == NULL) return -1;
    int left_height = height(root->left);
    int right_height = height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Function to print level and height of a node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found!\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
        return;
    }
    if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i; 

    // Creating the BST
    struct Node* root = NULL;
    for (i = 0; i < n; i++) 
        root = insert(root, arr[i]);

    // Deleting a node (for example, deleting node 20)
    root = deleteNode(root, 20);

    // Printing the height of the BST
    printf("Height of BST: %d\n", height(root));

    // Printing the level and height of a node (for example, node 30)
    int key = 30;
    printf("Details of Node %d:\n", key);
    printLevelAndHeight(root, key, 0);

    return 0;
}

