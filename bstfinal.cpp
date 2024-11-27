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

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* searchNode(Node* root, int value) {
    Node* temp = root;
    while (temp != nullptr) {
        if (temp->data == value) {
            return temp;
        } 
        else if (value < temp->data) {
            temp = temp->left;
        } 
        else {
            temp = temp->right;
        }
    }
    return nullptr;
}

void searchThis(Node*& root, int val) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    if (searchNode(root, val) != nullptr) {
        cout << "Node is Found." << endl;
    } else {
        cout << "Node Not Found." << endl;
    }
}

void addNode(Node* &root, int value) {
    Node *newNode = new Node(value);
    if (searchNode(root, newNode->data)) {
        cout << "Node is already present, enter unique value." << endl;
        return;
    }
    if (root == nullptr) {
        root = newNode;
        return;
    }
    Node *parent = nullptr;
    Node *current = root;
    while (current != nullptr) {
        if (current->data > value) {
            parent = current;
            current = current->left;
        } else if (current->data < value) {
            parent = current;
            current = current->right;
        }
    }
    if (parent->data > value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

void inOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }

    stack<Node*> s;
    s.push(root);
    Node* lastVisited = root;
    while (!s.empty()) {
        Node *current = s.top();
        s.pop();
        if (current->left && current->left != lastVisited && current->right != lastVisited) {
            s.push(current);
            s.push(current->left);
        } else if (current->right && current->right != lastVisited) {
            cout << current->data << " ";
            s.push(current);
            s.push(current->right);
        } else if (current->right != lastVisited) {
            cout << current->data << " ";
        }
        lastVisited = current;
    }
}

void breadthFirst(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty. Cannot print!" << endl;
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
    cout << endl;
}

Node* findParent(Node* root, int value) {
    if (root == nullptr || root->data == value) return nullptr;

    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr) {
        if (current->data == value) return parent;
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

void deleteNode(Node*& root, int value) {
    if (root == nullptr) {
        cout << "Tree is empty. Cannot delete!" << endl;
        return;
    }

    Node* nodeToDelete = searchNode(root, value);
    if (nodeToDelete == nullptr) {
        cout << "Node not found. Cannot delete!" << endl;
        return;
    }

    Node* parent = findParent(root, value);

    // Case 1: Node is a leaf.
    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        if (parent == nullptr) {
            root = nullptr; // Deleting the root node.
        } else if (parent->left == nodeToDelete) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete nodeToDelete;
    }
    // Case 2: Node has one child.
    else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        Node* child = (nodeToDelete->left) ? nodeToDelete->left : nodeToDelete->right;
        if (parent == nullptr) {
            root = child; // Replacing root.
        } else if (parent->left == nodeToDelete) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete nodeToDelete;
    }
    // Case 3: Node has two children.
    else {
        Node* successor = nodeToDelete->right;
        Node* successorParent = nodeToDelete;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        nodeToDelete->data = successor->data;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        delete successor;
    }
}

int getOnlyInteger() {
    int x;
    while (true) {
        cin >> x;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid integer: ";
        } else {
            return x;
        }
    }
}

int main() {
    int r;
    cout << "Enter the root node: ";
    r = getOnlyInteger();
    Node* root = new Node(r);

    while (true) {
        cout << endl
             << "Enter the operation: \n"
             << "1 - To search any value\n"
             << "2 - To add nodes\n"
             << "3 - To perform BFS\n"
             << "4 - To perform Inorder Traversal\n"
             << "5 - To delete any node\n"
             << "0 - Exit.\n";
        int operation = getOnlyInteger();

        switch (operation) {
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            case 1: {
                cout << "Enter data to search: ";
                int value = getOnlyInteger();
                searchThis(root, value);
                break;
            }
            case 2: {
                cout << "How many values do you want to add?" << endl;
                int count = getOnlyInteger();
                for (int i = 0; i < count; i++) {
                    cout << "Enter value " << (i + 1) << ": ";
                    int value = getOnlyInteger();
                    addNode(root, value);
                }
                break;
            }
            case 3:
                cout << "Breadth-First Traversal: ";
                breadthFirst(root);
                break;
            case 4:
                cout << "Inorder Traversal: ";
                inOrder(root);
                break;
            case 5: {
                cout << "Enter the value of the node to delete: ";
                int value = getOnlyInteger();
                deleteNode(root, value);
                break;
            }
            default:
                cout << "Invalid operation. Try again." << endl;
        }
    }
    return 0;
}
