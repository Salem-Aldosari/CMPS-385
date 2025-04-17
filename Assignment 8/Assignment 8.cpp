#include <iostream> 
#include <stdexcept> 
using namespace std; 


class AVLNode {
public:
    int key;     
    int height;  
    AVLNode* left; 
    AVLNode* right; 

    
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    

    
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    
    void adjustHeight() {
        height = 1 + max(getHeight(left), getHeight(right));
        
    }

    
    
    int getBalanceFactor() {
        return getHeight(right) - getHeight(left);
    }

    
    bool isEmpty() {
        return this == nullptr;
    }

    
    AVLNode* getRightAVL() {
        return right;
    }

    
    
    void rightRotate() {
        
        if (isEmpty() || left == nullptr)
            throw runtime_error("Invalid Operation: Cannot right-rotate");

        
        AVLNode* temp = right;
        
        right = left;
        
        left = right->left;
        
        right->left = right->right;
        
        right->right = temp;

       
        int tmpKey = key;
        key = right->key;
        right->key = tmpKey;

        
        right->adjustHeight();
        adjustHeight();
    }

    
    
    void leftRotate() {
        
        if (isEmpty() || right == nullptr)
            throw runtime_error("Invalid Operation: Cannot left-rotate");

        
        AVLNode* temp = left;
        
        left = right;
        
        right = left->right;
        
        left->right = left->left;
        
        left->left = temp;

        
        int tmpKey = key;
        key = left->key;
        left->key = tmpKey;

        
        left->adjustHeight();
        adjustHeight();
    }

    
    
    void printInOrder() {
        if (left) left->printInOrder(); 
        cout << key << " ";             
        if (right) right->printInOrder(); 
    }
};

int main() {
    
    
    AVLNode* root = new AVLNode(30);
    root->left = new AVLNode(20);
    root->left->left = new AVLNode(10);

    cout << "Before Right Rotation (InOrder): ";
    root->printInOrder(); 
    cout << endl;

    root->rightRotate(); 

    cout << "After Right Rotation (InOrder): ";
    root->printInOrder(); 
    cout << endl;

    
    
    AVLNode* root2 = new AVLNode(10);
    root2->right = new AVLNode(20);
    root2->right->right = new AVLNode(30);

    cout << "\nBefore Left Rotation (InOrder): ";
    root2->printInOrder(); 
    cout << endl;

    root2->leftRotate(); 

    cout << "After Left Rotation (InOrder): ";
    root2->printInOrder(); 
    cout << endl;

    return 0; 
}
