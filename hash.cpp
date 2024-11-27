#include <iostream>
#include <limits>

using namespace std;

class Node {
public:
    int key;
    Node* next;

    Node(int k) : key(k), next(nullptr) {}
};

class HashTable {
private:
    Node* hashtable[10];

public:
    HashTable() {
        for (int i = 0; i < 10; i++) {
            hashtable[i] = nullptr;
        }
    }

    void insert(int key) {
        int index = key % 10;
        Node* newNode = new Node(key);

        if (hashtable[index] == nullptr) {
            hashtable[index] = newNode;
            cout << "Key " << key << " inserted successfully.\n";
        } 
        else {
            Node* temp = hashtable[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            cout << "Key " << key << " inserted successfully.\n";
        }
    }

    void search(int key) {
        int index = key % 10;
        Node* temp = hashtable[index];

        while (temp != nullptr) {
            if (temp->key == key) {
                cout << "Key " << key << " found.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Key " << key << " not found.\n";
    }

    void remove(int key) {
        int index = key % 10;
        Node* temp = hashtable[index];
        Node* prev = nullptr;

        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr) {
                    hashtable[index] = temp->next;
                } 
                else {
                    prev->next = temp->next;
                }
                delete temp;
                cout << "Key " << key << " deleted successfully.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Key " << key << " not found.\n";
    }

    void printTable() {
        cout << "\nHash Table Contents:\n";
        for (int i = 0; i < 10; i++) {
            cout << "Index " << i << ": ";
            Node* temp = hashtable[i];
            if (temp == nullptr) {
                cout << "Empty";
            } 
            else {
                while (temp != nullptr) {
                    cout << temp->key;
                    temp = temp->next;
                    if (temp != nullptr) cout << " -> ";
                }
            }
            cout << endl;
        }
    }

    int getInteger() {
        int x;
        while (true) {
            cin >> x;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid integer: ";
            } 
            else {
                return x;
            }
        }
    }
};

int main() {
    HashTable ht;
    int choice, key;

    while (true) {
        cout << "\nEnter your choice: ";
        cout << "\n1 - Insert Key";
        cout << "\n2 - Search Key";
        cout << "\n3 - Delete Key";
        cout << "\n4 - Print Hash Table";
        cout << "\n5 - Exit\n";
        choice = ht.getInteger();

        switch (choice) {
            case 1:
                cout << "Enter the Key: ";
                key = ht.getInteger();
                ht.insert(key);
                break;

            case 2:
                cout << "Enter the Key to search: ";
                key = ht.getInteger();
                ht.search(key);
                break;

            case 3:
                cout << "Enter the Key to delete: ";
                key = ht.getInteger();
                ht.remove(key);
                break;

            case 4:
                ht.printTable();
                break;

            case 5:
                exit(0);

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
