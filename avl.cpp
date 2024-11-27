#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data, height;
    Node *left, *right;

    Node(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

// Helper functions
int getHeight(Node *root) {
    return root ? root->height : 0;
}

int getBalance(Node *root) {
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

Node *leftRotate(Node *root) {
    Node *child = root->right;
    Node *leftChild = child->left;

    child->left = root;
    root->right = leftChild;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}

Node *rightRotate(Node *root) {
    Node *child = root->left;
    Node *rightChild = child->right;

    child->right = root;
    root->left = rightChild;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    child->height = 1 + max(getHeight(child->left), getHeight(child->right));

    return child;
}

// AVL insert
Node *insert(Node *root, int key) {
    if (!root) return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    // LL Rotation
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // RR Rotation
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);

    // LR Rotation
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Rotation
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Traversals
void preorder(Node *root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void BFS(Node *root) {
    if (!root) return;
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *curr = q.front();
        q.pop();
        cout << curr->data << " ";

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// Utility function for input validation
int getOnlyInteger() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            return value;
        }
    }
}

// Main function
int main() {
    Node *root = nullptr;
    while (true) {
        cout << "\nEnter your choice: \n"
             << "1 - Insert Node\n"
             << "2 - Preorder Traversal\n"
             << "3 - Inorder Traversal\n"
             << "4 - Postorder Traversal\n"
             << "5 - Breadth-First Traversal\n"
             << "0 - Exit\n";
        int choice = getOnlyInteger();

        switch (choice) {
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            case 1: 
                cout << "Enter the value to insert: " << endl;
                int key;
                key = getOnlyInteger();
                root = insert(root, key);
                cout << key << " inserted into the AVL tree.\n";
                break;
            
            case 2:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 4:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Breadth-First Traversal: ";
                BFS(root);
                cout << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
