#include <iostream>
using namespace std;

// Node structure for the doubly linked list
struct Node {
    int data;     // Data stored in the node
    Node* prev;   // Pointer to the previous node
    Node* next;   // Pointer to the next node

    Node(int val) : data(val), prev(nullptr), next(nullptr) {} // Constructor to initialize a new node
};

// Function to insert a node at a specific index
int DoubleLinkedlistInsert(int data, int index, Node*& head) { // head is passed by reference
    Node* newNode = new Node(data); // Create a new node with the given data
    if (index < 0) { // Check for invalid index (negative)
        cout << "Invalid index" << endl;
        return -1; // Return error code
    }
    if (head == nullptr) { // Check if the list is empty
        if (index == 0) { // If the list is empty and index is 0
            head = newNode; // Make the new node the head
            return 0; // Return success code
        }
        else { // If the list is empty and index is not 0
            cout << "Index out of bounds" << endl;
            return -1; // Return error code
        }
    }

    if (index == 0) { // If index is 0, insert at the beginning
        newNode->next = head; // New node's next points to the current head
        head->prev = newNode; // Current head's previous points to the new node
        head = newNode; // Update the head to the new node
        return 0; // Return success code
    }

    Node* temp = head; // Start from the head
    for (int i = 0; i < index - 1; i++) { // Traverse to the node before the insertion point
        if (temp->next == nullptr) { // Check if index is out of bounds
            cout << "Index out of bounds" << endl;
            return -1; // Return error code
        }
        temp = temp->next; // Move to the next node
    }
    newNode->next = temp->next; // New node's next points to the node after the insertion point
    if (temp->next != nullptr) { // If there's a node after the insertion point
        temp->next->prev = newNode; // The node after the insertion point's previous points to the new node
    }
    temp->next = newNode; // The node before the insertion point's next points to the new node
    newNode->prev = temp; // New node's previous points to the node before the insertion point
    return 0; // Return success code
}

// Function to delete a node at a specific index
int DoubleLinkedlistDelete(int index, Node*& head) { // head is passed by reference
    if (head == nullptr || index < 0) { // Check for empty list or invalid index
        cout << "Invalid index or empty list" << endl;
        return -1; // Return error code
    }
    Node* temp = head; // Start from the head
    if (index == 0) { // If index is 0, delete the head
        head = temp->next; // Update the head to the next node
        if (head != nullptr) { // If there's a new head
            head->prev = nullptr; // New head's previous points to null
        }
        delete temp; // Delete the old head
        return 0; // Return success code
    }
    for (int i = 0; i < index; i++) { // Traverse to the node to be deleted
        if (temp == nullptr) { // Check if index is out of bounds
            cout << "Index out of bounds" << endl;
            return -1; // Return error code
        }
        temp = temp->next; // Move to the next node
    }
    if (temp->prev != nullptr) { // If there's a node before the node to be deleted
        temp->prev->next = temp->next; // Previous node's next points to the node after the node to be deleted
    }
    if (temp->next != nullptr) { // If there's a node after the node to be deleted
        temp->next->prev = temp->prev; // Next node's previous points to the node before the node to be deleted
    }
    delete temp; // Delete the node
    return 0; // Return success code
}

// Function to print the doubly linked list
void PrintList(Node* head) {
    Node* temp = head; // Start from the head
    while (temp != nullptr) { // Traverse until the end of the list
        cout << temp->data << " <-> "; // Print the data and the double arrow
        temp = temp->next; // Move to the next node
    }
    cout << "NULL" << endl; // Print NULL to indicate the end of the list
}

int main() {
    Node* head = nullptr; // Initialize an empty list

    DoubleLinkedlistInsert(50, 0, head); // Insert 50 at index 0
    DoubleLinkedlistInsert(70, 1, head); // Insert 70 at index 1
    DoubleLinkedlistInsert(90, 2, head); // Insert 90 at index 2
    DoubleLinkedlistInsert(10, 1, head); // Insert 10 at index 1

    cout << "List after insertions:" << endl;
    PrintList(head); // Print the list

    DoubleLinkedlistDelete(2, head); // Delete the node at index 2
    cout << "List after deleting index 2:" << endl;
    PrintList(head); // Print the list after deletion

    return 0; // Exit the program
}