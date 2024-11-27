#include <iostream>
#include <climits>
#include <limits>
using namespace std;

class MaxHeap {
private:
    int* heap;
    int capacity;
    int size;

    void heapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapify(largest);
        }
    }

    int getOnlyInteger() {
        int input;
        while (true) {
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter an integer: ";
            } else {
                break;
            }
        }
        return input;
    }

public:
    MaxHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new int[capacity];
    }

    ~MaxHeap() {
        delete[] heap;
    }

    int getMax() {
        if (size > 0) {
            return heap[0];
        }
        return INT_MIN;
    }

    void insert() {
        if (size == capacity) {
            cout << "Heap is full!" << endl;
            return;
        }

        cout << "Enter a value to insert into the heap: ";
        int val = getOnlyInteger();
        heap[size] = val;
        int index = size;
        size++;

        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    int extractMax() {
        if (size == 0) return INT_MIN;

        int maxVal = heap[0];
        heap[0] = heap[size - 1];
        size--;

        heapify(0);

        return maxVal;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap heap(10);
    int choice;

    do {
        cout << "\nMax Heap Operations: \n";
        cout << "1. Insert element\n";
        cout << "2. Extract Max\n";
        cout << "3. Display Heap\n";
        cout << "4. Get Max\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                heap.insert();
                break;
            case 2:
                cout << "Extracted Max: " << heap.extractMax() << endl;
                break;
            case 3:
                cout << "Current Heap: ";
                heap.display();
                break;
            case 4:
                cout << "Maximum element in the heap: " << heap.getMax() << endl;
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
