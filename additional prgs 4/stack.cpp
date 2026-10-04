#include <iostream>
using namespace std;

class Stack {
    int *arr;
    int top;
    int size;

public:
    // Constructor
    Stack(int s) {
        size = s;
        top = -1;

        arr = new int[size];

        cout << "Stack created\n";
    }

    // Push
    void push(int value) {
        if (top == size - 1) {
            cout << "Stack Overflow\n";
        }
        else {
            top++;
            arr[top] = value;
            cout << value << " pushed\n";
        }
    }

    // Pop
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
        }
        else {
            cout << arr[top] << " popped\n";
            top--;
        }
    }

    // Display
    void display() {
        if (top == -1) {
            cout << "Stack is empty\n";
        }
        else {
            cout << "Stack elements:\n";

            for (int i = top; i >= 0; i--) {
                cout << arr[i] << endl;
            }
        }
    }

    // Destructor
    ~Stack() {
        delete[] arr;
        cout << "Stack memory released\n";
    }
};

int main() {
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    s.pop();

    cout << "\nAfter pop:\n";
    s.display();

    return 0;
}