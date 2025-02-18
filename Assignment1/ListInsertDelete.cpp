#include <iostream> 

using namespace std; 

// Structure to represent a node in the linked list
struct Node {
    int data;       // Data stored in the node
    Node* next;     // Pointer to the next node in the list
};

// Function to insert a node at a specified index
void insertNode(int data, int index, Node*& head) {
    Node* newNode = new Node(); // Create a new node dynamically
    newNode->data = data;       // Assign the given data to the new node
    newNode->next = nullptr;    // Initialize the next pointer of the new node to null

    if (index == 0) {          // If inserting at the beginning (index 0)
        newNode->next = head;   // Make the new node point to the current head
        head = newNode;        // Update the head to point to the new node
        return;                // Exit the function
    }

    Node* current = head;      // Start traversing from the head
    for (int i = 0; current != nullptr && i < index - 1; i++) { // Iterate up to the node before the insertion point
        current = current->next; // Move to the next node
    }

    if (current == nullptr) {  // If the index is out of bounds
        cerr << "Index out of bounds" << endl; // Print an error message to cerr
        delete newNode;      // Deallocate the memory of the new node to avoid memory leaks
        return;                // Exit the function
    }

    newNode->next = current->next; // Make the new node's next pointer point to the node after the current node
    current->next = newNode;     // Make the current node's next pointer point to the new node
}

// Function to delete a node at a specified index
void deleteNode(int index, Node*& head) {
    if (head == nullptr) {      // If the list is empty
        cerr << "List is empty" << endl; // Print an error message to cerr
        return;                // Exit the function
    }

    if (index == 0) {          // If deleting the first node (index 0)
        Node* temp = head;      // Store the current head in a temporary pointer
        head = head->next;    // Move the head to the next node
        delete temp;          // Deallocate the memory of the old head
        return;                // Exit the function
    }

    Node* current = head;      // Start traversing from the head
    Node* previous = nullptr;   // Initialize a pointer to keep track of the previous node
    for (int i = 0; current != nullptr && i < index; i++) { // Iterate up to the node to be deleted
        previous = current;    // Store the current node as the previous node
        current = current->next; // Move to the next node
    }

    if (current == nullptr) {  // If the index is out of bounds
        cerr << "Index out of bounds" << endl; // Print an error message to cerr
        return;                // Exit the function
    }

    previous->next = current->next; // Make the previous node's next pointer point to the node after the current node
    delete current;             // Deallocate the memory of the deleted node
}

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;      // Start traversing from the head
    while (current != nullptr) { // Iterate until the end of the list
        cout << current->data << " -> "; // Print the data of the current node followed by " -> "
        current = current->next; // Move to the next node
    }
    cout << "NULL" << endl;    // Print "NULL" to indicate the end of the list
}

int main() {
    Node* head = nullptr;      // Initialize an empty linked list (head is nullptr)

    insertNode(60, 0, head);   // Insert 10 at index 0 (beginning)
    insertNode(90, 1, head);   // Insert 90 at index 1
    insertNode(20, 2, head);   // Insert 20 at index 2
    insertNode(55, 1, head);   // Insert 55 at index 1 (between 10 and 20)

    cout << "Linked list after insertions: "; // Print a message before printing the list
    printList(head);            // Print the linked list

    deleteNode(2, head);       // Delete the node at index 2 (originally 30)

    cout << "Linked list after deletion: ";  // Print a message before printing the list
    printList(head);            // Print the linked list

    deleteNode(0, head);       // Delete the first node

    cout << "Linked list after deleting first node: ";  // Print a message before printing the list
    printList(head);            // Print the linked list


    return 0;
}