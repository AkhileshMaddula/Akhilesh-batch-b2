#include <iostream>
using namespace std;

class Rectangle
{
private:
    int length, width;

public:
    void setLength(int l)
    {
        if(l >= 0)
            length = l;
    }

    void setWidth(int w)
    {
        if(w >= 0)
            width = w;
    }

    int area()
    {
        return length * width;
    }

    int perimeter()
    {
        return 2 * (length + width);
    }
};

int main()
{
    Rectangle r;

    r.setLength(3);
    r.setWidth(2);

    cout << "Area = " << r.area() << endl;
    cout << "Perimeter = " << r.perimeter() << endl;

    return 0;
}