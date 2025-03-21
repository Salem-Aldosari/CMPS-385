#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
    vector<int> heap; // Vector to store the heap elements

    // Reheapification upward (Heapify-Up)
    void heapifyUp(int index) {
        // While the current index is not the root (index 0)
        while (index > 0) {
            int parent = (index - 1) / 2; // Calculate the parent index
            // If the current element is greater than its parent
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]); // Swap the elements
                index = parent; // Move the index to the parent
            }
            else {
                break; // Heap property is satisfied, exit the loop
            }
        }
    }

    // Reheapification downward (Heapify-Down)
    void heapifyDown(int index) {
        int size = heap.size(); // Get the size of the heap
        while (true) {
            int leftChild = 2 * index + 1; // Calculate the left child index
            int rightChild = 2 * index + 2; // Calculate the right child index
            int largest = index; // Initialize the largest as the current index

            // If the left child exists and is greater than the current largest
            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild; // Update the largest index
            }
            // If the right child exists and is greater than the current largest
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild; // Update the largest index
            }
            // If the largest is not the current index (a swap is needed)
            if (largest != index) {
                swap(heap[index], heap[largest]); // Swap the elements
                index = largest; // Move the index to the largest child
            }
            else {
                break; // Heap property is satisfied, exit the loop
            }
        }
    }

public:
    // Insert a new element and restore heap property
    void insert(int value) {
        heap.push_back(value); // Add the new value to the end of the heap
        heapifyUp(heap.size() - 1); // Reheapify upward to maintain heap property
    }

    // Remove the top (max) element from the heap
    int removeMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty"); // Throw an error if the heap is empty
        }
        int maxValue = heap[0]; // Store the maximum value (root)
        heap[0] = heap.back(); // Replace the root with the last element
        heap.pop_back(); // Remove the last element
        if (!heap.empty()) {
            heapifyDown(0); // Reheapify downward to maintain heap property
        }
        return maxValue; // Return the removed maximum value
    }

    // Display heap elements
    void display() {
        for (int val : heap) {
            cout << val << " "; // Print each element of the heap
        }
        cout << endl; // Print a newline character
    }
};

int main() {
    MaxHeap heap;

    // Testing insertion (Reheapification upward)
    heap.insert(57);
    heap.insert(89);
    heap.insert(90);
    heap.insert(89);
    heap.insert(91);

    cout << "Heap after insertions: ";
    heap.display();

    // Testing deletion (Reheapification downward)
    cout << "Removing max: " << heap.removeMax() << endl;
    cout << "Heap after deletion: ";
    heap.display();

    return 0;
}