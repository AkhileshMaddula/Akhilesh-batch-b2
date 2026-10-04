#include <iostream>
using namespace std;

class Counter {
private:
    int count;

public:
    // Constructor
    Counter() {
        count = 0;
    }

    // Increment
    void increment() {
        count++;
    }

    // Reset
    void reset() {
        count = 0;
    }

    // Get value
    int get() {
        return count;
    }
};

int main() {
    Counter c[3];

    // Increment counters
    c[0].increment();
    c[0].increment();

    c[1].increment();
    c[1].increment();
    c[1].increment();

    c[2].increment();

    cout << "Counter 1 = " << c[0].get() << endl;
    cout << "Counter 2 = " << c[1].get() << endl;
    cout << "Counter 3 = " << c[2].get() << endl;

    // Reset counter 2
    c[1].reset();

    cout << "\nAfter resetting Counter 2:\n";
    cout << "Counter 1 = " << c[0].get() << endl;
    cout << "Counter 2 = " << c[1].get() << endl;
    cout << "Counter 3 = " << c[2].get() << endl;

    return 0;
}