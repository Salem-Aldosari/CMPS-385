#include <iostream> 
#include <stdexcept> 
using namespace std; 

// Definition of the AVLNode class, representing a node in an AVL tree
class AVLNode {
public:
    int key;     // The value stored in the node
    int height;  // The height of the node in the tree
    AVLNode* left;  // Pointer to the left child node
    AVLNode* right; // Pointer to the right child node

    // Constructor for the AVLNode class
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    // Initializes a new AVLNode with the given key, height set to 1 (for a single node), and no children.

    // Helper function to get the height of a node. Returns 0 if the node is null.
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    // Updates the height of the current node based on the heights of its children.
    void adjustHeight() {
        height = 1 + max(getHeight(left), getHeight(right));
        // The height of a node is 1 (for the node itself) plus the maximum height of its left and right subtrees.
    }

    // Calculates the balance factor of the current node.
    // Balance factor is defined as the height of the right subtree minus the height of the left subtree.
    int getBalanceFactor() {
        return getHeight(right) - getHeight(left);
    }

    // Checks if the current node is null (empty).
    bool isEmpty() {
        return this == nullptr;
    }

    // Returns the right child of the current node.
    AVLNode* getRightAVL() {
        return right;
    }

    // In-place Right Rotation (Slide 16 logic)
    // This operation is used to rebalance the AVL tree when the left subtree is too heavy.
    void rightRotate() {
        // Check for invalid operation: cannot rotate if the node is empty or has no left child.
        if (isEmpty() || left == nullptr)
            throw runtime_error("Invalid Operation: Cannot right-rotate");

        // Store the right child of the current left child temporarily.
        AVLNode* temp = right;
        // Make the current node's right child the original left child.
        right = left;
        // Make the current node's left child the left child of the original left child.
        left = right->left;
        // Make the left child of the new right child (originally the left child) the original right child of the new right child.
        right->left = right->right;
        // Make the right child of the new right child the temporarily stored right child of the original node.
        right->right = temp;

        // Swap the keys of the current node and its new right child.
        int tmpKey = key;
        key = right->key;
        right->key = tmpKey;

        // Update the heights of the affected nodes.
        right->adjustHeight();
        adjustHeight();
    }

    // In-place Left Rotation (mirrored logic of Slide 16)
    // This operation is used to rebalance the AVL tree when the right subtree is too heavy.
    void leftRotate() {
        // Check for invalid operation: cannot rotate if the node is empty or has no right child.
        if (isEmpty() || right == nullptr)
            throw runtime_error("Invalid Operation: Cannot left-rotate");

        // Store the left child of the current right child temporarily.
        AVLNode* temp = left;
        // Make the current node's left child the original right child.
        left = right;
        // Make the current node's right child the right child of the original right child.
        right = left->right;
        // Make the right child of the new left child (originally the right child) the original left child of the new left child.
        left->right = left->left;
        // Make the left child of the new left child the temporarily stored left child of the original node.
        left->left = temp;

        // Swap the keys of the current node and its new left child.
        int tmpKey = key;
        key = left->key;
        left->key = tmpKey;

        // Update the heights of the affected nodes.
        left->adjustHeight();
        adjustHeight();
    }

    // Performs an in-order traversal of the subtree rooted at the current node and prints the keys.
    // In an in-order traversal, the left subtree is visited first, then the root, and finally the right subtree.
    void printInOrder() {
        if (left) left->printInOrder(); // Recursively print the left subtree
        cout << key << " ";             // Print the key of the current node
        if (right) right->printInOrder(); // Recursively print the right subtree
    }
};

int main() {
    // Test Right Rotation
    // Create a skewed tree where a right rotation should balance it.
    AVLNode* root = new AVLNode(30);
    root->left = new AVLNode(20);
    root->left->left = new AVLNode(10);

    cout << "Before Right Rotation (InOrder): ";
    root->printInOrder(); // Output: 10 20 30
    cout << endl;

    root->rightRotate(); // Perform the right rotation on the root.

    cout << "After Right Rotation (InOrder): ";
    root->printInOrder(); // Output: 20 10 30 (Note: The root has changed)
    cout << endl;

    // Test Left Rotation
    // Create a skewed tree where a left rotation should balance it.
    AVLNode* root2 = new AVLNode(10);
    root2->right = new AVLNode(20);
    root2->right->right = new AVLNode(30);

    cout << "\nBefore Left Rotation (InOrder): ";
    root2->printInOrder(); // Output: 10 20 30
    cout << endl;

    root2->leftRotate(); // Perform the left rotation on the root.

    cout << "After Left Rotation (InOrder): ";
    root2->printInOrder(); // Output: 20 10 30 (Note: The root has changed)
    cout << endl;

    return 0; // Indicate successful program execution
}