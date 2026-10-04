#include <iostream>
using namespace std;

class Complex {
private:
    int real;
    int imag;

public:
    // Set data
    void setData(int r, int i) {
        real = r;
        imag = i;
    }

    // Display
    void display() {
        if (imag >= 0)
            cout << real << " + " << imag << "i" << endl;
        else
            cout << real << " - " << -imag << "i" << endl;
    }
};

int main() {
    Complex c[3];

    c[0].setData(2, 3);
    c[1].setData(4, 5);
    c[2].setData(6, -2);

    cout << "Complex Numbers:\n";

    for (int i = 0; i < 3; i++) {
        c[i].display();
    }

    return 0;
}