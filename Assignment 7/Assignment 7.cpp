#include <iostream> // Include the iostream library for input and output operations.
using namespace std; // Use the standard namespace to avoid writing std:: before cout, endl, etc.

// Node structure for Binary Search Tree
struct Node {
    int key;       // Data stored in the node.  This is the value that determines the node's position in the BST.
    Node* left;    // Pointer to the left child node.  Left children have keys *less than* the parent.
    Node* right;   // Pointer to the right child node. Right children have keys *greater than* the parent.

    // Constructor for the Node struct.  Initializes a new node with a given key value.
    // The left and right pointers are initialized to nullptr (null), indicating that the new node initially has no children.
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// This function inserts a new node with the value 'x' into the Binary Search Tree.
// 'root' is a pointer to the root of the tree (or subtree) where the insertion should occur.
Node* InsertBST(int x, Node* root) {
    // Base case: If the current subtree is empty (root is null), we've found the insertion point.
    // Create a new node with the value 'x' and return a pointer to it.  This new node becomes the new child.
    if (root == nullptr) return new Node(x);

    // Recursive case 1: If the value 'x' is less than the current node's key,
    // the new node should be inserted into the *left* subtree.
    // Recursively call InsertBST on the left child of the current node.
    // The result of this recursive call (which will be the new left child) is assigned to root->left.
    if (x < root->key) {
        root->left = InsertBST(x, root->left);
    }
    // Recursive case 2: If the value 'x' is greater than the current node's key,
    // the new node should be inserted into the *right* subtree.
    // Recursively call InsertBST on the right child of the current node.
    // The result of this recursive call (which will be the new right child) is assigned to root->right.
    else if (x > root->key) {
        root->right = InsertBST(x, root->right);
    }
    // Implicit case: If x == root->key, the value 'x' is already in the tree.
    // In this implementation, we do *not* insert duplicate keys.  The function simply returns the original root.
    return root;
}

// This function finds the node with the smallest key in the subtree rooted at 'root'.
// The smallest key in a BST is always found by traversing as far left as possible.
Node* FindMin(Node* root) {
    // Keep going to the left child as long as there is a left child.
    while (root && root->left != nullptr)
        root = root->left;
    // When the loop finishes, 'root' will point to the leftmost node, which has the smallest key.
    return root;
}


// This function deletes the node with the key 'x' from the Binary Search Tree.
// 'root' is a pointer to the root of the tree (or subtree) where the deletion should occur.
Node* DeleteBST(int x, Node* root) {
    // Base case 1: If the tree is empty (root is null), there's nothing to delete.  Return null.
    if (root == nullptr) return root;

    // Recursive case 1: If the key 'x' is less than the current node's key,
    // the node to be deleted is in the *left* subtree.  Recursively call DeleteBST on the left child.
    if (x < root->key) {
        root->left = DeleteBST(x, root->left);
    }
    // Recursive case 2: If the key 'x' is greater than the current node's key,
    // the node to be deleted is in the *right* subtree.  Recursively call DeleteBST on the right child.
    else if (x > root->key) {
        root->right = DeleteBST(x, root->right);
    }
    // Base case 2: If the key 'x' is equal to the current node's key, we've found the node to delete.
    else {
        // Case 1: The node to be deleted has *no left child*.
        // Replace the node with its right child (which might be null).
        if (root->left == nullptr) {
            Node* temp = root->right; // Store the right child temporarily.
            delete root;             // Delete the current node.
            return temp;            // Return the right child (which is now the new child of the parent).
        }
        // Case 2: The node to be deleted has *no right child*.
        // Replace the node with its left child.
        else if (root->right == nullptr) {
            Node* temp = root->left;  // Store the left child temporarily.
            delete root;              // Delete the current node.
            return temp;             // Return the left child (which is now the new child of the parent).
        }
        // Case 3: The node to be deleted has *two children*.
        // Find the in-order successor (the smallest node in the right subtree).
        else {
            Node* successor = FindMin(root->right);
            // Replace the key of the node to be deleted with the key of its successor.
            root->key = successor->key;
            // Recursively delete the successor from its original position in the right subtree.
            // This is safe because the successor, being the smallest in the right subtree,
            // is guaranteed to have either no children or only a right child.
            root->right = DeleteBST(successor->key, root->right);
        }
    }
    // Return the (possibly modified) root of the current subtree.
    return root;
}

// In-order traversal for display
// This function performs an in-order traversal of the Binary Search Tree.
// In-order traversal visits the left subtree, then the root, then the right subtree.
// For a BST, this prints the keys in sorted order (ascending).
void InOrder(Node* root) {
    // Base case: If the current node is null, the subtree is empty, so return.
    if (!root) return;
    // Recursively traverse the left subtree.
    InOrder(root->left);
    // Print the key of the current node.
    cout << root->key << " ";
    // Recursively traverse the right subtree.
    InOrder(root->right);
}

// Main function to demonstrate insert and delete operations
int main() {
    Node* T = nullptr; // Initialize an empty Binary Search Tree.  'T' will point to the root.

    // Insert nodes into the BST.  The order of insertion affects the structure of the tree.
    T = InsertBST(200, T); // Insert 200 as the root.
    T = InsertBST(150, T); // Insert 150 into the left subtree.
    T = InsertBST(300, T); // Insert 300 into the right subtree.
    T = InsertBST(260, T); // Insert 260 into the left subtree of 300.
    T = InsertBST(370, T); // Insert 370 into the right subtree of 300.
    // The resulting BST looks like this:
    //
    //      200
    //     /  \
    //    150   300
    //        /  \
    //       260   370

    cout << "In-order after insertions: ";
    InOrder(T); // Call InOrder to print the keys in sorted order.  Output: 150 200 260 300 370
    cout << endl;

    // Delete a node with two children.  Here, we delete the node with key 300.
    // The successor of 300 is 370, so 300 will be replaced by 370, and 370 will be deleted from its original position.
    T = DeleteBST(300, T);
    // The BST now looks like this:
    //
    //      200
    //     /  \
    //    150   370
    //        /
    //       260

    cout << "In-order after deleting 300: ";
    InOrder(T); // Print the keys again in sorted order. Output: 150 200 260 370
    cout << endl;

    return 0; // Indicate successful program execution.
}
