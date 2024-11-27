#include <iostream>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* searchNode(Node* root, int value) {
    if (root == nullptr) 
        return nullptr;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp->data == value) {
            return temp;
        }
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
    return nullptr;
}

void searchThis(Node* root, int val) {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    if (searchNode(root, val) != nullptr) {
        cout << "Node is Found" << endl;
    } else {
        cout << "Node Not Found" << endl;
    }
}

void addNode(Node*& root, int value) {
    Node* newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp->left == nullptr) {
            temp->left = newNode;
            return;
        } else {
            q.push(temp->left);
        }
        if (temp->right == nullptr) {
            temp->right = newNode;
            return;
        } else {
            q.push(temp->right);
        }
    }
}

void inOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    stack<Node*> s;
    Node* current = root;
    while (!s.empty() || current != nullptr) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

void postOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);
        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

void breadthFirst(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}

Node* leafNode(Node* root) {
    if (root == nullptr) 
        return nullptr;
    queue<Node*> q;
    q.push(root);
    Node* leaf = nullptr;
    while (!q.empty()) {
        leaf = q.front();
        q.pop();
        if (leaf->left) q.push(leaf->left);
        if (leaf->right) q.push(leaf->right);
    }
    return leaf;
}

Node* findParent(Node* root, int value) {
    if (root == nullptr || root->data == value) 
        return nullptr;

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if ((temp->left && temp->left->data == value) || (temp->right && temp->right->data == value)) {
            return temp;
        }
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
    return nullptr;
}

void deleteNode(Node*& root, int value) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot delete!" << endl;
        return;
    }
    Node* nodeToDelete = searchNode(root, value);
    if (nodeToDelete == nullptr) {
        cout << "Node not found" << endl;
        return;
    }
    Node* leaf = leafNode(root);
    if (nodeToDelete == root && nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        delete root;
        root = nullptr;
        return;
    }
    if (leaf == nodeToDelete) {
        Node* parent = findParent(root, leaf->data);
        if (parent->left == leaf) parent->left = nullptr;
        else parent->right = nullptr;
        delete leaf;
        return;
    }
    int x = nodeToDelete->data;
    nodeToDelete->data = leaf->data;
    leaf->data = x;
    Node* parent = findParent(root, leaf->data);
    if (parent->left == leaf) parent->left = nullptr;
    else parent->right = nullptr;
    delete leaf;
}

int getInteger() {
    int x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please give an integer: ";
        } else return x;
    }
}

int main() {
    int x;
    cout << "Enter root value: ";
    x = getInteger();
    Node* root = new Node(x);

    while (true) {
        cout << endl << "Enter the operation: \n1 - To search any value \n2 - To add nodes \n3 - To perform BFS \n4 - To perform Inorder Traversal \n5 - To perform Preorder Traversal \n6 - To perform Postorder Traversal \n7 - To delete any node \n0 - Exit." << endl;
        int operation;
        operation = getInteger();

        if (operation == 0) {
            break;
        }
        switch (operation) {
            case 1: {
                int value;
                cout << "Enter data to search: ";
                value = getInteger();
                searchThis(root, value);
                break;
            }
            case 2: {
                int noOfValues1, value1;
                cout << "How many nodes to be added? ";
                noOfValues1 = getInteger();
                cout << "Enter value to be added: ";
                for (int i = 0; i < noOfValues1; i++) {
                    value1 = getInteger();
                    addNode(root, value1);
                }
                break;
            }
            case 3: {
                breadthFirst(root);
                break;
            }
            case 4: {
                inOrder(root);
                break;
            }
            case 5: {
                preOrder(root);
                break;
            }
            case 6: {
                postOrder(root);
                break;
            }
            case 7: {
                int value2;
                cout << "Enter value to be deleted: ";
                value2 = getInteger();
                deleteNode(root, value2);
                break;
            }
            default:
                cout << "Invalid operation. Try again." << endl;
        }
    }
    return 0;
}
