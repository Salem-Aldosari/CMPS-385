#include <iostream>
using namespace std;

// Node structure for circular linked list
class Node {
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// Circular Queue class using a linked list
class CircularQueue {
private:
    Node* rear;  // Single pointer to track rear (last) node

public:
    // Constructor
    CircularQueue() {
        rear = nullptr;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return rear == nullptr;
    }

    // Enqueue operation
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            // If the queue is empty, point the new node to itself
            rear = newNode;
            rear->next = rear;
        }
        else {
            // Insert at rear and adjust pointers
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Enqueued: " << value << endl;
    }

    // Dequeue operation
    void dequeue() {
        if (isEmpty()) {
            cout << "The queue is already empty, dequeue fails.\n";
            return;
        }
        Node* front = rear->next;  // Front node (next of rear)
        if (rear == front) {  // If only one node
            delete front;
            rear = nullptr;
        }
        else {
            rear->next = front->next;
            delete front;
        }
        cout << "Dequeued an element.\n";
    }

    // Get front element without removing it
    void getFront() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Front element: " << rear->next->data << endl;
    }

    // Destructor to clean up memory
    ~CircularQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Main function to test the queue
int main() {
    CircularQueue q;
    q.enqueue(16);
    q.enqueue(27);
    q.enqueue(39);

    q.getFront(); // print 16

    q.dequeue();
    q.getFront(); // print 27

    q.dequeue();
    q.dequeue();
    q.getFront();  // Should return queue is empty

    return 0;
}
