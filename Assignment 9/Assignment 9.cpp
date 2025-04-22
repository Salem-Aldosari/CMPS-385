#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For runtime_error

using namespace std;

const int ORDER = 3; // Max keys per node

struct BTreeNode {
    vector<int> keys;
    vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf) : isLeaf(leaf) {}
};

// Helper function to insert into a node at correct position
void insertKeySorted(vector<int>& keys, int key) {
    auto it = upper_bound(keys.begin(), keys.end(), key);
    keys.insert(it, key);
}

class BTree {
public:
    BTreeNode* root;

    BTree() : root(new BTreeNode(true)) {}

    void insert(int key) {
        if (root->keys.size() == ORDER) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

private:
    void insertNonFull(BTreeNode* node, int key) {
        if (node->isLeaf) {
            insertKeySorted(node->keys, key);
            if (node->keys.size() == ORDER) {
                splitLeaf(getParent(root, node), node);
            }
        }
        else {
            int i = 0;
            while (i < node->keys.size() && key > node->keys[i]) i++;

            if (node->children[i]->keys.size() == ORDER) {
                splitChild(node, i);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key);
            if (node->keys.size() == ORDER) {
                splitInternal(getParent(root, node), node);
            }
        }
    }

    void splitChild(BTreeNode* parent, int index) {
        BTreeNode* fullChild = parent->children[index];
        int mid = ORDER / 2;
        int midKey = fullChild->keys[mid];

        BTreeNode* rightChild = new BTreeNode(fullChild->isLeaf);
        rightChild->keys.assign(fullChild->keys.begin() + mid + 1, fullChild->keys.end());
        fullChild->keys.resize(mid);

        if (!fullChild->isLeaf) {
            rightChild->children.assign(fullChild->children.begin() + mid + 1, fullChild->children.end());
            fullChild->children.resize(mid + 1);
        }

        if (parent) {
            insertKeySorted(parent->keys, midKey);
            parent->children.insert(parent->children.begin() + index + 1, rightChild);
            if (parent->keys.size() == ORDER) {
                splitInternal(getParent(root, parent), parent);
            }
        }
        else {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->keys.push_back(midKey);
            newRoot->children.push_back(fullChild);
            newRoot->children.push_back(rightChild);
            root = newRoot;
        }
    }

    void splitLeaf(BTreeNode* parent, BTreeNode* leafToSplit) {
        BTreeNode* newSibling = new BTreeNode(true);
        int mid = ORDER / 2;
        int midKey = leafToSplit->keys[mid];

        newSibling->keys.assign(leafToSplit->keys.begin() + mid + 1, leafToSplit->keys.end());
        leafToSplit->keys.resize(mid);

        if (parent) {
            insertKeySorted(parent->keys, midKey);
            auto it = find(parent->children.begin(), parent->children.end(), leafToSplit);
            if (it != parent->children.end()) {
                parent->children.insert(it + 1, newSibling);
            }
            if (parent->keys.size() == ORDER) {
                splitInternal(getParent(root, parent), parent);
            }
        }
        else {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->keys.push_back(midKey);
            newRoot->children.push_back(leafToSplit);
            newRoot->children.push_back(newSibling);
            root = newRoot;
        }
    }

    void splitInternal(BTreeNode* parent, BTreeNode* nodeToSplit) {
        BTreeNode* newSibling = new BTreeNode(false);
        int mid = ORDER / 2;
        int midKey = nodeToSplit->keys[mid];

        newSibling->keys.assign(nodeToSplit->keys.begin() + mid + 1, nodeToSplit->keys.end());
        nodeToSplit->keys.resize(mid);

        newSibling->children.assign(nodeToSplit->children.begin() + mid + 1, nodeToSplit->children.end());
        nodeToSplit->children.resize(mid + 1);

        if (parent) {
            insertKeySorted(parent->keys, midKey);
            auto it = find(parent->children.begin(), parent->children.end(), nodeToSplit);
            if (it != parent->children.end()) {
                parent->children.insert(it + 1, newSibling);
            }
            if (parent->keys.size() == ORDER) {
                splitInternal(getParent(root, parent), parent);
            }
        }
        else {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->keys.push_back(midKey);
            newRoot->children.push_back(nodeToSplit);
            newRoot->children.push_back(newSibling);
            root = newRoot;
        }
    }

    BTreeNode* getParent(BTreeNode* current, BTreeNode* node) {
        if (current == nullptr || current == node) return nullptr;
        for (BTreeNode* child : current->children) {
            if (child == node) return current;
            BTreeNode* parent = getParent(child, node);
            if (parent) return parent;
        }
        return nullptr;
    }

public:
    void printTree(BTreeNode* node, int level = 0, int childIndex = -1) {
        if (!node) return;
        cout << string(level * 4, ' ');
        if (childIndex >= 0) cout << "Child " << childIndex << ": ";
        cout << "[";
        for (size_t i = 0; i < node->keys.size(); ++i) {
            cout << node->keys[i];
            if (i < node->keys.size() - 1) cout << " | ";
        }
        cout << "]";
        if (node->isLeaf) cout << " (Leaf)";
        cout << "\n";

        for (size_t i = 0; i < node->children.size(); ++i)
            printTree(node->children[i], level + 1, static_cast<int>(i));
    }

    void print() {
        cout << "\n=== Final B-Tree Structure ===\n";
        printTree(root);
        cout << "==============================\n";
    }
};

// Assignment-style wrapper function
int insetBminustree(int key, BTree& B) {
    B.insert(key);
    return 1;
}

// Main function with required test case
int main() {
    BTree tree;
    vector<int> values = { 78, 52, 81, 40, 33, 90, 85, 20, 38 };

    for (int val : values)
        insetBminustree(val, tree);

    tree.print();
    return 0;
}