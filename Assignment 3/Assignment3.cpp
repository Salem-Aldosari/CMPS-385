#include <iostream>
#include <stdexcept>

const int MAX_STACK = 100; // Define maximum stack size.

class StackException : public std::exception { // Custom exception class for stack errors.
private:
    std::string message;
public:
    explicit StackException(const std::string& err) : message(err) {} // Constructor.
    const char* what() const noexcept override { return message.c_str(); } // Returns error message.
};

class Stack {
private:
    int items[MAX_STACK]; // Array to store stack elements.
    int top; // Index of the top element.

public:
    Stack() : top(-1) {} // Constructor: initializes top to -1 (empty stack).

    bool isEmpty() const { // Checks if the stack is empty.
        return top < 0;
    }

    void push(const int& newItem) { // Pushes an element onto the stack.
        if (top >= MAX_STACK - 1) // Checks for stack overflow.
            throw StackException("StackException: Stack full on push");
        items[++top] = newItem; // Increments top and adds the new item.
    }

    void topAndPop(int& stackTop) { // Retrieves and removes the top element.
        if (isEmpty()) // Checks for stack underflow.
            throw StackException("StackException: Stack empty on topAndPop");
        stackTop = items[top--]; // Retrieves the top element and decrements top.
    }
};

int main() {
    Stack s;

    try {
        s.push(50);
        s.push(40);
        s.push(10);

        int topElement;
        s.topAndPop(topElement); // Pops 50
        std::cout << "Top element popped: " << topElement << std::endl;

        s.topAndPop(topElement); // Pops 40
        std::cout << "Top element popped: " << topElement << std::endl;

        s.topAndPop(topElement); // Pops 10
        std::cout << "Top element popped: " << topElement << std::endl;

    }
    catch (const StackException& e) { // Catches stack exceptions.
        std::cerr << e.what() << std::endl; // Prints the error message.
    }

    return 0;
}