#include <iostream> <
using namespace std; 
// Function to perform a binary search on a sorted array
// array[]: The array to search within. It must be sorted in ascending order for binary search to work correctly.
// size: The number of elements in the array.
// target: The value to search for in the array.
int binarySearch(int array[], int size, int target) {
    // Initialize 'first' to the index of the first element
    int first = 0;
    // Initialize 'last' to the index of the last element
    int last = size - 1;

    // Loop continues as long as the 'first' index is less than or equal to the 'last' index
    // This condition ensures that the search space is still valid.
    while (first <= last) {
        // Calculate the middle index of the current search space.
        // Using (first + last) / 2 can potentially lead to integer overflow if first and last are very large.
        // A safer alternative is first + (last - first) / 2.
        int middle = (first + last) / 2;

        // Check if the element at the middle index is the target
        if (array[middle] == target) {
            // If found, print a success message and return the index of the target
            cout << "Target " << target << " found at index " << middle << "." << endl;
            return middle;
        }
        // If the target is less than the element at the middle index
        else if (target < array[middle]) {
            // The target must be in the lower half of the current search space.
            // Adjust 'last' to be one less than the middle index.
            last = middle - 1;
        }
        // If the target is greater than the element at the middle index
        else { // target > array[middle]
            // The target must be in the upper half of the current search space.
            // Adjust 'first' to be one more than the middle index.
            first = middle + 1;
        }
    }

    // If the loop finishes, it means the target was not found in the array.
    // Print a "not found" message and return -1 (a common convention to indicate failure to find).
    cout << "Target " << target << " not found." << endl;
    return -1;
}

// Main function where the program execution begins
int main() {
    // Declare and initialize a sorted integer array for testing the binary search
    int myArray[] = { 70, 121, 421, 590, 791, 860, 1048, 2120 };
    // Calculate the size of the array dynamically.
    // sizeof(myArray) gives the total size of the array in bytes.
    // sizeof(myArray[0]) gives the size of a single element in bytes.
    // Dividing them gives the number of elements in the array.
    int size = sizeof(myArray) / sizeof(myArray[0]);

    // Call binarySearch to find a target that exists in the array (found case)
    binarySearch(myArray, size, 421); // Expected output: "Target 421 found at index 2."

    // Call binarySearch to find a target that does not exist in the array (not found case)
    binarySearch(myArray, size, 893); // Expected output: "Target 893 not found."

    // Indicate successful program execution
    return 0;
}