#include <iostream>
#include <stdexcept>

const int MAX_STACK = 100; 

class StackException : public std::exception { 
private:
    std::string message;
public:
    explicit StackException(const std::string& err) : message(err) {} 
    const char* what() const noexcept override { return message.c_str(); } 
};

class Stack {
private:
    int items[MAX_STACK]; 
    int top; 

public:
    Stack() : top(-1) {} 

    bool isEmpty() const { 
        return top < 0;
    }

    void push(const int& newItem) { 
        if (top >= MAX_STACK - 1) 
            throw StackException("StackException: Stack full on push");
        items[++top] = newItem; 
    }

    void topAndPop(int& stackTop) { 
        if (isEmpty()) 
            throw StackException("StackException: Stack empty on topAndPop");
        stackTop = items[top--]; 
    }
};

int main() {
    Stack s;

    try {
        s.push(50);
        s.push(40);
        s.push(10);

        int topElement;
        s.topAndPop(topElement); 
        std::cout << "Top element popped: " << topElement << std::endl;

        s.topAndPop(topElement); 
        std::cout << "Top element popped: " << topElement << std::endl;

        s.topAndPop(topElement); 
        std::cout << "Top element popped: " << topElement << std::endl;

    }
    catch (const StackException& e) { 
        std::cerr << e.what() << std::endl; 
    }

    return 0;
}
