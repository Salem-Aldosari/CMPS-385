#include <iostream>
#define TABLE_SIZE 907 // Define the size of the hash table

using namespace std;

int hashTable[TABLE_SIZE]; // Declare the hash table as an integer array

// Initialize hash table
void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) { // Loop through each index of the hash table
        hashTable[i] = -1; // Set each element to -1, indicating an empty slot
    }
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE; // Calculate the hash index using the modulo operator
}

// Linear probing insertion
int HashInsertion(int key) {
    int index = hashFunction(key); // Calculate the initial hash index
    int originalIndex = index; // Store the original index to detect full table

    for (int i = 0; i < TABLE_SIZE; i++) { // Loop through the table, probing for an empty slot
        int newIndex = (index + i) % TABLE_SIZE; // Calculate the new index using linear probing
        if (hashTable[newIndex] == -1) { // Check if the slot is empty
            hashTable[newIndex] = key; // Insert the key into the empty slot
            return newIndex; // Return the index where the key was inserted
        }
    }

    return -1; // Table is full, insertion failed
}

// Linear probing deletion
int HashDeletion(int key) {
    int index = hashFunction(key); // Calculate the initial hash index

    for (int i = 0; i < TABLE_SIZE; i++) { // Loop through the table, probing for the key
        int newIndex = (index + i) % TABLE_SIZE; // Calculate the new index using linear probing
        if (hashTable[newIndex] == key) { // Check if the key is found
            hashTable[newIndex] = -1; // Mark the slot as empty (deleted)
            return newIndex; // Return the index where the key was deleted
        }
        else if (hashTable[newIndex] == -1) { // Check if an empty slot is encountered before finding the key
            return -1; // Key not found
        }
    }

    return -1; // Key not found after full table scan
}

// Display hash table
void displayHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) { // Loop through each index of the hash table
        if (hashTable[i] != -1) { // Check if the slot is occupied
            cout << "Index " << i << ": " << hashTable[i] << endl; // Display the index and the key
        }
    }
}

int main() {
    initializeHashTable(); // Initialize the hash table

    // Insert example keys
    HashInsertion(100);
    HashInsertion(130);
  

    // Display table
    cout << "Hash table after insertion:" << endl;
    displayHashTable();

    // Delete key
    HashDeletion(130);

    // Display table after deletion
    cout << "\nHash table after deletion:" << endl;
    displayHashTable();

    return 0;
}