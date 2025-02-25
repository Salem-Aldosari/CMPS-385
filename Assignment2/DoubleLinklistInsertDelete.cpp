#include <iostream>
using namespace std;


struct Node {
    int data;     
    Node* prev;   
    Node* next;   

    Node(int val) : data(val), prev(nullptr), next(nullptr) {} 
};


int DoubleLinkedlistInsert(int data, int index, Node*& head) { 
    Node* newNode = new Node(data); 
    if (index < 0) { 
        cout << "Invalid index" << endl;
        return -1; 
    }
    if (head == nullptr) { 
        if (index == 0) { 
            head = newNode; 
            return 0; 
        }
        else { 
            cout << "Index out of bounds" << endl;
            return -1; 
        }
    }

    if (index == 0) { 
        newNode->next = head; 
        head->prev = newNode; 
        head = newNode; 
        return 0; 
    }

    Node* temp = head; 
    for (int i = 0; i < index - 1; i++) { 
        if (temp->next == nullptr) { 
            cout << "Index out of bounds" << endl;
            return -1; 
        }
        temp = temp->next; 
    }
    newNode->next = temp->next; 
    if (temp->next != nullptr) { 
        temp->next->prev = newNode; 
    }
    temp->next = newNode; 
    newNode->prev = temp; 
    return 0; 
}


int DoubleLinkedlistDelete(int index, Node*& head) { 
    if (head == nullptr || index < 0) { 
        cout << "Invalid index or empty list" << endl;
        return -1; 
    }
    Node* temp = head; 
    if (index == 0) { 
        head = temp->next; 
        if (head != nullptr) { 
            head->prev = nullptr; 
        }
        delete temp; 
        return 0; 
    }
    for (int i = 0; i < index; i++) { 
        if (temp == nullptr) { 
            cout << "Index out of bounds" << endl;
            return -1; 
        }
        temp = temp->next; 
    }
    if (temp->prev != nullptr) { 
        temp->prev->next = temp->next; 
    }
    if (temp->next != nullptr) { 
        temp->next->prev = temp->prev; 
    }
    delete temp; 
    return 0; 
}


void PrintList(Node* head) {
    Node* temp = head; 
    while (temp != nullptr) { 
        cout << temp->data << " <-> "; 
        temp = temp->next; 
    }
    cout << "NULL" << endl; 
}

int main() {
    Node* head = nullptr; 

    DoubleLinkedlistInsert(50, 0, head); 
    DoubleLinkedlistInsert(70, 1, head); 
    DoubleLinkedlistInsert(90, 2, head); 
    DoubleLinkedlistInsert(10, 1, head); 

    cout << "List after insertions:" << endl;
    PrintList(head); 

    DoubleLinkedlistDelete(2, head); 
    cout << "List after deleting index 2:" << endl;
    PrintList(head); 

    return 0; 
}
