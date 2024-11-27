#include <iostream>
#include <limits>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool isThreaded;

    Node(int value) {
        data = value;
        left = right = nullptr;
        isThreaded = false;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;

    Node* leftmost(Node* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* deleteNodeUtil(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = deleteNodeUtil(root->left, value);
        } 
        else if (value > root->data) {
            if (!root->isThreaded) {
                root->right = deleteNodeUtil(root->right, value);
            }
        } 
        else {
            // Node to be deleted found
            if (root->left == nullptr) {
                Node* temp = root->isThreaded ? root->right : nullptr;
                delete root;
                return temp;
            } 
            else if (root->right == nullptr || root->isThreaded) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children
            Node* successor = leftmost(root->right);
            root->data = successor->data;
            if (successor->isThreaded) {
                root->right = deleteNodeUtil(root->right, successor->data);
            } else {
                root->right = deleteNodeUtil(root->right, successor->data);
            }
        }
        return root;
    }

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* curr = root;
        Node* parent = nullptr;

        while (curr != nullptr) {
            parent = curr;

            if (value < curr->data) {
                if (curr->left == nullptr)
                    break;
                curr = curr->left;
            } 
            else {
                if (!curr->isThreaded) {
                    if (curr->right == nullptr)
                        break;
                    curr = curr->right;
                } 
                else {
                    break;
                }
            }
        }

        if (value < parent->data) {
            parent->left = newNode;
            newNode->right = parent;
            newNode->isThreaded = true;
        } 
        else {
            if (parent->isThreaded) {
                newNode->right = parent->right;
                newNode->isThreaded = true;
            }
            parent->right = newNode;
            parent->isThreaded = false;
        }
    }

    void deleteNode(int value) {
        root = deleteNodeUtil(root, value);
    }

    void inorder() {
        Node* curr = leftmost(root);
        while (curr != nullptr) {
            cout << curr->data << " ";

            if (curr->isThreaded)
                curr = curr->right;
            else
                curr = leftmost(curr->right);
        }
    }
    
    int getInteger() {
        int x;
        while (true) {
            cin >> x;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter an integer: ";
            } else {
                return x;
            }
        }
    }
};

int main() {
    ThreadedBinaryTree tbt;
    int num, num1, ch;

    while (true) {
        cout << "\nSelect the operation: \n";
        cout << "1. To Add a node in the tree\n";
        cout << "2. To Delete a node in the tree\n";
        cout << "3. Print Nodes (In-order Traversal)\n";
        cout << "4. Exit\n";
        ch = tbt.getInteger();

        switch (ch) {
            case 1:
                cout << "Enter the number to be added: ";
                num = tbt.getInteger();
                tbt.insert(num);
                break;

            case 2:
                cout << "Enter the number to be deleted: ";
                num1 = tbt.getInteger();
                tbt.deleteNode(num1);
                break;

            case 3:
                cout << "In-order Traversal: ";
                tbt.inorder();
                cout << endl;
                break;

            case 4:
                cout << "The Program Ends\n";
                return 0;

            default:
                cout << "Wrong choice, please try again\n";
                break;
        }
    }
    return 0;
}
