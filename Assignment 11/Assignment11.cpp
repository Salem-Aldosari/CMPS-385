#include <iostream>  
#include <algorithm> 

/**
 * @brief Sorts an array using the Bubble Sort algorithm.
 *
 * This function implements the Bubble Sort algorithm, which repeatedly steps through the list,
 * compares adjacent elements and swaps them if they are in the wrong order. The pass through the
 * list is repeated until no swaps are needed, which indicates that the list is sorted.
 * It includes an optimization to detect if the array becomes sorted early.
 *
 * @tparam Type The data type of the elements in the array (e.g., int, float, custom objects).
 * @param array A constant pointer to the beginning of the array to be sorted.
 * The array will be modified in-place.
 * @param n A constant integer representing the number of elements in the array.
 */
template <typename Type>
void bubble(Type* const array, int const n) {
    // Outer loop: Controls the number of passes.
    // In each pass, the largest unsorted element "bubbles" to its correct position
    // at the end of the unsorted portion of the array.
    // 'i' represents the last unsorted element's index.
    // We iterate from n-1 down to 1 because the largest element is placed at array[i]
    // after each inner loop completion, so we don't need to check it again.
    for (int i = n - 1; i > 0; --i) {
        // Flag to optimize the algorithm: If no swaps occur in an entire pass,
        // it means the array is already sorted, and we can stop early.
        bool sorted = true;

        // Inner loop: Compares adjacent elements and swaps them if they are in the wrong order.
        // This loop iterates up to 'i' because elements from array[i+1] to array[n-1]
        // are already in their correct sorted positions.
        for (int j = 0; j < i; ++j) {
            // Compare the current element with the next element.
            if (array[j] > array[j + 1]) {
                // If they are in the wrong order, swap them.
                std::swap(array[j], array[j + 1]);
                // A swap occurred, so the array is not yet fully sorted in this pass.
                sorted = false;
            }
        }

        // Optimization: If no swaps were made in the inner loop (i.e., 'sorted' is still true),
        // it means the array is now completely sorted.
        if (sorted) {
            break; // Exit the outer loop early.
        }
    }
}

/**
 * @brief Main function to demonstrate the Bubble Sort algorithm.
 *
 * This function initializes an integer array, prints its original state,
 * calls the bubble sort function to sort it, and then prints the sorted array.
 *
 * @return 0 if the program executes successfully.
 */
int main() {
    // Declare and initialize an integer array.
    int arr[] = { 38, 29, 17, 42, 53 };
    // Calculate the number of elements in the array.
    // sizeof(arr) gives the total size of the array in bytes.
    // sizeof(arr[0]) gives the size of one element in bytes.
    // Dividing them gives the number of elements.
    int n = sizeof(arr) / sizeof(arr[0]);

    // Print the original unsorted array.
    std::cout << "Original array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl; // Add a newline for better formatting.

    // Call the bubble sort function to sort the array.
    bubble(arr, n);

    // Print the sorted array.
    std::cout << "Sorted array:   "; // Use spaces for alignment.
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl; // Add a newline at the end.

    return 0; // Indicate successful program execution.
}