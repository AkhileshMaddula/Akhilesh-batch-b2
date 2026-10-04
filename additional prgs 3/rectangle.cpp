#include <iostream>
using namespace std;

class Rectangle {
private:
    int length;
    int width;

public:
    // Set length
    void setLength(int l) {
        if (l >= 0)
            length = l;
        else
            cout << "Invalid length\n";
    }

    // Set width
    void setWidth(int w) {
        if (w >= 0)
            width = w;
        else
            cout << "Invalid width\n";
    }

    // Get length
    int getLength() {
        return length;
    }

    // Get width
    int getWidth() {
        return width;
    }

    // Calculate area
    int area() {
        return length * width;
    }

    // Calculate perimeter
    int perimeter() {
        return 2 * (length + width);
    }
};

int main() {
    Rectangle r;

    r.setLength(10);
    r.setWidth(5);

    cout << "Length = " << r.getLength() << endl;
    cout << "Width = " << r.getWidth() << endl;
    cout << "Area = " << r.area() << endl;
    cout << "Perimeter = " << r.perimeter() << endl;

    return 0;
}