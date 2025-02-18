#include <iostream> 

using namespace std; 


struct Node {
    int data;       
    Node* next;     
};


void insertNode(int data, int index, Node*& head) {
    Node* newNode = new Node(); 
    newNode->data = data;       
    newNode->next = nullptr;   

    if (index == 0) {          
        newNode->next = head;   
        head = newNode;        
        return;                
    }

    Node* current = head;      
    for (int i = 0; current != nullptr && i < index - 1; i++) { 
        current = current->next; 
    }

    if (current == nullptr) {  
        cerr << "Index out of bounds" << endl; 
        delete newNode;      
        return;                
    }

    newNode->next = current->next; 
    current->next = newNode;     
}


void deleteNode(int index, Node*& head) {
    if (head == nullptr) {      
        cerr << "List is empty" << endl;
        return;                
    }

    if (index == 0) {          
        Node* temp = head;      
        head = head->next;    
        delete temp;          
        return;                
    }

    Node* current = head;      
    Node* previous = nullptr;   
    for (int i = 0; current != nullptr && i < index; i++) { 
        previous = current;    
        current = current->next; 
    }

    if (current == nullptr) {  
        cerr << "Index out of bounds" << endl; 
        return;                
    }

    previous->next = current->next; 
    delete current;             
}


void printList(Node* head) {
    Node* current = head;      
    while (current != nullptr) { 
        cout << current->data << " -> "; 
        current = current->next; 
    }
    cout << "NULL" << endl;    
}

int main() {
    Node* head = nullptr;      

    insertNode(60, 0, head);   
    insertNode(90, 1, head);   
    insertNode(20, 2, head);   
    insertNode(55, 1, head);  

    cout << "Linked list after insertions: "; 
    printList(head);            

    deleteNode(2, head);       

    cout << "Linked list after deletion: ";  
    printList(head);           

    deleteNode(0, head);       

    cout << "Linked list after deleting first node: ";  
    printList(head);            


    return 0;
}
