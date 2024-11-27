#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
    string name;
    Node *left;
    Node *right;
    Node *leftcenter;
    Node *rightcenter;

    Node(string name2)
    {
        name = name2;
        left = NULL;
        right = NULL;
        leftcenter = NULL;
        rightcenter = NULL;
    }
};

Node *root = NULL;

Node *searchNode(string key)
{
    if (root == NULL)
    {
        cout << "Tree is empty\n";
        return NULL;
    }

    stack<Node *> myStack;
    myStack.push(root);
    while (!myStack.empty())
    {
        Node *start = myStack.top();
        myStack.pop();
        if (start->name == key)
        {
            cout << "Found\n";
            return start;
        }
        else
        {
            if (start->left != NULL)
            {
                myStack.push(start->left);
            }
            if (start->leftcenter != NULL)
            {
                myStack.push(start->leftcenter);
            }
            if (start->rightcenter != NULL)
            {
                myStack.push(start->rightcenter);
            }
            if (start->right != NULL)
            {
                myStack.push(start->right);
            }
        }
    }
    cout << "Element not found\n";
    return NULL;
}
Node *travesalNode(string key)
{
    stack<Node *> myStack;
    myStack.push(root);
    while (!myStack.empty())
    {
        Node *start = myStack.top();
        myStack.pop();
        if (start->name == key)
        {
            return start;
        }
        else
        {
            if (start->left != NULL)
            {
                myStack.push(start->left);
            }
            if (start->leftcenter != NULL)
            {
                myStack.push(start->leftcenter);
            }
            if (start->rightcenter != NULL)
            {
                myStack.push(start->rightcenter);
            }
            if (start->right != NULL)
            {
                myStack.push(start->right);
            }
        }
    }
    return NULL;
}

void addNode(int position, string parent, string name3)
{
    if (root == NULL)
    {
        root = new Node(name3);
    }
    else
    {
        Node *temp = new Node(name3);
        Node *tempParent = travesalNode(parent);
        if (tempParent == NULL)
        {
            cout << "Parent node not found\n";
            delete temp;
            return;
        }
        if (position == 1)
        {
            tempParent->left = temp;
        }
        else if (position == 2)
        {
            tempParent->leftcenter = temp;
        }
        else if (position == 3)
        {
            tempParent->rightcenter = temp;
        }
        else if (position == 4)
        {
            tempParent->right = temp;
        }
        else
        {
            cout << "Entered wrong position\n";
            delete temp;
        }
    }
}

void printTree(Node *temp)
{
        if (temp != NULL)
        {
            cout << temp->name << endl;

            if (temp->left != NULL)
            {
                printTree(temp->left);
            }
            if (temp->leftcenter!= NULL)
            {
                printTree(temp->leftcenter);
            }
            if (temp->rightcenter!= NULL)
            {
                printTree(temp->rightcenter);
            }
            if (temp->right!= NULL)
            {
                printTree(temp->right);
            }
        }
        else
            return; 
}

int main()
{
    int ch, pstn;
    string name;
    string parentname;
    while (true)
    {
        cout << "1. To Add a node in the tree\n";
        cout << "2. To Search a node in the tree\n";
        cout << "3. Print Node\n";
        cout << "4. Exit\n";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter The name to be added\n";
            cin >> name;
            cout << "Enter the name of parent node\n";
            cin >> parentname;
            cout << "Enter Position to be added\n";
            cin >> pstn;
            addNode(pstn, parentname, name);
            break;

        case 2:
            cout << "Enter the Name to be Searched\n";
            cin >> name;
            searchNode(name);
            break;

        case 3:
            printTree(root);
            break;

        case 4:
            cout << "The Program Ends\n";
            return 0;

        default:
            cout << "Wrong choice, the program will run again\n";
            break;
        }
    }

    return 0;
}